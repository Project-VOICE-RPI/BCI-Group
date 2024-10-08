// Import definitions for thinkgear.h, generated by dylib_imports.sh
#include "thinkgear.imports.h"
#include "DylibImports.h"

extern "C" {
int ( *TG_GetDriverVersion)() = 0;
int ( *TG_GetNewConnectionId)() = 0;
int ( *TG_SetStreamLog)( int connectionId, const char *filename ) = 0;
int ( *TG_SetDataLog)( int connectionId, const char *filename ) = 0;
int ( *TG_WriteStreamLog)( int connectionId, int insertTimestamp, const char *msg ) = 0;
int ( *TG_WriteDataLog)( int connectionId, int insertTimestamp, const char *msg ) = 0;
int ( *TG_EnableLowPassFilter)( int connectionId, int rawSamplingRate ) = 0;
int ( *TG_EnableBlinkDetection)( int connectionId, int enable ) = 0;
int ( *TG_Connect)( int connectionId, const char *serialPortName, int serialBaudrate, int serialDataFormat ) = 0;
int ( *TG_ReadPackets)( int connectionId, int numPackets ) = 0;
int ( *TG_GetValueStatus)( int connectionId, int dataType ) = 0;
float ( *TG_GetValue)( int connectionId, int dataType ) = 0;
int ( *TG_SendByte)( int connectionId, int b ) = 0;
int ( *TG_SetBaudrate)( int connectionId, int serialBaudrate ) = 0;
int ( *TG_SetDataFormat)( int connectionId, int serialDataFormat ) = 0;
int ( *TG_EnableAutoRead)( int connectionId, int enable ) = 0;
void ( *TG_Disconnect)( int connectionId ) = 0;
void ( *TG_FreeConnection)( int connectionId ) = 0;
}

static const Dylib::Import imports[] =
{
  { "TG_GetDriverVersion", (void**)&TG_GetDriverVersion, Dylib::Import::cMangled },
  { "TG_GetNewConnectionId", (void**)&TG_GetNewConnectionId, Dylib::Import::cMangled },
  { "TG_SetStreamLog", (void**)&TG_SetStreamLog, Dylib::Import::cMangled },
  { "TG_SetDataLog", (void**)&TG_SetDataLog, Dylib::Import::cMangled },
  { "TG_WriteStreamLog", (void**)&TG_WriteStreamLog, Dylib::Import::cMangled },
  { "TG_WriteDataLog", (void**)&TG_WriteDataLog, Dylib::Import::cMangled },
  { "TG_EnableLowPassFilter", (void**)&TG_EnableLowPassFilter, Dylib::Import::cMangled },
  { "TG_EnableBlinkDetection", (void**)&TG_EnableBlinkDetection, Dylib::Import::cMangled },
  { "TG_Connect", (void**)&TG_Connect, Dylib::Import::cMangled },
  { "TG_ReadPackets", (void**)&TG_ReadPackets, Dylib::Import::cMangled },
  { "TG_GetValueStatus", (void**)&TG_GetValueStatus, Dylib::Import::cMangled },
  { "TG_GetValue", (void**)&TG_GetValue, Dylib::Import::cMangled },
  { "TG_SendByte", (void**)&TG_SendByte, Dylib::Import::cMangled },
  { "TG_SetBaudrate", (void**)&TG_SetBaudrate, Dylib::Import::cMangled },
  { "TG_SetDataFormat", (void**)&TG_SetDataFormat, Dylib::Import::cMangled },
  { "TG_EnableAutoRead", (void**)&TG_EnableAutoRead, Dylib::Import::cMangled },
  { "TG_Disconnect", (void**)&TG_Disconnect, Dylib::Import::cMangled },
  { "TG_FreeConnection", (void**)&TG_FreeConnection, Dylib::Import::cMangled },
  { 0, 0, 0 }
};

// Here you may specify a custom error message to be displayed when the library cannot be found.
static const char* notFoundMsg = "";
// Here you may specify an URL to some local or remote help resource.
static const char* notFoundURL = "";
RegisterDylib( thinkgear, imports, notFoundMsg, notFoundURL );

