#include "pch.h"

int
WSPAPI WSPCleanup(
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPCleanup(lpErrno);
}