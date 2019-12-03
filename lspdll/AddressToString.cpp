#include "pch.h"


INT
WSPAPI WSPAddressToString(
    _In_reads_bytes_(dwAddressLength) LPSOCKADDR lpsaAddress,
    _In_ DWORD dwAddressLength,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_to_(*lpdwAddressStringLength, *lpdwAddressStringLength) LPWSTR lpszAddressString,
    _Inout_ LPDWORD lpdwAddressStringLength,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo, lpszAddressString, lpdwAddressStringLength, lpErrno);

    return baseProcTable.lpWSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo, lpszAddressString, lpdwAddressStringLength, lpErrno);
}
