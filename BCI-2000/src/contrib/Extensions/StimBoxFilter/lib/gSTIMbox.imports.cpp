// Import definitions for gSTIMbox.h, generated by dylib_imports.sh
#include "gSTIMbox.imports.h"
#include "DylibImports.h"


extern "C" {
int ( *gSTIMboxinit)(HANDLE *com, int comport, int inputSR, int inputFrame, int blocking) = 0;
int ( *gSTIMboxreset)(HANDLE com) = 0;
int ( *gSTIMboxsetMode)(HANDLE com, int nrPorts, int port[], int mode[]) = 0;
int ( *gSTIMboxsetPortState)(HANDLE com, int nrPorts, int port[], int state[]) = 0;
int ( *gSTIMboxsetFrequency)(HANDLE com, int nrPorts, int port[], double freq[]) = 0;
int ( *gSTIMboxclose)(HANDLE com) = 0;
int ( *gSTIMboxgetHWVersion)(HANDLE com, float &HWVersion) = 0;
int ( *gSTIMboxgetDriverVersion)(double &DriverVersion) = 0;
int ( *gSTIMboxgetConnStatus)(HANDLE com, int &status) = 0;
int ( *gSTIMboxgetInputs)(HANDLE com, int *buffer, int &overUnderflow) = 0;
int ( *gSTIMboxstartInputMonitoring)(HANDLE com) = 0;
int ( *gSTIMboxstopInputMonitoring)(HANDLE com) = 0;
int ( *gSTIMboxsetInputInversion)(HANDLE com, int inversion) = 0;
int ( *gSTIMboxgetInputSamplerate)(HANDLE com, int &sr) = 0;
int ( *gSTIMboxgetInputFramelength)(HANDLE com, int &fl) = 0;
int ( *gSTIMboxgetErrorMessage)(int error, int messagelength, char *errormessage) = 0;
}

static const Dylib::Import imports[] =
{
  { "gSTIMboxinit", (void**)&gSTIMboxinit, Dylib::Import::cMangled },
  { "gSTIMboxreset", (void**)&gSTIMboxreset, Dylib::Import::cMangled },
  { "gSTIMboxsetMode", (void**)&gSTIMboxsetMode, Dylib::Import::cMangled },
  { "gSTIMboxsetPortState", (void**)&gSTIMboxsetPortState, Dylib::Import::cMangled },
  { "gSTIMboxsetFrequency", (void**)&gSTIMboxsetFrequency, Dylib::Import::cMangled },
  { "gSTIMboxclose", (void**)&gSTIMboxclose, Dylib::Import::cMangled },
  { "gSTIMboxgetHWVersion", (void**)&gSTIMboxgetHWVersion, Dylib::Import::cMangled },
  { "gSTIMboxgetDriverVersion", (void**)&gSTIMboxgetDriverVersion, Dylib::Import::cMangled },
  { "gSTIMboxgetConnStatus", (void**)&gSTIMboxgetConnStatus, Dylib::Import::cMangled },
  { "gSTIMboxgetInputs", (void**)&gSTIMboxgetInputs, Dylib::Import::cMangled },
  { "gSTIMboxstartInputMonitoring", (void**)&gSTIMboxstartInputMonitoring, Dylib::Import::cMangled },
  { "gSTIMboxstopInputMonitoring", (void**)&gSTIMboxstopInputMonitoring, Dylib::Import::cMangled },
  { "gSTIMboxsetInputInversion", (void**)&gSTIMboxsetInputInversion, Dylib::Import::cMangled },
  { "gSTIMboxgetInputSamplerate", (void**)&gSTIMboxgetInputSamplerate, Dylib::Import::cMangled },
  { "gSTIMboxgetInputFramelength", (void**)&gSTIMboxgetInputFramelength, Dylib::Import::cMangled },
  { "gSTIMboxgetErrorMessage", (void**)&gSTIMboxgetErrorMessage, Dylib::Import::cMangled },
  { 0, 0, 0 }
};

// Here you may specify a custom error message to be displayed when the library cannot be found.
static const char* notFoundMsg = "";
// Here you may specify an URL to some local or remote help resource.
static const char* notFoundURL = "";
RegisterDylib( gSTIMbox, imports, notFoundMsg, notFoundURL );
