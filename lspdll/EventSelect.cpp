#include "pch.h"



int
WSPAPI WSPEventSelect(
    _In_ SOCKET s,
    _In_opt_ WSAEVENT hEventObject,
    _In_ long lNetworkEvents,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno);
    return baseProcTable.lpWSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno);
}