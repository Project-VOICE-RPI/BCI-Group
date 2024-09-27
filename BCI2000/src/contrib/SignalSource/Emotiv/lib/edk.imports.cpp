// Import definitions for include/edk.h, generated by dylib_imports.sh
#include "edk.imports.h"
#include "DylibImports.h"

extern "C" {
EmoStateHandle ( *ES_Create)() = 0;
void ( *ES_Free)(EmoStateHandle state) = 0;
void ( *ES_Init)(EmoStateHandle state) = 0;
float ( *ES_GetTimeFromStart)(EmoStateHandle state) = 0;
int ( *ES_GetHeadsetOn)(EmoStateHandle state) = 0;
int ( *ES_GetNumContactQualityChannels)(EmoStateHandle state) = 0;
EE_EEG_ContactQuality_t ( *ES_GetContactQuality)(EmoStateHandle state, int electroIdx) = 0;
int ( *ES_GetContactQualityFromAllChannels)(EmoStateHandle state, EE_EEG_ContactQuality_t* contactQuality, size_t numChannels) = 0;
int ( *ES_ExpressivIsBlink)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsLeftWink)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsRightWink)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsEyesOpen)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsLookingUp)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsLookingDown)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsLookingLeft)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsLookingRight)(EmoStateHandle state) = 0;
void ( *ES_ExpressivGetEyelidState)(EmoStateHandle state, float* leftEye, float* rightEye) = 0;
void ( *ES_ExpressivGetEyeLocation)(EmoStateHandle state, float* x, float* y) = 0;
float ( *ES_ExpressivGetEyebrowExtent)(EmoStateHandle state) = 0;
float ( *ES_ExpressivGetSmileExtent)(EmoStateHandle state) = 0;
float ( *ES_ExpressivGetClenchExtent)(EmoStateHandle state) = 0;
EE_ExpressivAlgo_t ( *ES_ExpressivGetUpperFaceAction)(EmoStateHandle state) = 0;
float ( *ES_ExpressivGetUpperFaceActionPower)(EmoStateHandle state) = 0;
EE_ExpressivAlgo_t ( *ES_ExpressivGetLowerFaceAction)(EmoStateHandle state) = 0;
float ( *ES_ExpressivGetLowerFaceActionPower)(EmoStateHandle state) = 0;
int ( *ES_ExpressivIsActive)(EmoStateHandle state, EE_ExpressivAlgo_t type) = 0;
float ( *ES_AffectivGetExcitementLongTermScore)(EmoStateHandle state) = 0;
float ( *ES_AffectivGetExcitementShortTermScore)(EmoStateHandle state) = 0;
int ( *ES_AffectivIsActive)(EmoStateHandle state, EE_AffectivAlgo_t type) = 0;
float ( *ES_AffectivGetMeditationScore)(EmoStateHandle state) = 0;
float ( *ES_AffectivGetFrustrationScore)(EmoStateHandle state) = 0;
float ( *ES_AffectivGetEngagementBoredomScore)(EmoStateHandle state) = 0;
EE_CognitivAction_t ( *ES_CognitivGetCurrentAction)(EmoStateHandle state) = 0;
float ( *ES_CognitivGetCurrentActionPower)(EmoStateHandle state) = 0;
int ( *ES_CognitivIsActive)(EmoStateHandle state) = 0;
EE_SignalStrength_t ( *ES_GetWirelessSignalStatus)(EmoStateHandle state) = 0;
void ( *ES_Copy)(EmoStateHandle a, EmoStateHandle b) = 0;
int ( *ES_AffectivEqual)(EmoStateHandle a, EmoStateHandle b) = 0;
int ( *ES_ExpressivEqual)(EmoStateHandle a, EmoStateHandle b) = 0;
int ( *ES_CognitivEqual)(EmoStateHandle a, EmoStateHandle b) = 0;
int ( *ES_EmoEngineEqual)(EmoStateHandle a, EmoStateHandle b) = 0;
int ( *ES_Equal)(EmoStateHandle a, EmoStateHandle b) = 0;
void ( *ES_GetBatteryChargeLevel)(EmoStateHandle state, int* chargeLevel, int* maxChargeLevel) = 0;
int ( *EE_EngineConnect)() = 0;
int ( *EE_EngineRemoteConnect)(const char* szHost, unsigned short port) = 0;
int ( *EE_EngineDisconnect)() = 0;
int ( *EE_EnableDiagnostics)(const char* szFilename, int fEnable, int nReserved) = 0;
EmoEngineEventHandle ( *EE_EmoEngineEventCreate)() = 0;
EmoEngineEventHandle ( *EE_ProfileEventCreate)() = 0;
void ( *EE_EmoEngineEventFree)(EmoEngineEventHandle hEvent) = 0;
EmoStateHandle ( *EE_EmoStateCreate)() = 0;
void ( *EE_EmoStateFree)(EmoStateHandle hState) = 0;
EE_Event_t ( *EE_EmoEngineEventGetType)(EmoEngineEventHandle hEvent) = 0;
EE_CognitivEvent_t ( *EE_CognitivEventGetType)(EmoEngineEventHandle hEvent) = 0;
EE_ExpressivEvent_t ( *EE_ExpressivEventGetType)(EmoEngineEventHandle hEvent) = 0;
int ( *EE_EmoEngineEventGetUserId)(EmoEngineEventHandle hEvent, unsigned int *pUserIdOut) = 0;
int ( *EE_EmoEngineEventGetEmoState)(EmoEngineEventHandle hEvent, EmoStateHandle hEmoState) = 0;
int ( *EE_EngineGetNextEvent)(EmoEngineEventHandle hEvent) = 0;
int ( *EE_EngineClearEventQueue)(int eventTypes) = 0;
int ( *EE_EngineGetNumUser)(unsigned int* pNumUserOut) = 0;
int ( *EE_SetHardwarePlayerDisplay)(unsigned int userId, unsigned int playerNum) = 0;
int ( *EE_SetUserProfile)(unsigned int userId, const unsigned char profileBuffer[], unsigned int length) = 0;
int ( *EE_GetUserProfile)(unsigned int userId, EmoEngineEventHandle hEvent) = 0;
int ( *EE_GetBaseProfile)(EmoEngineEventHandle hEvent) = 0;
int ( *EE_GetUserProfileSize)(EmoEngineEventHandle hEvt, unsigned int* pProfileSizeOut) = 0;
int ( *EE_GetUserProfileBytes)(EmoEngineEventHandle hEvt, unsigned char destBuffer[], unsigned int length) = 0;
int ( *EE_LoadUserProfile)(unsigned int userID, const char* szInputFilename) = 0;
int ( *EE_SaveUserProfile)(unsigned int userID, const char* szOutputFilename) = 0;
int ( *EE_ExpressivSetThreshold)(unsigned int userId, EE_ExpressivAlgo_t algoName, EE_ExpressivThreshold_t thresholdName, int value) = 0;
int ( *EE_ExpressivGetThreshold)(unsigned int userId, EE_ExpressivAlgo_t algoName, EE_ExpressivThreshold_t thresholdName, int *pValueOut) = 0;
int ( *EE_ExpressivSetTrainingAction)(unsigned int userId, EE_ExpressivAlgo_t action) = 0;
int ( *EE_ExpressivSetTrainingControl)(unsigned int userId, EE_ExpressivTrainingControl_t control) = 0;
int ( *EE_ExpressivGetTrainingAction)(unsigned int userId, EE_ExpressivAlgo_t* pActionOut) = 0;
int ( *EE_ExpressivGetTrainingTime)(unsigned int userId, unsigned int* pTrainingTimeOut) = 0;
int ( *EE_ExpressivGetTrainedSignatureActions)(unsigned int userId, unsigned long* pTrainedActionsOut) = 0;
int ( *EE_ExpressivGetTrainedSignatureAvailable)(unsigned int userId, int* pfAvailableOut) = 0;
int ( *EE_ExpressivSetSignatureType)(unsigned int userId, EE_ExpressivSignature_t sigType) = 0;
int ( *EE_ExpressivGetSignatureType)(unsigned int userId, EE_ExpressivSignature_t* pSigTypeOut) = 0;
int ( *EE_CognitivSetActiveActions)(unsigned int userId, unsigned long activeActions) = 0;
int ( *EE_CognitivGetActiveActions)(unsigned int userId, unsigned long* pActiveActionsOut) = 0;
int ( *EE_CognitivGetTrainingTime)(unsigned int userId, unsigned int* pTrainingTimeOut) = 0;
int ( *EE_CognitivSetTrainingControl)(unsigned int userId, EE_CognitivTrainingControl_t control) = 0;
int ( *EE_CognitivSetTrainingAction)(unsigned int userId, EE_CognitivAction_t action) = 0;
int ( *EE_CognitivGetTrainingAction)(unsigned int userId, EE_CognitivAction_t* pActionOut) = 0;
int ( *EE_CognitivGetTrainedSignatureActions)(unsigned int userId, unsigned long* pTrainedActionsOut) = 0;
int ( *EE_CognitivGetOverallSkillRating)(unsigned int userId, float* pOverallSkillRatingOut) = 0;
int ( *EE_CognitivGetActionSkillRating)(unsigned int userId, EE_CognitivAction_t action, float* pActionSkillRatingOut) = 0;
int ( *EE_CognitivSetActivationLevel)(unsigned int userId, int level) = 0;
int ( *EE_CognitivSetActionSensitivity)(unsigned int userId, int action1Sensitivity, int action2Sensitivity, int action3Sensitivity, int action4Sensitivity) = 0;
int ( *EE_CognitivGetActivationLevel)(unsigned int userId, int *pLevelOut) = 0;
int ( *EE_CognitivGetActionSensitivity)(unsigned int userId, int* pAction1SensitivityOut, int* pAction2SensitivityOut, int* pAction3SensitivityOut, int* pAction4SensitivityOut) = 0;
int ( *EE_CognitivStartSamplingNeutral)(unsigned int userId) = 0;
int ( *EE_CognitivStopSamplingNeutral)(unsigned int userId) = 0;
int ( *EE_CognitivSetSignatureCaching)(unsigned int userId, unsigned int enabled) = 0;
int ( *EE_CognitivGetSignatureCaching)(unsigned int userId, unsigned int* pEnabledOut) = 0;
int ( *EE_CognitivSetSignatureCacheSize)(unsigned int userId, unsigned int size) = 0;
int ( *EE_CognitivGetSignatureCacheSize)(unsigned int userId, unsigned int* pSizeOut) = 0;
int ( *EE_HeadsetGetSensorDetails)(EE_InputChannels_t channelId, InputSensorDescriptor_t* pDescriptorOut) = 0;
int ( *EE_HardwareGetVersion)(unsigned int userId, unsigned long* pHwVersionOut) = 0;
int ( *EE_SoftwareGetVersion)(char* pszVersionOut, unsigned int nVersionChars, unsigned long* pBuildNumOut) = 0;
int ( *EE_HeadsetGetGyroDelta)(unsigned int userId, int* pXOut, int* pYOut) = 0;
int ( *EE_HeadsetGyroRezero)(unsigned int userId) = 0;
OptimizationParamHandle ( *EE_OptimizationParamCreate)() = 0;
void ( *EE_OptimizationParamFree)(OptimizationParamHandle hParam) = 0;
int ( *EE_OptimizationEnable)(OptimizationParamHandle hParam) = 0;
int ( *EE_OptimizationIsEnabled)(bool* pEnabledOut) = 0;
int ( *EE_OptimizationDisable)() = 0;
int ( *EE_OptimizationGetParam)(OptimizationParamHandle hParam) = 0;
int ( *EE_OptimizationGetVitalAlgorithm)(OptimizationParamHandle hParam, EE_EmotivSuite_t suite, unsigned int* pVitalAlgorithmBitVectorOut) = 0;
int ( *EE_OptimizationSetVitalAlgorithm)(OptimizationParamHandle hParam, EE_EmotivSuite_t suite, unsigned int vitalAlgorithmBitVector) = 0;
int ( *EE_ResetDetection)(unsigned int userId, EE_EmotivSuite_t suite, unsigned int detectionBitVector) = 0;
DataHandle ( *EE_DataCreate)() = 0;
void ( *EE_DataFree)(DataHandle hData) = 0;
int ( *EE_DataUpdateHandle)(unsigned int userId, DataHandle hData) = 0;
int ( *EE_DataGet)(DataHandle hData, EE_DataChannel_t channel, double buffer[], unsigned int bufferSizeInSample) = 0;
int ( *EE_DataGetNumberOfSample)(DataHandle hData, unsigned int* nSampleOut) = 0;
int ( *EE_DataSetBufferSizeInSec)(float bufferSizeInSec) = 0;
int ( *EE_DataGetBufferSizeInSec)(float* pBufferSizeInSecOut) = 0;
int ( *EE_DataAcquisitionEnable)(unsigned int userId, bool enable) = 0;
int ( *EE_DataAcquisitionIsEnabled)(unsigned int userId, bool* pEnableOut) = 0;
int ( *EE_DataSetSychronizationSignal)(unsigned int userId, int signal) = 0;
int ( *EE_DataSetMarker)(unsigned int userId, int marker) = 0;
int ( *EE_DataGetSamplingRate)(unsigned int userId, unsigned int* samplingRateOut) = 0;
}

