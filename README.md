# proξmate
Capture network packets and forward to agent server.

## Usage

### Installation
```
bin  # the installation directory  
├─ config
│  ├─ proxies.json
│  └─ rules.json
├─ lspdll32           # 32bit
│  └─ proxipcap.dll
├─ lspdll64           # 64bit
│  └─ proxipcap.dll
├─ protocol32         # 32bit
│  ├─ socks5.dll
│  └─ ...             # other protocol plugins
└─ protocol64         # 64bit
   ├─ socks5.dll      
   └─ ...             # other protocol plugins
```
### Deploy
Copy ```lspdll64\proxipcap.dll``` to ```C:\Windows\System32\```  
Copy ```lspdll32\proxipcap.dll``` to ```C:\Windows\SysWOW64\```  
### Environment
Set environment variable ```PROXIMATE_ROOT``` to ```X:\path\to\bin```(no "\\" at the end)
### Config
Edit config\proxies.json to set proxy servers.  
Edit config\rules.json to set applications you want to apply the proxies.  
