#include "pch.h"


int
WSPAPI WSPBind(
    _In_ SOCKET s,
    _In_reads_bytes_(namelen) const struct sockaddr FAR* name,
    _In_ int namelen,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPBind(s, name, namelen, lpErrno);
}
