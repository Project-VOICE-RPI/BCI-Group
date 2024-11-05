
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 11 12:17:23 2004
 */
/* Compiler settings for C:\development\Versions\NervusSDK33\FileAccessSDK33\FileAccess3.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAsciiWrite,0xB0355642,0x4646,0x4039,0x92,0xE0,0x69,0xE7,0x97,0x47,0x0B,0x71);


MIDL_DEFINE_GUID(IID, IID_IFileRead3,0xF5AEC09C,0xC032,0x49d7,0x8E,0xDA,0x52,0x2A,0x64,0xE2,0x28,0x85);


MIDL_DEFINE_GUID(IID, IID_IFileWrite3,0x87550C7F,0x43DB,0x465d,0xBF,0x77,0x9B,0xE0,0xEF,0x74,0xDC,0x08);


MIDL_DEFINE_GUID(IID, IID_IEegStorage,0xDDE93137,0xF71D,0x4e69,0x85,0xD0,0x6D,0x46,0x97,0x4E,0x14,0x78);


MIDL_DEFINE_GUID(IID, IID_IEegSegments,0xA82442C0,0x8C14,0x46ac,0x9E,0xD5,0x27,0xC2,0xD2,0x46,0x9A,0xB8);


MIDL_DEFINE_GUID(IID, IID_IInitEegSegments,0x1874E9C2,0x2380,0x4af3,0x9D,0x37,0x67,0x26,0xE9,0x74,0x8B,0x89);


MIDL_DEFINE_GUID(IID, IID_IEegData,0x35838D50,0xD0E7,0x41a3,0x9A,0xA0,0xE3,0x21,0x5F,0x4D,0x7A,0x2B);


MIDL_DEFINE_GUID(IID, IID_IInitEegData,0x98F4BD79,0xCE69,0x43fb,0xB5,0x61,0xA3,0x28,0xC8,0x3C,0x68,0xBF);


MIDL_DEFINE_GUID(IID, IID_IUserEvent,0xBFD5C4C5,0x2835,0x486a,0xA3,0x01,0x1C,0xE2,0x8D,0x61,0x46,0xC1);


MIDL_DEFINE_GUID(IID, IID_IEventWrapper,0x1E2F536C,0xA286,0x4d6b,0xA7,0x6E,0xE0,0x64,0xAD,0xE6,0x12,0xFA);


MIDL_DEFINE_GUID(IID, IID_IInitEventWrapper,0x26228DE0,0x54CE,0x4e79,0xBF,0x01,0x05,0x2B,0xBD,0xF2,0x12,0x77);


MIDL_DEFINE_GUID(IID, IID_IUserEvent2,0xB5D85332,0x1313,0x4fe5,0x8B,0xA9,0x19,0x59,0xDB,0x24,0xD1,0x2A);


MIDL_DEFINE_GUID(IID, IID_IUserEvents,0x0272DEF0,0x57BD,0x4841,0xBD,0x55,0x3E,0xF6,0xF9,0x6C,0xA0,0x73);


MIDL_DEFINE_GUID(IID, IID_IEventUsers,0x337E0E77,0xE7EF,0x4c3b,0x97,0x47,0x62,0x53,0x2C,0xDB,0xCD,0xE0);


MIDL_DEFINE_GUID(IID, IID_ITrendWrite,0x8AB24A6B,0x623B,0x46af,0x81,0x91,0x07,0xB9,0x9A,0xDD,0xCA,0xE3);


MIDL_DEFINE_GUID(IID, IID_ITrendRead,0xD88A5F33,0x023B,0x44ea,0x8A,0xB1,0xBF,0x22,0x3E,0xF5,0x24,0x14);


MIDL_DEFINE_GUID(IID, IID_IImpedanceEvent,0x67156C30,0x82C8,0x44df,0x8F,0x14,0x94,0x6F,0xD1,0x05,0x66,0x5E);


MIDL_DEFINE_GUID(IID, IID_IEventWrapperProxy,0x0B96E985,0x0462,0x404f,0xBC,0x3F,0xCE,0xD3,0x4A,0x6D,0x26,0x36);


MIDL_DEFINE_GUID(IID, IID_ISegments,0xF8032A01,0x9352,0x47fa,0xB2,0xDE,0x9B,0xE9,0x7B,0x3B,0x44,0x14);


MIDL_DEFINE_GUID(IID, IID_IStorageMan,0x18F60508,0x0347,0x4884,0x9D,0x0C,0xF1,0x30,0x7B,0x8C,0x02,0x9E);


MIDL_DEFINE_GUID(IID, IID_IStorageManEx,0x8EEAE4ED,0x724F,0x4034,0xBA,0x93,0x7A,0x56,0xD9,0xC2,0x93,0xCD);


MIDL_DEFINE_GUID(IID, IID_IStorageManProxy,0x0329CCF6,0x78E6,0x489a,0xAC,0x02,0x91,0xCF,0x59,0x2A,0x59,0x34);


MIDL_DEFINE_GUID(IID, IID_IEventWrapperCopy,0xCC5B5C73,0x11CE,0x47b2,0x8E,0xEB,0x32,0x38,0x27,0xAC,0xC9,0x4F);


MIDL_DEFINE_GUID(IID, IID_ISleepData,0xE64B2F6D,0x7F8E,0x4686,0xA1,0xB4,0x65,0x81,0x32,0xA0,0x11,0xAB);


MIDL_DEFINE_GUID(IID, LIBID_FILEACCESS3Lib,0x065D5899,0xE843,0x4fee,0xB5,0xB7,0x7C,0x63,0xED,0xEB,0xC3,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_FileWrite3,0xBFB9D16B,0x512D,0x47e6,0xAD,0x85,0x63,0x2B,0x0F,0x39,0xFE,0xB3);


MIDL_DEFINE_GUID(CLSID, CLSID_FileRead3,0xBE3AC01B,0x934F,0x4fbb,0x98,0xE6,0xC9,0x77,0x71,0x0F,0x16,0x27);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapper,0xD02AEFCC,0xB0D0,0x4877,0x8A,0xA1,0x14,0x91,0x82,0xC9,0x19,0x4B);


MIDL_DEFINE_GUID(CLSID, CLSID_UserEvent,0x28FC5B18,0x24BA,0x48a8,0x9F,0x7E,0x23,0x0B,0x10,0xF9,0x6E,0x8A);


MIDL_DEFINE_GUID(CLSID, CLSID_TrendWrite,0x61AE14D0,0xD711,0x4e0b,0x96,0xF7,0xBD,0x66,0x49,0x54,0x71,0xBD);


MIDL_DEFINE_GUID(CLSID, CLSID_TrendRead,0x2290B46F,0x421A,0x4149,0x9E,0x36,0x06,0x40,0xBA,0x80,0xA2,0x30);


MIDL_DEFINE_GUID(CLSID, CLSID_ImpedanceEvent,0xCF4F7DEC,0xFE6E,0x454b,0xB0,0x74,0x44,0x2D,0x34,0xC9,0x1C,0x86);


MIDL_DEFINE_GUID(CLSID, CLSID_EegData,0x77E268AC,0x1AEC,0x440a,0xBE,0x64,0x19,0x21,0x92,0x54,0x3F,0x16);


MIDL_DEFINE_GUID(CLSID, CLSID_EegSegments,0x38979206,0x3556,0x426c,0x94,0x23,0x64,0x12,0x08,0xC0,0x65,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapperProxy,0x7F0B08D2,0xF593,0x4ea1,0x82,0xBE,0x29,0xAE,0x94,0x6C,0x1A,0xDA);


MIDL_DEFINE_GUID(CLSID, CLSID_SleepData,0x788BA2F9,0x3A62,0x43c7,0xA4,0xF5,0x3B,0x48,0xE5,0xBF,0x0C,0x61);


MIDL_DEFINE_GUID(CLSID, CLSID_AsciiWrite,0x9A0F9B69,0xDD00,0x4592,0x91,0x92,0x43,0xDA,0xB8,0x8C,0xD0,0xE8);


MIDL_DEFINE_GUID(CLSID, CLSID_Segments,0xA9BA61C9,0x829C,0x4b9b,0xB0,0x6F,0x77,0x1C,0x04,0x23,0x04,0x7E);


MIDL_DEFINE_GUID(CLSID, CLSID_StorageMan,0x57DDCF4E,0xD7BF,0x4446,0x95,0x7D,0x1F,0x45,0xB9,0xD8,0xCC,0x62);


MIDL_DEFINE_GUID(CLSID, CLSID_StorageManProxy,0x549EA9FA,0x3EC9,0x4325,0xB3,0xB1,0x29,0x03,0x9F,0x11,0x8A,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapperCopy,0xF1E41323,0x8281,0x439c,0x8B,0x23,0x9A,0x7D,0xD5,0xA3,0xA6,0x5F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 11 12:17:23 2004
 */
