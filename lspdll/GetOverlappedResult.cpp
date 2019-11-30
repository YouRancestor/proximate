#include "pch.h"


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