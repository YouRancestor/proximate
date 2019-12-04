// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <WS2spi.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>
#include <map>
#include <mutex>


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

WSPPROC_TABLE nextProcs = { 0 };

std::string svr;
int port = 0;
std::string usr;
std::string pwd;

enum SyncType
{
    Sync = 0,
    Async = 1,
    Event = 2
};

struct AsyncParam
{
    long lEvent;
    HWND hWnd;
    unsigned int wMsg;
};

struct EventParam
{
    long lNetworkEvents;
    WSAEVENT hEventObject;
};

union Param
{
    AsyncParam async;
    EventParam event;
};

struct SyncInfo
{
    SyncType type;
    Param param;
};


std::map<SOCKET, SyncInfo> infoMap; // FIXME: How to get these info from SOCKET?
std::mutex infoMutex;


int
WSPAPI WSPConnect(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _In_opt_ LPWSABUF lpCallerData,
    _Out_opt_ LPWSABUF lpCalleeData,
    _In_opt_ LPQOS lpSQOS,
    _In_opt_ LPQOS lpGQOS,
    _Out_ LPINT lpErrno
) {
    int ret = 0;
    bool success = false;

    std::lock_guard<std::mutex> lock(infoMutex);


    // turn off notification
    const SyncInfo &info = infoMap[s];
    int err = 0;
    switch (info.type)
    {
    case Sync:
        break;
    case Async:
        nextProcs.lpWSPAsyncSelect(s, info.param.async.hWnd, 0, 0, &err);
        break;
    case Event:
        nextProcs.lpWSPEventSelect(s, info.param.event.hEventObject, 0, &err);
        break;
    default:
        break;
    }
    sockaddr_in svrAddr = { 0 };
    svrAddr.sin_family = ((sockaddr_in*)name)->sin_family;
    svrAddr.sin_port = htons(::port);
    inet_pton(svrAddr.sin_family,svr.c_str(), &svrAddr.sin_addr.S_un.S_addr);
    ret = nextProcs.lpWSPConnect(s, (sockaddr*)&svrAddr, sizeof(svrAddr), lpCallerData, lpCalleeData, lpSQOS, lpGQOS, lpErrno);
    do{

        // socks5 handshake
        char buf[512];
        DWORD bytesNumber = 0;
        WSABUF verifybuf;
        char verify[4] = { 0x05, 0x02, 0x00, 0x02 };
        verifybuf.buf = verify;
        verifybuf.len = 4;
        do
        {
            // TODO: check time out

            if (ret && *lpErrno != WSAEWOULDBLOCK && *lpErrno != WSAEINPROGRESS && *lpErrno != WSAENOTCONN)
            {
                goto end;
            }
            ret = nextProcs.lpWSPSend(s, &verifybuf, 1, &bytesNumber, 0, NULL, NULL, NULL, lpErrno);
            if (ret)
            {
                continue;
            }
            else
                break;
        } while (true);
        
        int method = 0;
        do
        {
            WSABUF handshakebuf;
            handshakebuf.buf = buf;
            handshakebuf.len = 512;
            DWORD Flags = 0;
            ret = nextProcs.lpWSPRecv(s, &handshakebuf, 1, &bytesNumber, &Flags, NULL, NULL, NULL, lpErrno);
            if (ret == 0 && bytesNumber > 0)
            {
                method = buf[1];
                break;
            }
            else if (*lpErrno != WSAEWOULDBLOCK && *lpErrno != WSAEINPROGRESS && *lpErrno != WSAENOTCONN)
            {
                *lpErrno = WSAECONNREFUSED;
                ret = SOCKET_ERROR;
                goto end;
            }
        } while (true);

        switch (method)
        {
        case 0x2: // user password
        {

        }
        case 0x0: // anonymous
        {
            std::string buffer;
            buffer.push_back(0x05); // VER
            buffer.push_back(0x01); // CMD CONNECT
            buffer.push_back(0x00); // reserved

            switch (name->sa_family)
            {
            case AF_INET: // IPv4
            {
                buffer.push_back(0x01); // IPv4
                // target ip
                sockaddr_in* addr = (sockaddr_in*)name;
                char* ip = (char*)&addr->sin_addr.S_un.S_addr;  // already in big endian
                buffer.push_back(ip[0]);
                buffer.push_back(ip[1]);
                buffer.push_back(ip[2]);
                buffer.push_back(ip[3]);
            }
                break;
            case AF_INET6: // IPv6 (not support yet)
            default:
                *lpErrno = WSAEPFNOSUPPORT;
                return WSAEADDRNOTAVAIL;
                break;
            }

            sockaddr_in* addr = (sockaddr_in*)name;
            // target port
            char* port = (char*)&addr->sin_port; // already in big endian
            buffer.push_back(port[0]);
            buffer.push_back(port[1]);


            WSABUF connbuf;
            memcpy(buf, buffer.c_str(), buffer.size());
            connbuf.buf = buf;
            connbuf.len = buffer.size();

            int ret = nextProcs.lpWSPSend(s, &connbuf, 1, &bytesNumber, 0, NULL, NULL, NULL, lpErrno);
            if (ret)
            {
                if (*lpErrno != WSAEWOULDBLOCK && *lpErrno != WSAEINPROGRESS && *lpErrno)
                    goto end;
            }

            do
            {
                connbuf.len = 512;
                DWORD Flags = 0;
                ret = nextProcs.lpWSPRecv(s, &connbuf, 1, &bytesNumber, &Flags, NULL, NULL, NULL, lpErrno);
                if (ret == 0 && bytesNumber > 0)
                {
                    switch (buf[1])
                    {
                    case 0x00: // success
                        success = true;
                        break;
                    default:
                        *lpErrno = WSAECONNREFUSED;
                        ret = SOCKET_ERROR;
                        goto end;
                    }
                    break;
                }
                else if (*lpErrno != WSAEWOULDBLOCK && *lpErrno != WSAEINPROGRESS)
                {
                    *lpErrno = WSAECONNREFUSED;
                    ret = SOCKET_ERROR;
                    goto end;
                }
            } while (true);
        }
            break;
        default:
            *lpErrno = WSAECONNRESET;
            ret = SOCKET_ERROR;
            goto end;
        }

    } while (0);

end:
    // resume notification
    switch (info.type)
    {
    case Sync:
        break;
    case Async:
        nextProcs.lpWSPAsyncSelect(s, info.param.async.hWnd, info.param.async.wMsg, info.param.async.lEvent, &err);
        if (success)
        {
            PostMessage(info.param.async.hWnd, info.param.async.wMsg, s, FD_CONNECT);
            PostMessage(info.param.async.hWnd, info.param.async.wMsg, s, FD_WRITE);
        }
        break;
    case Event:
        nextProcs.lpWSPEventSelect(s, info.param.event.hEventObject, info.param.event.lNetworkEvents, &err);
        if(success && (info.param.event.lNetworkEvents& FD_CONNECT) || (info.param.event.lNetworkEvents & FD_WRITE))
            SetEvent(info.param.event.hEventObject);
        break;
    default:
        break;
    }
    return ret;
}


