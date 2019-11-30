#include "pch.h"

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
