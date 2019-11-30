#include "pch.h"



int
WSPAPI WSPListen(
    _In_ SOCKET s,
    _In_ int backlog,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPListen(s, backlog, lpErrno);
}