int
WSPAPI WSPAsyncSelect(
    _In_ SOCKET s,
    _In_ HWND hWnd,
    _In_ unsigned int wMsg,
    _In_ long lEvent,
    _Out_ LPINT lpErrno
) {
    {
        std::lock_guard<std::mutex> lock(infoMutex);
        infoMap[s].param.async.hWnd = hWnd;
        infoMap[s].param.async.wMsg = wMsg;
        infoMap[s].param.async.lEvent = lEvent;
        if (!lEvent)
            infoMap[s].type = Sync;
        else
            infoMap[s].type = Async;
    }



    return nextProcs.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);
}

int
WSPAPI WSPEventSelect(
    _In_ SOCKET s,
    _In_opt_ WSAEVENT hEventObject,
    _In_ long lNetworkEvents,
    _Out_ LPINT lpErrno
) {
    {
        std::lock_guard<std::mutex> lock(infoMutex);
        infoMap[s].param.event.hEventObject = hEventObject;
        infoMap[s].param.event.lNetworkEvents = lNetworkEvents;
        if (!lNetworkEvents)
            infoMap[s].type = Sync;
        else
            infoMap[s].type = Event;
    }

    return nextProcs.lpWSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno);
}

int
WSPAPI WSPCloseSocket(
    _In_ SOCKET s,
    _Out_ LPINT lpErrno
) {
    {
        std::lock_guard<std::mutex> lock(infoMutex);
        infoMap.erase(s);
    }
    return nextProcs.lpWSPCloseSocket(s, lpErrno);
}

int
WSPAPI WSPCleanup(
    _Out_ LPINT lpErrno
) {
    {
        std::lock_guard<std::mutex> lock(infoMutex);
        infoMap.clear();
    }

    return nextProcs.lpWSPCleanup(lpErrno);
}


int Init(WSPPROC_TABLE* nextProcTable, char* svr, int port, char* usr, char* pwd)
{
    int ret = 0;

    // save next ptoctable
    nextProcs = *nextProcTable;

    nextProcTable->lpWSPConnect = WSPConnect;
    nextProcTable->lpWSPAsyncSelect = WSPAsyncSelect;
    nextProcTable->lpWSPEventSelect = WSPEventSelect;
    nextProcTable->lpWSPCleanup = WSPCleanup;

    if(svr)
        ::svr = svr;
    ::port = port;

    if(usr)
        ::usr = usr;
    if(pwd)
        ::pwd = pwd;

    return ret;
}

