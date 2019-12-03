#include "pch.h"

int
WSPAPI WSPCloseSocket(
    _In_ SOCKET s,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPCloseSocket(s, lpErrno);
    return baseProcTable.lpWSPCloseSocket(s, lpErrno);
}