/* Compiler settings for C:\development\Versions\NervusSDK33\FileAccessSDK33\FileAccess3.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAsciiWrite,0xB0355642,0x4646,0x4039,0x92,0xE0,0x69,0xE7,0x97,0x47,0x0B,0x71);


MIDL_DEFINE_GUID(IID, IID_IFileRead3,0xF5AEC09C,0xC032,0x49d7,0x8E,0xDA,0x52,0x2A,0x64,0xE2,0x28,0x85);


MIDL_DEFINE_GUID(IID, IID_IFileWrite3,0x87550C7F,0x43DB,0x465d,0xBF,0x77,0x9B,0xE0,0xEF,0x74,0xDC,0x08);


MIDL_DEFINE_GUID(IID, IID_IEegStorage,0xDDE93137,0xF71D,0x4e69,0x85,0xD0,0x6D,0x46,0x97,0x4E,0x14,0x78);


MIDL_DEFINE_GUID(IID, IID_IEegSegments,0xA82442C0,0x8C14,0x46ac,0x9E,0xD5,0x27,0xC2,0xD2,0x46,0x9A,0xB8);


MIDL_DEFINE_GUID(IID, IID_IInitEegSegments,0x1874E9C2,0x2380,0x4af3,0x9D,0x37,0x67,0x26,0xE9,0x74,0x8B,0x89);


MIDL_DEFINE_GUID(IID, IID_IEegData,0x35838D50,0xD0E7,0x41a3,0x9A,0xA0,0xE3,0x21,0x5F,0x4D,0x7A,0x2B);


MIDL_DEFINE_GUID(IID, IID_IInitEegData,0x98F4BD79,0xCE69,0x43fb,0xB5,0x61,0xA3,0x28,0xC8,0x3C,0x68,0xBF);


MIDL_DEFINE_GUID(IID, IID_IUserEvent,0xBFD5C4C5,0x2835,0x486a,0xA3,0x01,0x1C,0xE2,0x8D,0x61,0x46,0xC1);


MIDL_DEFINE_GUID(IID, IID_IEventWrapper,0x1E2F536C,0xA286,0x4d6b,0xA7,0x6E,0xE0,0x64,0xAD,0xE6,0x12,0xFA);


MIDL_DEFINE_GUID(IID, IID_IInitEventWrapper,0x26228DE0,0x54CE,0x4e79,0xBF,0x01,0x05,0x2B,0xBD,0xF2,0x12,0x77);


MIDL_DEFINE_GUID(IID, IID_IUserEvent2,0xB5D85332,0x1313,0x4fe5,0x8B,0xA9,0x19,0x59,0xDB,0x24,0xD1,0x2A);


MIDL_DEFINE_GUID(IID, IID_IUserEvents,0x0272DEF0,0x57BD,0x4841,0xBD,0x55,0x3E,0xF6,0xF9,0x6C,0xA0,0x73);


MIDL_DEFINE_GUID(IID, IID_IEventUsers,0x337E0E77,0xE7EF,0x4c3b,0x97,0x47,0x62,0x53,0x2C,0xDB,0xCD,0xE0);


MIDL_DEFINE_GUID(IID, IID_ITrendWrite,0x8AB24A6B,0x623B,0x46af,0x81,0x91,0x07,0xB9,0x9A,0xDD,0xCA,0xE3);


MIDL_DEFINE_GUID(IID, IID_ITrendRead,0xD88A5F33,0x023B,0x44ea,0x8A,0xB1,0xBF,0x22,0x3E,0xF5,0x24,0x14);


MIDL_DEFINE_GUID(IID, IID_IImpedanceEvent,0x67156C30,0x82C8,0x44df,0x8F,0x14,0x94,0x6F,0xD1,0x05,0x66,0x5E);


MIDL_DEFINE_GUID(IID, IID_IEventWrapperProxy,0x0B96E985,0x0462,0x404f,0xBC,0x3F,0xCE,0xD3,0x4A,0x6D,0x26,0x36);


MIDL_DEFINE_GUID(IID, IID_ISegments,0xF8032A01,0x9352,0x47fa,0xB2,0xDE,0x9B,0xE9,0x7B,0x3B,0x44,0x14);


MIDL_DEFINE_GUID(IID, IID_IStorageMan,0x18F60508,0x0347,0x4884,0x9D,0x0C,0xF1,0x30,0x7B,0x8C,0x02,0x9E);


MIDL_DEFINE_GUID(IID, IID_IStorageManEx,0x8EEAE4ED,0x724F,0x4034,0xBA,0x93,0x7A,0x56,0xD9,0xC2,0x93,0xCD);


MIDL_DEFINE_GUID(IID, IID_IStorageManProxy,0x0329CCF6,0x78E6,0x489a,0xAC,0x02,0x91,0xCF,0x59,0x2A,0x59,0x34);


MIDL_DEFINE_GUID(IID, IID_IEventWrapperCopy,0xCC5B5C73,0x11CE,0x47b2,0x8E,0xEB,0x32,0x38,0x27,0xAC,0xC9,0x4F);


MIDL_DEFINE_GUID(IID, IID_ISleepData,0xE64B2F6D,0x7F8E,0x4686,0xA1,0xB4,0x65,0x81,0x32,0xA0,0x11,0xAB);


MIDL_DEFINE_GUID(IID, LIBID_FILEACCESS3Lib,0x065D5899,0xE843,0x4fee,0xB5,0xB7,0x7C,0x63,0xED,0xEB,0xC3,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_FileWrite3,0xBFB9D16B,0x512D,0x47e6,0xAD,0x85,0x63,0x2B,0x0F,0x39,0xFE,0xB3);


MIDL_DEFINE_GUID(CLSID, CLSID_FileRead3,0xBE3AC01B,0x934F,0x4fbb,0x98,0xE6,0xC9,0x77,0x71,0x0F,0x16,0x27);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapper,0xD02AEFCC,0xB0D0,0x4877,0x8A,0xA1,0x14,0x91,0x82,0xC9,0x19,0x4B);


MIDL_DEFINE_GUID(CLSID, CLSID_UserEvent,0x28FC5B18,0x24BA,0x48a8,0x9F,0x7E,0x23,0x0B,0x10,0xF9,0x6E,0x8A);


MIDL_DEFINE_GUID(CLSID, CLSID_TrendWrite,0x61AE14D0,0xD711,0x4e0b,0x96,0xF7,0xBD,0x66,0x49,0x54,0x71,0xBD);


MIDL_DEFINE_GUID(CLSID, CLSID_TrendRead,0x2290B46F,0x421A,0x4149,0x9E,0x36,0x06,0x40,0xBA,0x80,0xA2,0x30);


MIDL_DEFINE_GUID(CLSID, CLSID_ImpedanceEvent,0xCF4F7DEC,0xFE6E,0x454b,0xB0,0x74,0x44,0x2D,0x34,0xC9,0x1C,0x86);


MIDL_DEFINE_GUID(CLSID, CLSID_EegData,0x77E268AC,0x1AEC,0x440a,0xBE,0x64,0x19,0x21,0x92,0x54,0x3F,0x16);


MIDL_DEFINE_GUID(CLSID, CLSID_EegSegments,0x38979206,0x3556,0x426c,0x94,0x23,0x64,0x12,0x08,0xC0,0x65,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapperProxy,0x7F0B08D2,0xF593,0x4ea1,0x82,0xBE,0x29,0xAE,0x94,0x6C,0x1A,0xDA);


MIDL_DEFINE_GUID(CLSID, CLSID_SleepData,0x788BA2F9,0x3A62,0x43c7,0xA4,0xF5,0x3B,0x48,0xE5,0xBF,0x0C,0x61);


MIDL_DEFINE_GUID(CLSID, CLSID_AsciiWrite,0x9A0F9B69,0xDD00,0x4592,0x91,0x92,0x43,0xDA,0xB8,0x8C,0xD0,0xE8);


MIDL_DEFINE_GUID(CLSID, CLSID_Segments,0xA9BA61C9,0x829C,0x4b9b,0xB0,0x6F,0x77,0x1C,0x04,0x23,0x04,0x7E);


MIDL_DEFINE_GUID(CLSID, CLSID_StorageMan,0x57DDCF4E,0xD7BF,0x4446,0x95,0x7D,0x1F,0x45,0xB9,0xD8,0xCC,0x62);


MIDL_DEFINE_GUID(CLSID, CLSID_StorageManProxy,0x549EA9FA,0x3EC9,0x4325,0xB3,0xB1,0x29,0x03,0x9F,0x11,0x8A,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_EventWrapperCopy,0xF1E41323,0x8281,0x439c,0x8B,0x23,0x9A,0x7D,0xD5,0xA3,0xA6,0x5F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/
