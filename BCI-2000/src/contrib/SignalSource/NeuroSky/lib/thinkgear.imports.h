// Import declarations for thinkgear.h, generated by dylib_imports.sh
#ifndef thinkgear_IMPORTS_H
#define thinkgear_IMPORTS_H

#include "Win32Defs.h"

#define TG_GetDriverVersion TG_GetDriverVersion_d77a
#define TG_GetNewConnectionId TG_GetNewConnectionId_c0c6
#define TG_SetStreamLog TG_SetStreamLog_2f84
#define TG_SetDataLog TG_SetDataLog_3210
#define TG_WriteStreamLog TG_WriteStreamLog_1882
#define TG_WriteDataLog TG_WriteDataLog_229a
#define TG_EnableLowPassFilter TG_EnableLowPassFilter_54d3
#define TG_EnableBlinkDetection TG_EnableBlinkDetection_80b9
#define TG_Connect TG_Connect_eec2
#define TG_ReadPackets TG_ReadPackets_6bc5
#define TG_GetValueStatus TG_GetValueStatus_1def
#define TG_GetValue TG_GetValue_a39b
#define TG_SendByte TG_SendByte_e4ec
#define TG_SetBaudrate TG_SetBaudrate_3f15
#define TG_SetDataFormat TG_SetDataFormat_a588
#define TG_EnableAutoRead TG_EnableAutoRead_1986
#define TG_Disconnect TG_Disconnect_d7e2
#define TG_FreeConnection TG_FreeConnection_eb21

#include "thinkgear.h"

#undef TG_GetDriverVersion
#undef TG_GetNewConnectionId
#undef TG_SetStreamLog
#undef TG_SetDataLog
#undef TG_WriteStreamLog
#undef TG_WriteDataLog
#undef TG_EnableLowPassFilter
#undef TG_EnableBlinkDetection
#undef TG_Connect
#undef TG_ReadPackets
#undef TG_GetValueStatus
#undef TG_GetValue
#undef TG_SendByte
#undef TG_SetBaudrate
#undef TG_SetDataFormat
#undef TG_EnableAutoRead
#undef TG_Disconnect
#undef TG_FreeConnection

extern "C" {
extern int ( *TG_GetDriverVersion)();
extern int ( *TG_GetNewConnectionId)();
extern int ( *TG_SetStreamLog)( int connectionId, const char *filename );
extern int ( *TG_SetDataLog)( int connectionId, const char *filename );
extern int ( *TG_WriteStreamLog)( int connectionId, int insertTimestamp, const char *msg );
extern int ( *TG_WriteDataLog)( int connectionId, int insertTimestamp, const char *msg );
extern int ( *TG_EnableLowPassFilter)( int connectionId, int rawSamplingRate );
extern int ( *TG_EnableBlinkDetection)( int connectionId, int enable );
extern int ( *TG_Connect)( int connectionId, const char *serialPortName, int serialBaudrate, int serialDataFormat );
extern int ( *TG_ReadPackets)( int connectionId, int numPackets );
extern int ( *TG_GetValueStatus)( int connectionId, int dataType );
extern float ( *TG_GetValue)( int connectionId, int dataType );
extern int ( *TG_SendByte)( int connectionId, int b );
extern int ( *TG_SetBaudrate)( int connectionId, int serialBaudrate );
extern int ( *TG_SetDataFormat)( int connectionId, int serialDataFormat );
extern int ( *TG_EnableAutoRead)( int connectionId, int enable );
extern void ( *TG_Disconnect)( int connectionId );
extern void ( *TG_FreeConnection)( int connectionId );
}

namespace Dylib { bool thinkgear_Loaded(); }

#endif // thinkgear_IMPORTS_H