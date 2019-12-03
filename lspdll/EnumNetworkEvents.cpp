#include "pch.h"


int
WSPAPI WSPEnumNetworkEvents(
    _In_ SOCKET s,
    _In_ WSAEVENT hEventObject,
    _Out_ LPWSANETWORKEVENTS lpNetworkEvents,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPEnumNetworkEvents(s, hEventObject, lpNetworkEvents, lpErrno);
    return baseProcTable.lpWSPEnumNetworkEvents(s, hEventObject, lpNetworkEvents, lpErrno);
}