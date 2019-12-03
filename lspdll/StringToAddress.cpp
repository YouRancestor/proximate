#include "pch.h"




INT
WSPAPI WSPStringToAddress(
    _In_ LPWSTR AddressString,
    _In_ INT AddressFamily,
    _In_opt_ LPWSAPROTOCOL_INFOW lpProtocolInfo,
    _Out_writes_bytes_to_(*lpAddressLength, *lpAddressLength) LPSOCKADDR lpAddress,
    _Inout_ LPINT lpAddressLength,
    _Out_ LPINT lpErrno
) {
    if (chain)
        return chain->procs.lpWSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo, lpAddress, lpAddressLength, lpErrno);

    return baseProcTable.lpWSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo, lpAddress, lpAddressLength, lpErrno);
}
