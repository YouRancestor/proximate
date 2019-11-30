#include "pch.h"

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

