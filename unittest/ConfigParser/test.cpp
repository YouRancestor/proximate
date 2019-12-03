#include "pch.h"

#include "ConfigParse.cpp"

TEST(ConfigParse, Cover) {
    TCHAR path[] =    _T("C:\\Program Files(x86)\\WinPcap\\rpcapd.exe");

    EXPECT_EQ(Cover(_T("C:\\Program Files(x86)\\WinPcap\\rpcapd.exe"), path), 3);
    EXPECT_EQ(Cover(_T("*\\rpcapd.exe"), path),2);
    //EXPECT_TRUE(Cover(_T("C:\\Program Files(x86)\\WinPcap\\*.exe"), path));
    //EXPECT_TRUE(Cover(_T("C:\\*\\rpcapd.exe"), path));
    EXPECT_TRUE(Cover(_T("*\\*.exe"), path));
    //EXPECT_FALSE(Cover(_T("D:\\*\\*.exe"), path));
    EXPECT_EQ(Cover(_T("*\\a.exe"), path),0);
    EXPECT_EQ(Cover(_T("C:\\Program Files\\WinPcap\\rpcapd.exe"), path),0);
    EXPECT_EQ(Cover(_T("C:\\Program Files(x86)\\WinPcap\\a.exe"), path),0);

}


static TCHAR exePath[] = _T("E:\\Home\\zyr\\Desktop\\实用工具\\SocketTool.exe");
TEST(ConfigParse, ReadRule) {
    Rule rule;

    SetEnvironmentVariable(_T("PROXIMATE_ROOT"), _T("E:\\CppProjects\\proximate-master\\bin"));
    bool ret = ReadRule(&rule);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(rule.needProxy);
    EXPECT_EQ(rule.proxyName, "SSH Tunnel");
}