#include "pch.h"

int
WSPAPI WSPAsyncSelect(
    _In_ SOCKET s,
    _In_ HWND hWnd,
    _In_ unsigned int wMsg,
    _In_ long lEvent,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);

    return baseProcTable.lpWSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno);
}
