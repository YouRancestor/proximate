#include "pch.h"


BOOL
WSPAPI WSPGetQOSByName(
    _In_ SOCKET s,
    _In_ LPWSABUF lpQOSName,
    _Out_ LPQOS lpQOS,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno);
    return baseProcTable.lpWSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno);
}