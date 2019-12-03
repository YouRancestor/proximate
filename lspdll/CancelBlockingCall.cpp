#include "pch.h"


int
WSPAPI WSPCancelBlockingCall(
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPCancelBlockingCall(lpErrno);
    return baseProcTable.lpWSPCancelBlockingCall(lpErrno);
}