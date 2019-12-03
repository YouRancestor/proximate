#include "pch.h"

int
WSPAPI WSPDuplicateSocket(
    _In_ SOCKET s,
    _In_ DWORD dwProcessId,
    _Out_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPDuplicateSocket(s, dwProcessId, lpProtocolInfo, lpErrno);
    return baseProcTable.lpWSPDuplicateSocket(s, dwProcessId, lpProtocolInfo, lpErrno);
}