// Import definitions for BioRadio150DLL.h, generated by dylib_imports.sh
#include "BioRadio150DLL.imports.h"
#include "DylibImports.h"

extern "C" {
BOOL (__stdcall *FindDevices)(TDeviceInfo *DeviceList, int *DeviceCount, int MaxCount, TUpdateStatusEvent UpdateStatusProc) = 0;
BOOL (__stdcall *FindDevicesSimple)(char *DevicePortNameList[], int *DeviceCount, int MaxDeviceCount, int PortNameStrLen) = 0;
unsigned int (__stdcall *CreateBioRadio)() = 0;
int (__stdcall *DestroyBioRadio)(unsigned int BioRadio150) = 0;
int (__stdcall *StartCommunication)(unsigned int BioRadio150 , char *PortName) = 0;
int (__stdcall *StartAcq)(unsigned int BioRadio150, char DisplayProgressDialog) = 0;
int (__stdcall *StopAcq)(unsigned int BioRadio150) = 0;
int (__stdcall *DisableBuffering)(unsigned int BioRadio150) = 0;
int (__stdcall *EnableBuffering)(unsigned int BioRadio150) = 0;
int (__stdcall *StopCommunication)(unsigned int BioRadio150) = 0;
int (__stdcall *LoadConfig)(unsigned int BioRadio150, char *Filename) = 0;
int (__stdcall *SaveConfig)(unsigned int BioRadio150, char *Filename) = 0;
int (__stdcall *PingConfig)(unsigned int BioRadio150, char DisplayProgressDialog) = 0;
int (__stdcall *GetConfig)(unsigned int BioRadio150, TBioRadioConfig *ConfigStruct, char PingDevice, char DisplayProgressDialog) = 0;
int (__stdcall *ProgramConfig)(unsigned int BioRadio150, char DisplayProgressDialog, const char *Filename) = 0;
int (__stdcall *SetConfig)(unsigned int BioRadio150, TBioRadioConfig *ConfigStruct, char ProgramDevice, char DisplayProgressDialog) = 0;
long (__stdcall *GetSampleRate)(unsigned int BioRadio150) = 0;
long (__stdcall *GetBitResolution)(unsigned int BioRadio150) = 0;
int (__stdcall *GetFastSweepsPerPacket)(unsigned int BioRadio150) = 0;
int (__stdcall *GetSlowSweepsPerPacket)(unsigned int BioRadio150) = 0;
int (__stdcall *GetNumEnabledInputs)(unsigned int BioRadio150, int *FastMainInputs, int *FastAuxInputs, int *SlowAuxInputs) = 0;
int (__stdcall *GetNumEnabledSlowInputs)(unsigned int BioRadio150) = 0;
int (__stdcall *GetNumEnabledFastInputs)(unsigned int BioRadio150) = 0;
long (__stdcall *GetMode)(unsigned int BioRadio150, WORD &Mode) = 0;
long (__stdcall *GetNumChannels)(unsigned int BioRadio150) = 0;
WORD (__stdcall *GetEnabledFastInputs)(unsigned int BioRadio150) = 0;
char (__stdcall *GetEnabledSlowInputs)(unsigned int BioRadio150) = 0;
int (__stdcall *TransferBuffer)(unsigned int BioRadio150) = 0;
int (__stdcall *ReadScaledData)(unsigned int BioRadio150, double *Data, int Size, int *NumRead) = 0;
int (__stdcall *ReadRawData)(unsigned int BioRadio150, WORD *Data, int Size, int *NumRead) = 0;
int (__stdcall *ReadScaledFastAndSlowData)(unsigned int BioRadio150, double *FastInputsData, int FastInputsSize, int *FastInputsNumRead, WORD *SlowInputsData, int SlowInputsSize, int *SlowInputsNumRead) = 0;
int (__stdcall *ReadRawFastAndSlowData)(unsigned int BioRadio150, WORD *FastInputsData, int FastInputsSize, int *FastInputsNumRead, WORD *SlowInputsData, int SlowInputsSize, int *SlowInputsNumRead) = 0;
int (__stdcall *SetBadDataValues)(unsigned int BioRadio150, double BadDataValueScaled, WORD BadDataValueRaw) = 0;
int (__stdcall *SetPadWait)(unsigned int BioRadio150, int numMissingPackets) = 0;
int (__stdcall *GetRFChannel)(unsigned int BioRadio150) = 0;
int (__stdcall *SetRFChannel)(unsigned int BioRadio150, int RFChannel) = 0;
int (__stdcall *GetUsableRFChannelList)(int *UsableRFChannelList, int Size) = 0;
int (__stdcall *GetFreqHoppingMode)(unsigned int BioRadio150) = 0;
int (__stdcall *GetFreqHoppingModeIndicator)() = 0;
int (__stdcall *SetFreqHoppingMode)(unsigned int BioRadio150, bool HoppingEnabled) = 0;
unsigned int (__stdcall *GetGoodPackets)(unsigned int BioRadio150) = 0;
unsigned int (__stdcall *GetBadPackets)(unsigned int BioRadio150) = 0;
unsigned int (__stdcall *GetDroppedPackets)(unsigned int BioRadio150) = 0;
int (__stdcall *GetUpRSSI)(unsigned int BioRadio150) = 0;
int (__stdcall *GetDownRSSI)(unsigned int BioRadio150) = 0;
int (__stdcall *GetLinkBufferSize)(unsigned int BioRadio150) = 0;
int (__stdcall *GetBitErrCount)(unsigned int BioRadio150) = 0;
int (__stdcall *GetBitErrRate)(unsigned int BioRadio150) = 0;
double (__stdcall *GetBatteryStatus)(unsigned int BioRadio150) = 0;
int (__stdcall *GetBioRadioModelString)(unsigned int BioRadio150, char *BioRadioModelString, int StrLength) = 0;
int (__stdcall *GetDeviceID)(unsigned int BioRadio150, WORD *DeviceID) = 0;
int (__stdcall *GetDeviceIDString)(unsigned int BioRadio150, char *DeviceIDCStr, int StrLength) = 0;
int (__stdcall *GetFirmwareVersionString)(unsigned int BioRadio150, char *VersionString, int StrLength) = 0;
void (__stdcall *GetDLLVersionString)(char *VersionString, int StrLength) = 0;
}

