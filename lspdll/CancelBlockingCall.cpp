#include "pch.h"


int
WSPAPI WSPCancelBlockingCall(
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCancelBlockingCall(lpErrno);
}