static const Dylib::Import imports[] =
{
  { "ES_Create", (void**)&ES_Create, Dylib::Import::cMangled },
  { "ES_Free", (void**)&ES_Free, Dylib::Import::cMangled },
  { "ES_Init", (void**)&ES_Init, Dylib::Import::cMangled },
  { "ES_GetTimeFromStart", (void**)&ES_GetTimeFromStart, Dylib::Import::cMangled },
  { "ES_GetHeadsetOn", (void**)&ES_GetHeadsetOn, Dylib::Import::cMangled },
  { "ES_GetNumContactQualityChannels", (void**)&ES_GetNumContactQualityChannels, Dylib::Import::cMangled },
  { "ES_GetContactQuality", (void**)&ES_GetContactQuality, Dylib::Import::cMangled },
  { "ES_GetContactQualityFromAllChannels", (void**)&ES_GetContactQualityFromAllChannels, Dylib::Import::cMangled },
  { "ES_ExpressivIsBlink", (void**)&ES_ExpressivIsBlink, Dylib::Import::cMangled },
  { "ES_ExpressivIsLeftWink", (void**)&ES_ExpressivIsLeftWink, Dylib::Import::cMangled },
  { "ES_ExpressivIsRightWink", (void**)&ES_ExpressivIsRightWink, Dylib::Import::cMangled },
  { "ES_ExpressivIsEyesOpen", (void**)&ES_ExpressivIsEyesOpen, Dylib::Import::cMangled },
  { "ES_ExpressivIsLookingUp", (void**)&ES_ExpressivIsLookingUp, Dylib::Import::cMangled },
  { "ES_ExpressivIsLookingDown", (void**)&ES_ExpressivIsLookingDown, Dylib::Import::cMangled },
  { "ES_ExpressivIsLookingLeft", (void**)&ES_ExpressivIsLookingLeft, Dylib::Import::cMangled },
  { "ES_ExpressivIsLookingRight", (void**)&ES_ExpressivIsLookingRight, Dylib::Import::cMangled },
  { "ES_ExpressivGetEyelidState", (void**)&ES_ExpressivGetEyelidState, Dylib::Import::cMangled },
  { "ES_ExpressivGetEyeLocation", (void**)&ES_ExpressivGetEyeLocation, Dylib::Import::cMangled },
  { "ES_ExpressivGetEyebrowExtent", (void**)&ES_ExpressivGetEyebrowExtent, Dylib::Import::cMangled },
  { "ES_ExpressivGetSmileExtent", (void**)&ES_ExpressivGetSmileExtent, Dylib::Import::cMangled },
  { "ES_ExpressivGetClenchExtent", (void**)&ES_ExpressivGetClenchExtent, Dylib::Import::cMangled },
  { "ES_ExpressivGetUpperFaceAction", (void**)&ES_ExpressivGetUpperFaceAction, Dylib::Import::cMangled },
  { "ES_ExpressivGetUpperFaceActionPower", (void**)&ES_ExpressivGetUpperFaceActionPower, Dylib::Import::cMangled },
  { "ES_ExpressivGetLowerFaceAction", (void**)&ES_ExpressivGetLowerFaceAction, Dylib::Import::cMangled },
  { "ES_ExpressivGetLowerFaceActionPower", (void**)&ES_ExpressivGetLowerFaceActionPower, Dylib::Import::cMangled },
  { "ES_ExpressivIsActive", (void**)&ES_ExpressivIsActive, Dylib::Import::cMangled },
  { "ES_AffectivGetExcitementLongTermScore", (void**)&ES_AffectivGetExcitementLongTermScore, Dylib::Import::cMangled },
  { "ES_AffectivGetExcitementShortTermScore", (void**)&ES_AffectivGetExcitementShortTermScore, Dylib::Import::cMangled },
  { "ES_AffectivIsActive", (void**)&ES_AffectivIsActive, Dylib::Import::cMangled },
  { "ES_AffectivGetMeditationScore", (void**)&ES_AffectivGetMeditationScore, Dylib::Import::cMangled },
  { "ES_AffectivGetFrustrationScore", (void**)&ES_AffectivGetFrustrationScore, Dylib::Import::cMangled },
  { "ES_AffectivGetEngagementBoredomScore", (void**)&ES_AffectivGetEngagementBoredomScore, Dylib::Import::cMangled },
  { "ES_CognitivGetCurrentAction", (void**)&ES_CognitivGetCurrentAction, Dylib::Import::cMangled },
  { "ES_CognitivGetCurrentActionPower", (void**)&ES_CognitivGetCurrentActionPower, Dylib::Import::cMangled },
  { "ES_CognitivIsActive", (void**)&ES_CognitivIsActive, Dylib::Import::cMangled },
  { "ES_GetWirelessSignalStatus", (void**)&ES_GetWirelessSignalStatus, Dylib::Import::cMangled },
  { "ES_Copy", (void**)&ES_Copy, Dylib::Import::cMangled },
  { "ES_AffectivEqual", (void**)&ES_AffectivEqual, Dylib::Import::cMangled },
  { "ES_ExpressivEqual", (void**)&ES_ExpressivEqual, Dylib::Import::cMangled },
  { "ES_CognitivEqual", (void**)&ES_CognitivEqual, Dylib::Import::cMangled },
  { "ES_EmoEngineEqual", (void**)&ES_EmoEngineEqual, Dylib::Import::cMangled },
  { "ES_Equal", (void**)&ES_Equal, Dylib::Import::cMangled },
  { "ES_GetBatteryChargeLevel", (void**)&ES_GetBatteryChargeLevel, Dylib::Import::cMangled },
  { "EE_EngineConnect", (void**)&EE_EngineConnect, Dylib::Import::cMangled },
  { "EE_EngineRemoteConnect", (void**)&EE_EngineRemoteConnect, Dylib::Import::cMangled },
  { "EE_EngineDisconnect", (void**)&EE_EngineDisconnect, Dylib::Import::cMangled },
  { "EE_EnableDiagnostics", (void**)&EE_EnableDiagnostics, Dylib::Import::cMangled },
  { "EE_EmoEngineEventCreate", (void**)&EE_EmoEngineEventCreate, Dylib::Import::cMangled },
  { "EE_ProfileEventCreate", (void**)&EE_ProfileEventCreate, Dylib::Import::cMangled },
  { "EE_EmoEngineEventFree", (void**)&EE_EmoEngineEventFree, Dylib::Import::cMangled },
  { "EE_EmoStateCreate", (void**)&EE_EmoStateCreate, Dylib::Import::cMangled },
  { "EE_EmoStateFree", (void**)&EE_EmoStateFree, Dylib::Import::cMangled },
  { "EE_EmoEngineEventGetType", (void**)&EE_EmoEngineEventGetType, Dylib::Import::cMangled },
  { "EE_CognitivEventGetType", (void**)&EE_CognitivEventGetType, Dylib::Import::cMangled },
  { "EE_ExpressivEventGetType", (void**)&EE_ExpressivEventGetType, Dylib::Import::cMangled },
  { "EE_EmoEngineEventGetUserId", (void**)&EE_EmoEngineEventGetUserId, Dylib::Import::cMangled },
  { "EE_EmoEngineEventGetEmoState", (void**)&EE_EmoEngineEventGetEmoState, Dylib::Import::cMangled },
  { "EE_EngineGetNextEvent", (void**)&EE_EngineGetNextEvent, Dylib::Import::cMangled },
  { "EE_EngineClearEventQueue", (void**)&EE_EngineClearEventQueue, Dylib::Import::cMangled },
  { "EE_EngineGetNumUser", (void**)&EE_EngineGetNumUser, Dylib::Import::cMangled },
  { "EE_SetHardwarePlayerDisplay", (void**)&EE_SetHardwarePlayerDisplay, Dylib::Import::cMangled },
  { "EE_SetUserProfile", (void**)&EE_SetUserProfile, Dylib::Import::cMangled },
  { "EE_GetUserProfile", (void**)&EE_GetUserProfile, Dylib::Import::cMangled },
  { "EE_GetBaseProfile", (void**)&EE_GetBaseProfile, Dylib::Import::cMangled },
  { "EE_GetUserProfileSize", (void**)&EE_GetUserProfileSize, Dylib::Import::cMangled },
  { "EE_GetUserProfileBytes", (void**)&EE_GetUserProfileBytes, Dylib::Import::cMangled },
  { "EE_LoadUserProfile", (void**)&EE_LoadUserProfile, Dylib::Import::cMangled },
  { "EE_SaveUserProfile", (void**)&EE_SaveUserProfile, Dylib::Import::cMangled },
  { "EE_ExpressivSetThreshold", (void**)&EE_ExpressivSetThreshold, Dylib::Import::cMangled },
  { "EE_ExpressivGetThreshold", (void**)&EE_ExpressivGetThreshold, Dylib::Import::cMangled },
  { "EE_ExpressivSetTrainingAction", (void**)&EE_ExpressivSetTrainingAction, Dylib::Import::cMangled },
  { "EE_ExpressivSetTrainingControl", (void**)&EE_ExpressivSetTrainingControl, Dylib::Import::cMangled },
  { "EE_ExpressivGetTrainingAction", (void**)&EE_ExpressivGetTrainingAction, Dylib::Import::cMangled },
  { "EE_ExpressivGetTrainingTime", (void**)&EE_ExpressivGetTrainingTime, Dylib::Import::cMangled },
  { "EE_ExpressivGetTrainedSignatureActions", (void**)&EE_ExpressivGetTrainedSignatureActions, Dylib::Import::cMangled },
  { "EE_ExpressivGetTrainedSignatureAvailable", (void**)&EE_ExpressivGetTrainedSignatureAvailable, Dylib::Import::cMangled },
  { "EE_ExpressivSetSignatureType", (void**)&EE_ExpressivSetSignatureType, Dylib::Import::cMangled },
  { "EE_ExpressivGetSignatureType", (void**)&EE_ExpressivGetSignatureType, Dylib::Import::cMangled },
  { "EE_CognitivSetActiveActions", (void**)&EE_CognitivSetActiveActions, Dylib::Import::cMangled },
  { "EE_CognitivGetActiveActions", (void**)&EE_CognitivGetActiveActions, Dylib::Import::cMangled },
  { "EE_CognitivGetTrainingTime", (void**)&EE_CognitivGetTrainingTime, Dylib::Import::cMangled },
  { "EE_CognitivSetTrainingControl", (void**)&EE_CognitivSetTrainingControl, Dylib::Import::cMangled },
  { "EE_CognitivSetTrainingAction", (void**)&EE_CognitivSetTrainingAction, Dylib::Import::cMangled },
  { "EE_CognitivGetTrainingAction", (void**)&EE_CognitivGetTrainingAction, Dylib::Import::cMangled },
  { "EE_CognitivGetTrainedSignatureActions", (void**)&EE_CognitivGetTrainedSignatureActions, Dylib::Import::cMangled },
  { "EE_CognitivGetOverallSkillRating", (void**)&EE_CognitivGetOverallSkillRating, Dylib::Import::cMangled },
  { "EE_CognitivGetActionSkillRating", (void**)&EE_CognitivGetActionSkillRating, Dylib::Import::cMangled },
  { "EE_CognitivSetActivationLevel", (void**)&EE_CognitivSetActivationLevel, Dylib::Import::cMangled },
  { "EE_CognitivSetActionSensitivity", (void**)&EE_CognitivSetActionSensitivity, Dylib::Import::cMangled },
  { "EE_CognitivGetActivationLevel", (void**)&EE_CognitivGetActivationLevel, Dylib::Import::cMangled },
  { "EE_CognitivGetActionSensitivity", (void**)&EE_CognitivGetActionSensitivity, Dylib::Import::cMangled },
  { "EE_CognitivStartSamplingNeutral", (void**)&EE_CognitivStartSamplingNeutral, Dylib::Import::cMangled },
  { "EE_CognitivStopSamplingNeutral", (void**)&EE_CognitivStopSamplingNeutral, Dylib::Import::cMangled },
  { "EE_CognitivSetSignatureCaching", (void**)&EE_CognitivSetSignatureCaching, Dylib::Import::cMangled },
  { "EE_CognitivGetSignatureCaching", (void**)&EE_CognitivGetSignatureCaching, Dylib::Import::cMangled },
  { "EE_CognitivSetSignatureCacheSize", (void**)&EE_CognitivSetSignatureCacheSize, Dylib::Import::cMangled },
  { "EE_CognitivGetSignatureCacheSize", (void**)&EE_CognitivGetSignatureCacheSize, Dylib::Import::cMangled },
  { "EE_HeadsetGetSensorDetails", (void**)&EE_HeadsetGetSensorDetails, Dylib::Import::cMangled },
  { "EE_HardwareGetVersion", (void**)&EE_HardwareGetVersion, Dylib::Import::cMangled },
  { "EE_SoftwareGetVersion", (void**)&EE_SoftwareGetVersion, Dylib::Import::cMangled },
  { "EE_HeadsetGetGyroDelta", (void**)&EE_HeadsetGetGyroDelta, Dylib::Import::cMangled },
  { "EE_HeadsetGyroRezero", (void**)&EE_HeadsetGyroRezero, Dylib::Import::cMangled },
  { "EE_OptimizationParamCreate", (void**)&EE_OptimizationParamCreate, Dylib::Import::cMangled },
  { "EE_OptimizationParamFree", (void**)&EE_OptimizationParamFree, Dylib::Import::cMangled },
  { "EE_OptimizationEnable", (void**)&EE_OptimizationEnable, Dylib::Import::cMangled },
  { "EE_OptimizationIsEnabled", (void**)&EE_OptimizationIsEnabled, Dylib::Import::cMangled },
  { "EE_OptimizationDisable", (void**)&EE_OptimizationDisable, Dylib::Import::cMangled },
  { "EE_OptimizationGetParam", (void**)&EE_OptimizationGetParam, Dylib::Import::cMangled },
  { "EE_OptimizationGetVitalAlgorithm", (void**)&EE_OptimizationGetVitalAlgorithm, Dylib::Import::cMangled },
  { "EE_OptimizationSetVitalAlgorithm", (void**)&EE_OptimizationSetVitalAlgorithm, Dylib::Import::cMangled },
  { "EE_ResetDetection", (void**)&EE_ResetDetection, Dylib::Import::cMangled },
  { "EE_DataCreate", (void**)&EE_DataCreate, Dylib::Import::cMangled },
  { "EE_DataFree", (void**)&EE_DataFree, Dylib::Import::cMangled },
  { "EE_DataUpdateHandle", (void**)&EE_DataUpdateHandle, Dylib::Import::cMangled },
  { "EE_DataGet", (void**)&EE_DataGet, Dylib::Import::cMangled },
  { "EE_DataGetNumberOfSample", (void**)&EE_DataGetNumberOfSample, Dylib::Import::cMangled },
  { "EE_DataSetBufferSizeInSec", (void**)&EE_DataSetBufferSizeInSec, Dylib::Import::cMangled },
  { "EE_DataGetBufferSizeInSec", (void**)&EE_DataGetBufferSizeInSec, Dylib::Import::cMangled },
  { "EE_DataAcquisitionEnable", (void**)&EE_DataAcquisitionEnable, Dylib::Import::cMangled },
  { "EE_DataAcquisitionIsEnabled", (void**)&EE_DataAcquisitionIsEnabled, Dylib::Import::cMangled },
  { "EE_DataSetSychronizationSignal", (void**)&EE_DataSetSychronizationSignal, Dylib::Import::cMangled },
  { "EE_DataSetMarker", (void**)&EE_DataSetMarker, Dylib::Import::cMangled },
  { "EE_DataGetSamplingRate", (void**)&EE_DataGetSamplingRate, Dylib::Import::cMangled },
  { 0, 0, 0 }
};

// Here you may specify a custom error message to be displayed when the library cannot be found.
static const char* notFoundMsg = "";
// Here you may specify an URL to some local or remote help resource.
static const char* notFoundURL = "";
RegisterDylib( edk, imports, notFoundMsg, notFoundURL );

