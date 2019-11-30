#include "pch.h"


int
WSPAPI WSPShutdown(
    _In_ SOCKET s,
    _In_ int how,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPShutdown(s, how, lpErrno);
}