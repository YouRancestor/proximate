#include "pch.h"



int
WSPAPI WSPListen(
    _In_ SOCKET s,
    _In_ int backlog,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPListen(s, backlog, lpErrno);
    return baseProcTable.lpWSPListen(s, backlog, lpErrno);
}