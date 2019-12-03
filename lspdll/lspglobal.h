#pragma once

#include <WS2spi.h>
#include <tchar.h>
#include <string>

extern WSPPROC_TABLE baseProcTable;

extern TCHAR exePath[];

int Cover(TCHAR* config, TCHAR* path);

struct Rule;
struct Protocol;

struct Rule
{
    bool needProxy;
    std::string proxyName;
    //std::vector<PortRange> dstPortRanges;
    //std::vector<IpAddressRange> dstAddressRanges;
};

struct Protocol
{
    WSPPROC_TABLE procs;

    Protocol* next;
    HMODULE dll;
};

bool ReadRule(Rule* cfg);

Protocol* LoadProtocol(const Rule& rule, WSPPROC_TABLE baseProcTable);
void FreeProtocol(Protocol* chain);

typedef int (*FunInit)(WSPPROC_TABLE *nextProcTable, char* svr, int port, char* usr, char* pwd);

extern Protocol* chain;