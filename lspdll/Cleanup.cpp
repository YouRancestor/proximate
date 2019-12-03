#include "pch.h"

int
WSPAPI WSPCleanup(
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPCleanup(lpErrno);
    return baseProcTable.lpWSPCleanup(lpErrno);
}