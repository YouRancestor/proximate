#include "pch.h"


int
WSPAPI WSPGetSockOpt(
    _In_ SOCKET s,
    _In_ int level,
    _In_ int optname,
    _Out_writes_bytes_(*optlen) char FAR* optval,
    _Inout_ LPINT optlen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPGetSockOpt(s, level, optname, optval, optlen, lpErrno);
}