static const Dylib::Import imports[] =
{
  { "FindDevices", (void**)&FindDevices, Dylib::Import::cMangled },
  { "FindDevicesSimple", (void**)&FindDevicesSimple, Dylib::Import::cMangled },
  { "CreateBioRadio", (void**)&CreateBioRadio, Dylib::Import::cMangled },
  { "DestroyBioRadio", (void**)&DestroyBioRadio, Dylib::Import::cMangled },
  { "StartCommunication", (void**)&StartCommunication, Dylib::Import::cMangled },
  { "StartAcq", (void**)&StartAcq, Dylib::Import::cMangled },
  { "StopAcq", (void**)&StopAcq, Dylib::Import::cMangled },
  { "DisableBuffering", (void**)&DisableBuffering, Dylib::Import::cMangled },
  { "EnableBuffering", (void**)&EnableBuffering, Dylib::Import::cMangled },
  { "StopCommunication", (void**)&StopCommunication, Dylib::Import::cMangled },
  { "LoadConfig", (void**)&LoadConfig, Dylib::Import::cMangled },
  { "SaveConfig", (void**)&SaveConfig, Dylib::Import::cMangled },
  { "PingConfig", (void**)&PingConfig, Dylib::Import::cMangled },
  { "GetConfig", (void**)&GetConfig, Dylib::Import::cMangled },
  { "ProgramConfig", (void**)&ProgramConfig, Dylib::Import::cMangled },
  { "SetConfig", (void**)&SetConfig, Dylib::Import::cMangled },
  { "GetSampleRate", (void**)&GetSampleRate, Dylib::Import::cMangled },
  { "GetBitResolution", (void**)&GetBitResolution, Dylib::Import::cMangled },
  { "GetFastSweepsPerPacket", (void**)&GetFastSweepsPerPacket, Dylib::Import::cMangled },
  { "GetSlowSweepsPerPacket", (void**)&GetSlowSweepsPerPacket, Dylib::Import::cMangled },
  { "GetNumEnabledInputs", (void**)&GetNumEnabledInputs, Dylib::Import::cMangled },
  { "GetNumEnabledSlowInputs", (void**)&GetNumEnabledSlowInputs, Dylib::Import::cMangled },
  { "GetNumEnabledFastInputs", (void**)&GetNumEnabledFastInputs, Dylib::Import::cMangled },
  { "GetMode", (void**)&GetMode, Dylib::Import::cMangled },
  { "GetNumChannels", (void**)&GetNumChannels, Dylib::Import::cMangled },
  { "GetEnabledFastInputs", (void**)&GetEnabledFastInputs, Dylib::Import::cMangled },
  { "GetEnabledSlowInputs", (void**)&GetEnabledSlowInputs, Dylib::Import::cMangled },
  { "TransferBuffer", (void**)&TransferBuffer, Dylib::Import::cMangled },
  { "ReadScaledData", (void**)&ReadScaledData, Dylib::Import::cMangled },
  { "ReadRawData", (void**)&ReadRawData, Dylib::Import::cMangled },
  { "ReadScaledFastAndSlowData", (void**)&ReadScaledFastAndSlowData, Dylib::Import::cMangled },
  { "ReadRawFastAndSlowData", (void**)&ReadRawFastAndSlowData, Dylib::Import::cMangled },
  { "SetBadDataValues", (void**)&SetBadDataValues, Dylib::Import::cMangled },
  { "SetPadWait", (void**)&SetPadWait, Dylib::Import::cMangled },
  { "GetRFChannel", (void**)&GetRFChannel, Dylib::Import::cMangled },
  { "SetRFChannel", (void**)&SetRFChannel, Dylib::Import::cMangled },
  { "GetUsableRFChannelList", (void**)&GetUsableRFChannelList, Dylib::Import::cMangled },
  { "GetFreqHoppingMode", (void**)&GetFreqHoppingMode, Dylib::Import::cMangled },
  { "GetFreqHoppingModeIndicator", (void**)&GetFreqHoppingModeIndicator, Dylib::Import::cMangled },
  { "SetFreqHoppingMode", (void**)&SetFreqHoppingMode, Dylib::Import::cMangled },
  { "GetGoodPackets", (void**)&GetGoodPackets, Dylib::Import::cMangled },
  { "GetBadPackets", (void**)&GetBadPackets, Dylib::Import::cMangled },
  { "GetDroppedPackets", (void**)&GetDroppedPackets, Dylib::Import::cMangled },
  { "GetUpRSSI", (void**)&GetUpRSSI, Dylib::Import::cMangled },
  { "GetDownRSSI", (void**)&GetDownRSSI, Dylib::Import::cMangled },
  { "GetLinkBufferSize", (void**)&GetLinkBufferSize, Dylib::Import::cMangled },
  { "GetBitErrCount", (void**)&GetBitErrCount, Dylib::Import::cMangled },
  { "GetBitErrRate", (void**)&GetBitErrRate, Dylib::Import::cMangled },
  { "GetBatteryStatus", (void**)&GetBatteryStatus, Dylib::Import::cMangled },
  { "GetBioRadioModelString", (void**)&GetBioRadioModelString, Dylib::Import::cMangled },
  { "GetDeviceID", (void**)&GetDeviceID, Dylib::Import::cMangled },
  { "GetDeviceIDString", (void**)&GetDeviceIDString, Dylib::Import::cMangled },
  { "GetFirmwareVersionString", (void**)&GetFirmwareVersionString, Dylib::Import::cMangled },
  { "GetDLLVersionString", (void**)&GetDLLVersionString, Dylib::Import::cMangled },
  { 0, 0, 0 }
};

// Here you may specify a custom error message to be displayed when the library cannot be found.
static const char* notFoundMsg = "";
// Here you may specify an URL to some local or remote help resource.
static const char* notFoundURL = "";
RegisterDylib( BioRadio150DLL, imports, notFoundMsg, notFoundURL );

