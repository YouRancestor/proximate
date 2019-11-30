#include "pch.h"

int
WSPAPI WSPCloseSocket(
    _In_ SOCKET s,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCloseSocket(s, lpErrno);
}