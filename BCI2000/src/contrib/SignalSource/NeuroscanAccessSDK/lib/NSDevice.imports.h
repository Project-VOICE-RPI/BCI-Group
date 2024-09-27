// Import declarations for NSDevice.h, generated by dylib_imports.sh
#ifndef NSDevice_IMPORTS_H
#define NSDevice_IMPORTS_H

#include "Win32Defs.h"

#define NSDConnect NSDConnect_a057
#define NSDDisconnect NSDDisconnect_303a
#define NSDGetCapabilities NSDGetCapabilities_2a5f
#define NSDGetBlocksPerSecond NSDGetBlocksPerSecond_63f7
#define NSDGetConfiguration NSDGetConfiguration_d0ac
#define NSDSetConfiguration NSDSetConfiguration_a40d
#define NSDCreateConfiguration NSDCreateConfiguration_4bb9
#define NSDGetData NSDGetData_0de1

#include "NSDevice.h"

#undef NSDConnect
#undef NSDDisconnect
#undef NSDGetCapabilities
#undef NSDGetBlocksPerSecond
#undef NSDGetConfiguration
#undef NSDSetConfiguration
#undef NSDCreateConfiguration
#undef NSDGetData

extern "C" {
extern long (__stdcall *NSDConnect)(int nType,const char* pId);
extern int (__stdcall *NSDDisconnect)(void);
extern int (__stdcall *NSDGetCapabilities)(char* pCapabilities);
extern int (__stdcall *NSDGetBlocksPerSecond)(void);
extern int (__stdcall *NSDGetConfiguration)(char* pConfiguration);
extern int (__stdcall *NSDSetConfiguration)(char* pConfiguration);
extern int (__stdcall *NSDCreateConfiguration)(int nChannels, int nRate);
extern int (__stdcall *NSDGetData)(float* pData);
}

namespace Dylib { bool NSDevice_Loaded(); }

#endif // NSDevice_IMPORTS_H
