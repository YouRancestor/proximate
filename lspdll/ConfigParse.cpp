#include "pch.h"
#include "cJSON.h"
#include <string>

#ifdef UNICODE
#define strcmp wcscmp
#define _tstrlen wcslen
#define strcat_s wcscat_s
#else
#define strcmp strcmp
#define _tstrlen strlen
#define strcat strcat
#endif

int Cover(TCHAR* config, TCHAR* path)
{
    if (!strcmp(config, _T("*\\*.exe")))
    {
        return 1;
    }
    else if(!strcmp(config,path))
    {
        return 3;
    }
    else
    {
        size_t configLen = _tstrlen(config);
        size_t pathLen = _tstrlen(path);

        size_t offset = pathLen - configLen;

        TCHAR* p1 = path + offset +1;
        TCHAR* p2 = config + 1;

        if (offset<=0)
        {
            return 0;
        }
        else if (!strcmp(p1, p2))
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
}


bool ReadRule(Rule* cfg)
{
    TCHAR ruleConfigPath[MAX_PATH];
    int len = GetEnvironmentVariable(_T("PROXIMATE_ROOT"), ruleConfigPath, MAX_PATH);
    strcat_s(ruleConfigPath, _T("\\config\\rules.json"));
    std::string jsonString;
    FILE* ruleConfigFile = NULL;
    _tfopen_s(&ruleConfigFile, ruleConfigPath, _T("r"));

    if (!ruleConfigFile)
        return false;

    char buff[256];
    while (int n = fread_s(buff, 256, 1, 256, ruleConfigFile))
    {
        jsonString.append(buff, n);
    }
    if (feof(ruleConfigFile))
    {
        fclose(ruleConfigFile);
    }
    else
    {
        fclose(ruleConfigFile);
        return false;
    }

    bool ret = false;

    cJSON *root = cJSON_Parse(jsonString.c_str());
    const char* error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
        fprintf(stderr, "Error before: %s\n", error_ptr);
    }

    cJSON* match = NULL;
    cJSON* rule = NULL;
    cJSON* programs = NULL;
    cJSON* program=NULL;
    cJSON* active = NULL;
    cJSON* proxy = NULL;

    WCHAR cfgstr[MAX_PATH];
    size_t retval = 0;

    int level = 0;
    int l = 0;

    if (!cJSON_IsArray(root))
        goto end;

    cJSON_ArrayForEach(rule, root)
    {
        if (!cJSON_IsObject(rule))
            goto end;
        programs = cJSON_GetObjectItem(rule, "programs");

        if (!cJSON_IsArray(programs))
            goto end;

        cJSON_ArrayForEach(program, programs)
        {
            if (!cJSON_IsString(program))
                goto end;

            //mbstowcs_s(&retval, cfgstr, MAX_PATH, program->valuestring, strlen(program->valuestring));
            MultiByteToWideChar(CP_UTF8, 0, program->valuestring, strlen(program->valuestring)+1, cfgstr, MAX_PATH);

            l = Cover(cfgstr, exePath);
            if (l > level)
            {
                level = l;
                match = rule;
                break;
            }
        }
    }
    if (match)
    {
        active = cJSON_GetObjectItem(match, "active");
        if (!cJSON_IsBool(active))
            goto end;
        if (active->valueint)
        {
            proxy = cJSON_GetObjectItem(match, "proxy");
            if (!cJSON_IsString(proxy))
                goto end;
            cfg->needProxy = true;
            cfg->proxyName = proxy->valuestring;
        }
    }
    ret = true;

end:
    cJSON_Delete(root);

    return ret;
}

Protocol* LoadProtocol(const Rule& rule, WSPPROC_TABLE baseProcTable)
{
    TCHAR proxyConfigPath[MAX_PATH];
    int len = GetEnvironmentVariable(_T("PROXIMATE_ROOT"), proxyConfigPath, MAX_PATH);
    strcat_s(proxyConfigPath, _T("\\config\\proxies.json"));

    std::string jsonString;
    FILE* proxyConfigFile = NULL;
    _tfopen_s(&proxyConfigFile, proxyConfigPath, _T("r"));

    if (!proxyConfigFile)
        return NULL;

    char buff[256];
    while (int n = fread_s(buff, 256, 1, 256, proxyConfigFile))
    {
        jsonString.append(buff, n);
    }
    if (feof(proxyConfigFile))
    {
        fclose(proxyConfigFile);
    }
    else
    {
        fclose(proxyConfigFile);
        return NULL;
    }

    Protocol* ch = NULL;

    cJSON *root = cJSON_Parse(jsonString.c_str());

    cJSON* proxy=NULL;
    if (!cJSON_IsArray(root))
        goto end;

    cJSON_ArrayForEach(proxy, root)
    {
        cJSON* protocolName = cJSON_GetObjectItem(proxy, "protocol");
        //char* proto = protocolName->valuestring;

        if (rule.proxyName != protocolName->valuestring)
        {
            continue;
        }

        cJSON* server = cJSON_GetObjectItem(proxy, "server");
        cJSON* port = cJSON_GetObjectItem(proxy, "port");
        cJSON* username = cJSON_GetObjectItem(proxy, "username");
        cJSON* password = cJSON_GetObjectItem(proxy, "password");

        char* svr = NULL;
        if (cJSON_IsString(server))
        {
            svr = server->valuestring;
        }
        int pt = 0;
        if (cJSON_IsNumber(port))
        {
            pt = port->valueint;
        }
        char* usr = NULL;
        if (cJSON_IsString(username))
        {
            usr = username->valuestring;
        }
        char* pwd = NULL;
        if (cJSON_IsString(password))
        {
            pwd = password->valuestring;
        }


        TCHAR protoPluginDir[MAX_PATH];
        int len = GetEnvironmentVariable(_T("PROXIMATE_ROOT"), protoPluginDir, MAX_PATH);

        wchar_t protoName[MAX_PATH];
        MultiByteToWideChar(CP_UTF8, 0, protocolName->valuestring, strlen(protocolName->valuestring) + 1, protoName, MAX_PATH);
        std::wstring protoPluginPath = protoPluginDir;
        protoPluginPath = protoPluginPath
#if (defined WIN64 || defined X64)
        + L"\\dll64\\"
#else
        + L"\\dll32\\"
#endif // WIN64
        + protoName + L".dll";


        HMODULE mod = LoadLibraryW(protoPluginPath.c_str());
        if (!mod)
            continue;
        FunInit init = (FunInit)GetProcAddress(mod, "Init");
        if (!init)
            continue;
        Protocol* protocol = new Protocol;
        protocol->next = NULL;
        protocol->dll = mod;
        protocol->procs = baseProcTable;
        init(&protocol->procs, svr, pt, usr, pwd);
        ch = protocol;
        break;
    }

end:
    cJSON_Delete(root);

    return ch;
}

void FreeProtocol(Protocol* chain)
{
    if (!chain)
        return;

    if(chain->dll)
        FreeLibrary(chain->dll);
    Protocol* next = chain->next;
    delete chain;
    FreeProtocol(next); // tail recursion
}
