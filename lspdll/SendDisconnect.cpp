#include "pch.h"


int
WSPAPI WSPSendDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpOutboundDisconnectData,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPSendDisconnect(s, lpOutboundDisconnectData, lpErrno);
    return baseProcTable.lpWSPSendDisconnect(s, lpOutboundDisconnectData, lpErrno);
}