#include "pch.h"


int
WSPAPI WSPGetSockName(
    _In_ SOCKET s,
    _Out_writes_bytes_to_(*namelen, *namelen) struct sockaddr FAR* name,
    _Inout_ LPINT namelen,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPGetSockName(s, name, namelen, lpErrno);
    return baseProcTable.lpWSPGetSockName(s, name, namelen, lpErrno);
}