#include "pch.h"



int
WSPAPI WSPRecvDisconnect(
    _In_ SOCKET s,
    _In_opt_ LPWSABUF lpInboundDisconnectData,
    _Out_ LPINT lpErrno
) {
    return baseProcTable.lpWSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno);
}