#include "pch.h"


int
WSPAPI WSPSelect(
    _In_ int nfds,
    _Inout_opt_ fd_set FAR* readfds,
    _Inout_opt_ fd_set FAR* writefds,
    _Inout_opt_ fd_set FAR* exceptfds,
    _In_opt_ const struct timeval FAR* timeout,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPSelect(nfds, readfds, writefds, exceptfds, timeout, lpErrno);
    return baseProcTable.lpWSPSelect(nfds, readfds, writefds, exceptfds, timeout, lpErrno);
}