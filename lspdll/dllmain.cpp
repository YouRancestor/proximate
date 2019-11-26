#include <WinSock2.h>
#include <WS2spi.h>
#include <tchar.h>

#define N_(x) _T(x)

TCHAR exepath[MAX_PATH] = { 0 };

WSPPROC_TABLE baseProcTable = { 0 };

BOOL APIENTRY DllMain( HMODULE hModule,
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

SOCKET
WSPAPI WSPAccept(
    _In_ SOCKET s,
    _Out_writes_bytes_to_opt_(*addrlen, *addrlen) struct sockaddr FAR* addr,
    _Inout_opt_ LPINT addrlen,
    _In_opt_ LPCONDITIONPROC lpfnCondition,
    _In_opt_ DWORD_PTR dwCallbackData,
    _Out_ LPINT lpErrno
    );

INT
WSPAPI WSPAddressToString(
    _In_reads_bytes_(dwAddressLength) LPSOCKADDR lpsaAddress,
    _In_ DWORD dwAddressLength,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_to_(*lpdwAddressStringLength, *lpdwAddressStringLength) LPWSTR lpszAddressString,
    _Inout_ LPDWORD lpdwAddressStringLength,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPAsyncSelect(
    _In_ SOCKET s,
    _In_ HWND hWnd,
    _In_ unsigned int wMsg,
    _In_ long lEvent,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPBind(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPCancelBlockingCall(
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPCleanup(
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPCloseSocket(
    _In_ SOCKET s,
    _Out_ LPINT lpErrno
    );

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
    );

int
WSPAPI WSPDuplicateSocket(
    _In_ SOCKET s,
    _In_ DWORD dwProcessId,
    _Out_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPEnumNetworkEvents(
    _In_ SOCKET s,
    _In_ WSAEVENT hEventObject,
    _Out_ LPWSANETWORKEVENTS lpNetworkEvents,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPEventSelect(
    _In_ SOCKET s,
    _In_opt_ WSAEVENT hEventObject,
    _In_ long lNetworkEvents,
    _Out_ LPINT lpErrno
    );

BOOL
WSPAPI WSPGetOverlappedResult(
    _In_ SOCKET s,
    _In_ LPWSAOVERLAPPED lpOverlapped,
    _Out_ LPDWORD lpcbTransfer,
    _In_ BOOL fWait,
    _Out_ LPDWORD lpdwFlags,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPGetPeerName(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR* name,
    _Inout_ LPINT namelen,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPGetSockName(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR* name,
    _Inout_ LPINT namelen,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPGetSockOpt(
    _In_ SOCKET s,
    _In_ int level,
    _In_ int optname,
    _Out_writes_bytes_(*optlen) char FAR* optval,
    _Inout_ LPINT optlen,
    _Out_ LPINT lpErrno
    );

BOOL
WSPAPI WSPGetQOSByName(
    _In_ SOCKET s,
    _In_ LPWSABUF lpQOSName,
    _Out_ LPQOS lpQOS,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPIoctl(
    _In_ SOCKET s,
    _In_ DWORD dwIoControlCode,
    _In_reads_bytes_opt_(cbInBuffer) LPVOID lpvInBuffer,
    _In_ DWORD cbInBuffer,
    _Out_writes_bytes_to_opt_(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    _In_ DWORD cbOutBuffer,
    _Out_ LPDWORD lpcbBytesReturned,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
    );

SOCKET
WSPAPI WSPJoinLeaf(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _In_opt_ LPWSABUF lpCallerData,
    _Out_opt_ LPWSABUF lpCalleeData,
    _In_opt_ LPQOS lpSQOS,
    _In_opt_ LPQOS lpGQOS,
    _In_ DWORD dwFlags,
    _Out_ LPINT lpErrno
    );


int
WSPAPI WSPListen(
    _In_ SOCKET s,
    _In_ int backlog,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPRecv(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesRecvd,
    _Inout_ LPDWORD lpFlags,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _In_ LPINT lpErrno
    );

int
WSPAPI WSPRecvDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpInboundDisconnectData,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPRecvFrom(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesRecvd,
    _Inout_ LPDWORD lpFlags,
    _Out_writes_bytes_to_opt_(*lpFromlen, *lpFromlen) struct sockaddr FAR* lpFrom,
    _Inout_opt_ LPINT lpFromlen,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSelect(
    _In_ int nfds,
    _Inout_opt_ fd_set FAR* readfds,
    _Inout_opt_ fd_set FAR* writefds,
    _Inout_opt_ fd_set FAR* exceptfds,
    _In_opt_ const struct timeval FAR* timeout,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSend(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesSent,
    _In_ DWORD dwFlags,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSendDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpOutboundDisconnectData,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSendDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpOutboundDisconnectData,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSendTo(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesSent,
    _In_ DWORD dwFlags,
    _In_reads_bytes_opt_(iTolen) const struct sockaddr FAR* lpTo,
    _In_ int iTolen,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPSetSockOpt(
    _In_ SOCKET s,
    _In_ int level,
    _In_ int optname,
    _In_reads_bytes_opt_(optlen) const char FAR* optval,
    _In_ int optlen,
    _Out_ LPINT lpErrno
    );

int
WSPAPI WSPShutdown(
    _In_ SOCKET s,
    _In_ int how,
    _Out_ LPINT lpErrno
    );

SOCKET
WSPAPI WSPSocket(
    _In_ int af,
    _In_ int type,
    _In_ int protocol,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _In_ GROUP g,
    _In_ DWORD dwFlags,
    _Out_ LPINT lpErrno
    );

INT
WSPAPI WSPStringToAddress(
    _In_ LPWSTR AddressString,
    _In_ INT AddressFamily,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_bytes_to_(*lpAddressLength, *lpAddressLength) LPSOCKADDR lpAddress,
    _Inout_ LPINT lpAddressLength,
    _Out_ LPINT lpErrno
    );




bool FindProtocolByEntryId(DWORD entryId, LPWSAPROTOCOL_INFO info)
{
    bool ret = false;
    DWORD dwBufferLen = 16384;
    LPWSAPROTOCOL_INFO lpProtocolInfo = (LPWSAPROTOCOL_INFO)HeapAlloc(GetProcessHeap(), 0, dwBufferLen);
    if (!lpProtocolInfo)
        return ret;
    INT err;
    INT num = WSCEnumProtocols(NULL, lpProtocolInfo, &dwBufferLen, &err);

    for (INT i = 0; i < num; ++i)
    {
        if (lpProtocolInfo[i].dwCatalogEntryId == entryId)
        {
            ret = true;
            *info = lpProtocolInfo[i];
            break;
        }
    }
    HeapFree(GetProcessHeap(), 0, lpProtocolInfo);
    return ret;
}

#define REGISTER_PROC(procTable, procName) procTable##->##lp##procName##=procName

int
WSPAPI
WSPStartup(
    _In_ WORD wVersionRequested,
    _In_ LPWSPDATA lpWSPData,
    _In_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _In_ WSPUPCALLTABLE UpcallTable,
    _Out_ LPWSPPROC_TABLE lpProcTable
)
{
    if (lpProtocolInfo->ProtocolChain.ChainLen <= 1)
    {
        return WSAEPROVIDERFAILEDINIT;
    }

    // only support WinSock 2.x
    if ((LOBYTE(wVersionRequested) != 2) ||
        ((LOBYTE(wVersionRequested) == 2) &&
        (HIBYTE(wVersionRequested) > 2))) {

        lpWSPData->wVersion = MAKEWORD(2, 2);
        lpWSPData->wHighVersion = MAKEWORD(2, 2);

        return WSAVERNOTSUPPORTED;
    }
    else
    {
        lpWSPData->wVersion = MAKEWORD(2, HIBYTE(wVersionRequested));
        lpWSPData->wHighVersion = MAKEWORD(2, 2);
    }
    GetModuleFileName(0, exepath, MAX_PATH);

    REGISTER_PROC(lpProcTable, WSPAccept);
    REGISTER_PROC(lpProcTable, WSPAddressToString);
    REGISTER_PROC(lpProcTable, WSPAsyncSelect);
    REGISTER_PROC(lpProcTable, WSPBind);
    REGISTER_PROC(lpProcTable, WSPCancelBlockingCall);
    REGISTER_PROC(lpProcTable, WSPCleanup);
    REGISTER_PROC(lpProcTable, WSPCloseSocket);
    REGISTER_PROC(lpProcTable, WSPConnect);
    REGISTER_PROC(lpProcTable, WSPDuplicateSocket);
    REGISTER_PROC(lpProcTable, WSPEnumNetworkEvents);
    REGISTER_PROC(lpProcTable, WSPEventSelect);
    REGISTER_PROC(lpProcTable, WSPGetOverlappedResult);
    REGISTER_PROC(lpProcTable, WSPGetPeerName);
    REGISTER_PROC(lpProcTable, WSPGetSockName);
    REGISTER_PROC(lpProcTable, WSPGetSockOpt);
    REGISTER_PROC(lpProcTable, WSPGetQOSByName);
    REGISTER_PROC(lpProcTable, WSPIoctl);
    REGISTER_PROC(lpProcTable, WSPJoinLeaf);
    REGISTER_PROC(lpProcTable, WSPListen);
    REGISTER_PROC(lpProcTable, WSPRecv);
    REGISTER_PROC(lpProcTable, WSPRecvDisconnect);
    REGISTER_PROC(lpProcTable, WSPRecvFrom);
    REGISTER_PROC(lpProcTable, WSPSelect);
    REGISTER_PROC(lpProcTable, WSPSend);
    REGISTER_PROC(lpProcTable, WSPSendDisconnect);
    REGISTER_PROC(lpProcTable, WSPSendTo);
    REGISTER_PROC(lpProcTable, WSPSetSockOpt);
    REGISTER_PROC(lpProcTable, WSPShutdown);
    REGISTER_PROC(lpProcTable, WSPSocket);
    REGISTER_PROC(lpProcTable, WSPStringToAddress);

    // get base protocol entry id
    DWORD baseEntryId = lpProtocolInfo->ProtocolChain.ChainEntries[1];

    // get base protocol info
    WSAPROTOCOL_INFO baseProtocolInfo = { 0 };
    if (!FindProtocolByEntryId(baseEntryId, &baseProtocolInfo))
    {
        return WSAEPROVIDERFAILEDINIT;
    }

    // load base protocol
    // get base protocol dll path (may contain environment variables)
    INT error = 0;
    TCHAR baseProviderDllPath[MAX_PATH];
    int len = MAX_PATH;
    if (WSCGetProviderPath(&baseProtocolInfo.ProviderId, baseProviderDllPath, &len, &error) == SOCKET_ERROR)
        return WSAEPROVIDERFAILEDINIT;
    // expand environment strings
    if(!ExpandEnvironmentStrings(baseProviderDllPath, baseProviderDllPath, MAX_PATH))
        return WSAEPROVIDERFAILEDINIT;
    // load base protocol dll
    HMODULE baseProtoclDll = LoadLibrary(baseProviderDllPath);
    if (baseProtoclDll == NULL)
        return WSAEPROVIDERFAILEDINIT;
    // init base protocol
    LPWSPSTARTUP baseWSPStartup = (LPWSPSTARTUP)GetProcAddress(baseProtoclDll, "WSPStartup");
    if (NULL == baseWSPStartup)
        return WSAEPROVIDERFAILEDINIT;
    return baseWSPStartup(wVersionRequested, lpWSPData, lpProtocolInfo, UpcallTable, &baseProcTable);

}



SOCKET
WSPAPI WSPAccept(
    _In_ SOCKET s,
    _Out_writes_bytes_to_opt_(*addrlen, *addrlen) struct sockaddr FAR* addr,
    _Inout_opt_ LPINT addrlen,
    _In_opt_ LPCONDITIONPROC lpfnCondition,
    _In_opt_ DWORD_PTR dwCallbackData,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPAccept(s, addr, addrlen, lpfnCondition, dwCallbackData, lpErrno);
}

INT
WSPAPI WSPAddressToString(
    _In_reads_bytes_(dwAddressLength) LPSOCKADDR lpsaAddress,
    _In_ DWORD dwAddressLength,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_to_(*lpdwAddressStringLength, *lpdwAddressStringLength) LPWSTR lpszAddressString,
    _Inout_ LPDWORD lpdwAddressStringLength,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo, lpszAddressString, lpdwAddressStringLength, lpErrno);
}

int
WSPAPI WSPAsyncSelect(
    _In_ SOCKET s,
    _In_ HWND hWnd,
    _In_ unsigned int wMsg,
    _In_ long lEvent,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);
}

int
WSPAPI WSPBind(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPBind(s, name, namelen, lpErrno);
}

int
WSPAPI WSPCancelBlockingCall(
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCancelBlockingCall(lpErrno);
}

int
WSPAPI WSPCleanup(
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCleanup(lpErrno);
}

int
WSPAPI WSPCloseSocket(
    _In_ SOCKET s,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCloseSocket(s, lpErrno);
}

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
    return baseProcTable.lpWSPConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS, lpErrno);
}

int
WSPAPI WSPDuplicateSocket(
    _In_ SOCKET s,
    _In_ DWORD dwProcessId,
    _Out_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPDuplicateSocket(s, dwProcessId, lpProtocolInfo, lpErrno);
}

int
WSPAPI WSPEnumNetworkEvents(
    _In_ SOCKET s,
    _In_ WSAEVENT hEventObject,
    _Out_ LPWSANETWORKEVENTS lpNetworkEvents,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPEnumNetworkEvents(s, hEventObject, lpNetworkEvents, lpErrno);
}

int
WSPAPI WSPEventSelect(
    _In_ SOCKET s,
    _In_opt_ WSAEVENT hEventObject,
    _In_ long lNetworkEvents,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno);
}

BOOL
WSPAPI WSPGetOverlappedResult(
    _In_ SOCKET s,
    _In_ LPWSAOVERLAPPED lpOverlapped,
    _Out_ LPDWORD lpcbTransfer,
    _In_ BOOL fWait,
    _Out_ LPDWORD lpdwFlags,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetOverlappedResult(s, lpOverlapped, lpcbTransfer, fWait, lpdwFlags, lpErrno);
}

int
WSPAPI WSPGetPeerName(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR* name,
    _Inout_ LPINT namelen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetPeerName(s, name, namelen, lpErrno);
}

int
WSPAPI WSPGetSockName(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR* name,
    _Inout_ LPINT namelen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetSockName(s, name, namelen, lpErrno);
}

int
WSPAPI WSPGetSockOpt(
    _In_ SOCKET s,
    _In_ int level,
    _In_ int optname,
    _Out_writes_bytes_(*optlen) char FAR* optval,
    _Inout_ LPINT optlen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetSockOpt(s, level, optname, optval, optlen, lpErrno);
}

BOOL
WSPAPI WSPGetQOSByName(
    _In_ SOCKET s,
    _In_ LPWSABUF lpQOSName,
    _Out_ LPQOS lpQOS,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno);
}

int
WSPAPI WSPIoctl(
    _In_ SOCKET s,
    _In_ DWORD dwIoControlCode,
    _In_reads_bytes_opt_(cbInBuffer) LPVOID lpvInBuffer,
    _In_ DWORD cbInBuffer,
    _Out_writes_bytes_to_opt_(cbOutBuffer, *lpcbBytesReturned) LPVOID lpvOutBuffer,
    _In_ DWORD cbOutBuffer,
    _Out_ LPDWORD lpcbBytesReturned,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPIoctl(s, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer, lpcbBytesReturned, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

SOCKET
WSPAPI WSPJoinLeaf(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _In_opt_ LPWSABUF lpCallerData,
    _Out_opt_ LPWSABUF lpCalleeData,
    _In_opt_ LPQOS lpSQOS,
    _In_opt_ LPQOS lpGQOS,
    _In_ DWORD dwFlags,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPJoinLeaf(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS, dwFlags, lpErrno);
}


int
WSPAPI WSPListen(
    _In_ SOCKET s,
    _In_ int backlog,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPListen(s, backlog, lpErrno);
}

int
WSPAPI WSPRecv(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesRecvd,
    _Inout_ LPDWORD lpFlags,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _In_ LPINT lpErrno
) {
    return baseProcTable.lpWSPRecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

int
WSPAPI WSPRecvDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpInboundDisconnectData,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno);
}

int
WSPAPI WSPRecvFrom(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesRecvd,
    _Inout_ LPDWORD lpFlags,
    _Out_writes_bytes_to_opt_(*lpFromlen, *lpFromlen) struct sockaddr FAR* lpFrom,
    _Inout_opt_ LPINT lpFromlen,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPRecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

int
WSPAPI WSPSelect(
    _In_ int nfds,
    _Inout_opt_ fd_set FAR* readfds,
    _Inout_opt_ fd_set FAR* writefds,
    _Inout_opt_ fd_set FAR* exceptfds,
    _In_opt_ const struct timeval FAR* timeout,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSelect(nfds, readfds, writefds, exceptfds, timeout, lpErrno);
}

int
WSPAPI WSPSend(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesSent,
    _In_ DWORD dwFlags,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

int
WSPAPI WSPSendDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpOutboundDisconnectData,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSendDisconnect(s, lpOutboundDisconnectData, lpErrno);
}

int
WSPAPI WSPSendTo(
    _In_ SOCKET s,
    _In_reads_(dwBufferCount) LPWSABUF lpBuffers,
    _In_ DWORD dwBufferCount,
    _Out_opt_ LPDWORD lpNumberOfBytesSent,
    _In_ DWORD dwFlags,
    _In_reads_bytes_opt_(iTolen) const struct sockaddr FAR* lpTo,
    _In_ int iTolen,
    _Inout_opt_ LPWSAOVERLAPPED lpOverlapped,
    _In_opt_ LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    _In_opt_ LPWSATHREADID lpThreadId,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno);
}

int
WSPAPI WSPSetSockOpt(
    _In_ SOCKET s,
    _In_ int level,
    _In_ int optname,
    _In_reads_bytes_opt_(optlen) const char FAR* optval,
    _In_ int optlen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSetSockOpt(s, level, optname, optval, optlen, lpErrno);
}

int
WSPAPI WSPShutdown(
    _In_ SOCKET s,
    _In_ int how,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPShutdown(s, how, lpErrno);
}

SOCKET
WSPAPI WSPSocket(
    _In_ int af,
    _In_ int type,
    _In_ int protocol,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _In_ GROUP g,
    _In_ DWORD dwFlags,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPSocket(af, type, protocol, lpProtocolInfo, g, dwFlags, lpErrno);
}

INT
WSPAPI WSPStringToAddress(
    _In_ LPWSTR AddressString,
    _In_ INT AddressFamily,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_bytes_to_(*lpAddressLength, *lpAddressLength) LPSOCKADDR lpAddress,
    _Inout_ LPINT lpAddressLength,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo, lpAddress, lpAddressLength, lpErrno);
}
