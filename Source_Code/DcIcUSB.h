//==============================================================================
//
// [File Name] DcIcUSB.h
//
// [Outline] DcIcUSB.DLL Header File
//
// [Update history]  [New]     Mon Nov 25 13:53:52 2013
//
//
//==============================================================================

#pragma once

#ifdef	__cplusplus
extern	"C" {
#endif

#ifndef	_DLLFUNC
#define _DLLFUNC	__declspec(dllimport)
#endif

#ifndef	_DLLSTDCALL
#define	_DLLSTDCALL	_stdcall
#endif


//---------------------------------------------------------------------------
// [Error Code]
//---------------------------------------------------------------------------
#define	DcIc_ERROR_GOOD				( 0 )							// There is no error (normal termination)
#define	DcIc_ERROR_UNKNOWN			( 1 )							// Unknown
#define	DcIc_ERROR_INITIALIZE		( 2 )							// Initialization is not done
#define	DcIc_ERROR_PARAMETER		( 3 )							// The parameter is illegal
#define	DcIc_ERROR_CONNECT			( 4 )							// The error occurred by the device connection
#define	DcIc_ERROR_DISCONNECT		( 5 )							// The error occurred by the device disconnection
#define	DcIc_ERROR_SEND				( 6 )							// This control doesn't correspond
#define	DcIc_ERROR_RECEIVE			( 7 )							// This control doesn't correspond
#define	DcIc_ERROR_STOPRECEIVE		( 8 )							// Fails in the data receive
#define	DcIc_ERROR_CLOSE			( 9 )							// Fails in the close
#define	DcIc_ERROR_ALLOC			( 10 )							// The memory allocation error occurred
#define	DcIc_ERROR_CAPTURE			( 11 )							// Fails in the data measurement
#define	DcIc_ERROR_TIMEOUT			( 12 )							// Timeout error

#define	DcIc_ERROR_WRITEPROTECT		( 20 )							//
#define DcIc_ERROR_ILLEGAL_ACCESS	( 21 )							//
#define DcIc_ERROR_ILLEGAL_ADDR		( 22 )							//
#define DcIc_ERROR_ILLEGAL_VALUE	( 23 )							// The parameter is illegal

#define DcIc_WAITSTATUS_ERROR		( 0 )							// The error occured
#define DcIc_WAITSTATUS_CAPTURING	( 1 )							// During a measurement
#define DcIc_WAITSTATUS_CAPTURED	( 2 )							// Finished with a measurement

//---------------------------------------------------------------------------
// [Default value]
//---------------------------------------------------------------------------
#define DcIc_TIMEOUT_MSEC_CMDRECV	(100)
#define DcIc_TIMEOUT_MSEC_DATARECV	(3000)

//---------------------------------------------------------------------------
// Prototype declaration
//----------------------------------------------------------------------------
typedef BOOL  (_DLLSTDCALL *_DcIc_Initialize)();
typedef BOOL  (_DLLSTDCALL *_DcIc_Terminate)();
typedef BOOL  (_DLLSTDCALL *_DcIc_CreateDeviceInfo)( LONG* );
typedef INT   (_DLLSTDCALL *_DcIc_Connect)( UINT );
typedef BOOL  (_DLLSTDCALL *_DcIc_Disconnect)( INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_Capture)( INT, void*, UINT );
typedef INT   (_DLLSTDCALL *_DcIc_Wait)( INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_Abort)( INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetHWRevision)( INT, BYTE* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetFWRevision)( INT, BYTE* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetSerialNumber)( INT, char* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetCameraNumber)( INT, char* );
typedef BOOL  (_DLLSTDCALL *_DcIc_Reset)( INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_StoreParameter)( INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_LoadParameter)(INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetLEDMode)( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetLEDMode)( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetGain)( INT, BYTE* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetGain)( INT, BYTE );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetTriggerMode)( INT, BYTE* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetTriggerMode)( INT, BYTE );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetTriggerPolarity)( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetTriggerPolarity)( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetTriggerEffective)( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetTriggerEffective)( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetExposureTime)( INT, DWORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetExposureTime)( INT, DWORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetLineTime)( INT, DWORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetLineTime)( INT, DWORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetHorizontalPixel)( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetHorizontalPixel)( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetVerticalPixel)( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetVerticalPixel)( INT, WORD );
typedef DWORD (_DLLSTDCALL *_DcIc_GetLastError)();
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOffset )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOffset )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetBurstCount )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetBurstCount )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulseMode )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulseMode )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulsePolarity )( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulsePolarity )( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulseCount )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulseCount )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulseAssert )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulseAssert )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulseDeassert )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulseDeassert )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetOutPulseDelay )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetOutPulseDelay )( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetDLLVersion )( char* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetDriverVersion )( char* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetCommandTimeout )( INT, INT* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetCommandTimeout )( INT, INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetDataTimeout )( INT, INT* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetDataTimeout )( INT, INT );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetSensitivity )( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetSensitivity )( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetCoolingControl )( INT, BOOL* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetCoolingControl )( INT, BOOL );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetTemperature1) ( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetTemperature2 )( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetMPPMode )( INT, BYTE* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetMPPMode )( INT, BYTE );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetHorizontalBinning)( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetHorizontalBinning)( INT, WORD );
typedef BOOL  (_DLLSTDCALL *_DcIc_GetVerticalBinning)( INT, WORD* );
typedef BOOL  (_DLLSTDCALL *_DcIc_SetVerticalBinning)( INT, WORD );

#define DCIC_INITIALIZE				_T( "DcIc_Initialize" )
#define DCIC_TERMINATE				_T( "DcIc_Terminate" )
#define DCIC_CREATEDEVICEINFO		_T( "DcIc_CreateDeviceInfo" )
#define DCIC_CONNECT				_T( "DcIc_Connect" )
#define DCIC_DISCONNECT				_T( "DcIc_Disconnect" )
#define DCIC_CAPTURE				_T( "DcIc_Capture" )
#define DCIC_WAIT					_T( "DcIc_Wait" )
#define DCIC_ABORT					_T( "DcIc_Abort" )
#define DCIC_GETHWREVISION			_T( "DcIc_GetHWRevision" )
#define DCIC_GETFWREVISION			_T( "DcIc_GetFWRevision" )
#define DCIC_GETSERIALNUMBER		_T( "DcIc_GetSerialNumber" )
#define DCIC_GETCAMERANUMBER		_T( "DcIc_GetCameraNumber" )
#define DCIC_RESET					_T( "DcIc_Reset" )
#define DCIC_STOREPARAMETER			_T( "DcIc_StoreParameter" )
#define DCIC_LOADPARAMETER			_T( "DcIc_LoadParameter" )
#define DCIC_GETLEDMODE				_T( "DcIc_GetLEDMode" )
#define DCIC_SETLEDMODE				_T( "DcIc_SetLEDMode" )
#define DCIC_GETGAIN				_T( "DcIc_GetGain" )
#define DCIC_SETGAIN				_T( "DcIc_SetGain" )
#define DCIC_GETTRIGGERMODE			_T( "DcIc_GetTriggerMode" )
#define DCIC_SETTRIGGERMODE			_T( "DcIc_SetTriggerMode" )
#define DCIC_GETTRIGGERPOLARITY		_T( "DcIc_GetTriggerPolarity" )
#define DCIC_SETTRIGGERPOLARITY		_T( "DcIc_SetTriggerPolarity" )
#define DCIC_GETTRIGGEREFFECTIVE	_T( "DcIc_GetTriggerEffective" )
#define DCIC_SETTRIGGEREFFECTIVE	_T( "DcIc_SetTriggerEffective" )
#define DCIC_GETSTARTPULSETIME		_T( "DcIc_GetStartPulseTime" )
#define DCIC_SETSTARTPULSETIME		_T( "DcIc_SetStartPulseTime" )
#define DCIC_GETLINETIEM			_T( "DcIc_GetLineTime" )
#define DCIC_SETLINETIEM			_T( "DcIc_SetLineTime" )
#define DCIC_GETHORIZONTALPIXEL		_T( "DcIc_GetHorizontalPixel" )
#define DCIC_SETHORIZONTALPIXEL		_T( "DcIc_SetHorizontalPixel" )
#define DCIC_GETVERTICALPIXEL		_T( "DcIc_GetVerticalPixel" )
#define DCIC_SETVERTICALPIXEL		_T( "DcIc_SetVerticalPixel" )
#define DCIC_GETLASTERROR			_T( "DcIc_GetLastError" )
#define DCIC_GETOFFSET				_T( "DcIc_GetOffset" )
#define DCIC_SETOFFSET				_T( "DcIc_SetOffset" )
#define DCIC_GETBURSTCOUNT			_T( "DcIc_GetBurstCount" )
#define DCIC_SETBURSTCOUNT			_T( "DcIc_SetBurstCount" )
#define DCIC_GETOUTPULSEMODE		_T( "DcIc_GetOutPulseMode" )
#define DCIC_SETOUTPULSEMODE		_T( "DcIc_SetOutPulseMode" )
#define DCIC_GETOUTPULSEPOLARITY	_T( "DcIc_GetOutPulsePolarity" )
#define DCIC_SETOUTPULSEPOLARITY	_T( "DcIc_SetOutPulsePolarity" )
#define DCIC_GETOUTPULSECOUNT		_T( "DcIc_GetOutPulseCount" )
#define DCIC_SETOUTPULSECOUNT		_T( "DcIc_SetOutPulseCount" )
#define DCIC_GETOUTPULSEASSERT		_T( "DcIc_GetOutPulseAssert" )
#define DCIC_SETOUTPULSEASSERT		_T( "DcIc_SetOutPulseAssert" )
#define DCIC_GETOUTPULSEDEASSERT	_T( "DcIc_GetOutPulseDeassert" )
#define DCIC_SETOUTPULSEDEASSERT	_T( "DcIc_SetOutPulseDeassert" )
#define DCIC_GETOUTPULSEDELAY		_T( "DcIc_GetOutPulseDelay" )
#define DCIC_SETOUTPULSEDELAY		_T( "DcIc_SetOutPulseDelay" )
#define DCIC_GETDLLVERSION			_T( "DcIc_GetDLLVersion" )
#define DCIC_GETDRIVERVERSION		_T( "DcIc_GetDriverVersion" )
#define DCIC_GETCOMMANDTIMEOUT		_T( "DcIc_GetCommandTimeout" )
#define DCIC_SETCOMMANDTIMEOUT		_T( "DcIc_SetCommandTimeout" )
#define DCIC_GETDATATIMEOUT			_T( "DcIc_GetDataTimeout" )
#define DCIC_SETDATATIMEOUT			_T( "DcIc_SetDataTimeout" )
#define DCIC_GETSENSITIVITY			_T( "DcIc_GetSensitivity" )
#define DCIC_SETSENSITIVITY			_T( "DcIc_SetSensitivity" )
#define DCIC_GETCOOLINGCONTROL		_T( "DcIc_GetCoolingControl" )
#define DCIC_SETCOOLINGCONTROL		_T( "DcIc_SetCoolingControl" )
#define DCIC_GETTEMPERATURE1		_T( "DcIc_GetTemperature1" )
#define DCIC_GETTEMPERATURE2		_T( "DcIc_GetTemperature2" )
#define DCIC_GETMPPMODE				_T( "DcIc_GetMPPMode" )
#define DCIC_SETMPPMODE				_T( "DcIc_SetMPPMode" )
#define DCIC_GETHORIZONTALBINNING	_T( "DcIc_GetHorizontalBinning" )
#define DCIC_SETHORIZONTALBINNING	_T( "DcIc_SetHorizontalBinning" )
#define DCIC_GETVERTICALBINNING		_T( "DcIc_GetVerticalBinning" )
#define DCIC_SETVERTICALBINNING		_T( "DcIc_SetVerticalBinning" )

//-----------------------------------------------------------------------------
// Function name : DcIc_Initialize
//
// Summry		 : Initialize library
//
// Argument		 : none
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Initialize( );

//-----------------------------------------------------------------------------
// Function name : DcIc_Terminate
//
// Summry		 : Terminate library
//
// Argument		 : none
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Terminate( );

//-----------------------------------------------------------------------------
// Function name : DcIc_CreateDeviceInfo
//
// Summry		 : Create hardware information
//
// Argument		 : [o] : plCount -> Count of informations are created
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_CreateDeviceInfo( long* plCount );

//-----------------------------------------------------------------------------
// Function name : DcIc_Connect
//
// Summry		 : Connect hardware
//
// Argument		 : [i] : nIndex -> Index for target hardware
//
// Return		 : DeviceID
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC INT _DLLSTDCALL DcIc_Connect( UINT nIndex );

//-----------------------------------------------------------------------------
// Function name : DcIc_Disconnect
//
// Summry		 : Disconnect hardware
//
// Argument		 : [i] nDeviceID -> Hardware ID to disconnect
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Disconnect( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_Capture
//
// Summry		 : Capture frames
//
// Argument		 : [i] nDeviceID -> Hardware ID
//				 : [i] pMeasBuffer -> Data buffer
//				 : [i] nFrameNum -> Capture frame count
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Capture( INT nDeviceID, void *pMeasBuffer, UINT uCapBytesFrameNum );

//-----------------------------------------------------------------------------
// Function name : DcIc_Wait
//
// Summry		 : Capture frames
//
// Argument		 : [i] nDeviceID -> Hardware ID
//
// Return		 : status
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC INT _DLLSTDCALL DcIc_Wait( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_Abort
//
// Summry		 : Abort capture
//
// Argument		 : [i] nDeviceID -> Hardware ID
//
// Return		 : status (TRUE->Success)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Abort( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetHWRevision
//
// Summry		 : Get hardware revision number by Get access
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pRevision -> Revision
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetHWRevision( INT nDeviceID, BYTE* pRevision );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetFWRevision
//
// Summry		 : Get firmware revision number by Get access
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pRevision -> Revision
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetFWRevision( INT nDeviceID, BYTE* pRevision );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetSerialNumber
//
// Summry		 : Get serial number of driver circuit
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pData -> Serial number
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetSerialNumber( INT nDeviceID, char* pData );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetCameraNumber
//
// Summry		 : Get model number of driver circuit
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pData -> Serial number
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetCameraNumber( INT nDeviceID, char* pData );

//-----------------------------------------------------------------------------
// Function name : DcIc_Reset
//
// Summry		 : Soft reset of a module
//
// Argument		 : [i] nDeviceID -> Hardware ID
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_Reset( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_StoreParameter
//
// Summry		 : Save parameter in flash memory
//
// Argument		 : [i] nDeviceID -> Hardware ID
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_StoreParameter( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_LoadParameter
//
// Summry		 : Load parameter from flash memory
//
// Argument		 : [i] nDeviceID -> Hardware ID
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_LoadParameter( INT nDeviceID );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetLEDMode
//
// Summry		 : Get that is in state of LED
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbMode -> State of LED ( TRUE : Led on , FALSE : Led off )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetLEDMode( INT nDeviceID, BOOL* pbMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetLEDMode
//
// Summry		 : Set that is in state of LED
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bMode -> State of LED ( TRUE : Led on , FALSE : Led off )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetLEDMode( INT nDeviceID, BOOL bMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetGain
//
// Summry		 : Get that is in gain
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pybGain -> Gain ( TRUE : Low , FALSE : Normal )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetGain( INT nDeviceID, BYTE* pybGain );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetGain
//
// Summry		 : Set that is in gain
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bGain -> Gain ( TRUE : Low , FALSE : Normal )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetGain( INT nDeviceID, BYTE byGain );


//-----------------------------------------------------------------------------
// Function name : DcIc_GetTriggerMode
//
// Summry		 : Trigger mode acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbyMode -> Trigger mode
//									  0 : Internal Sync Mode
//									  1 : Internal Async Mode
//									  2 : External Edge Sync Mode
//									  3 : External Edge Async Mode
//									  4 : External Gate Sync Mode
//									  5 : External Gate Async Mode
//									  6 : External Level Mode//
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetTriggerMode( INT nDeviceID, BYTE* pbyMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetTriggerMode
//
// Summry		 : Trigger mode setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] byMode -> Trigger mode
//									  0 : Internal Sync Mode
//									  1 : Internal Async Mode
//									  2 : External Edge Sync Mode
//									  3 : External Edge Async Mode
//									  4 : External Gate Sync Mode
//									  5 : External Gate Async Mode
//									  6 : External Level Mode//
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetTriggerMode( INT nDeviceID, BYTE byMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetTriggerPolarity
//
// Summry		 : Trigger polarity acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbTiggerPol -> Trigger polarity ( TRUE : High active,  FALSE : Low active )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetTriggerPolarity( INT nDeviceID, BOOL* pbTiggerPol );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetTriggerEffective
//
// Summry		 : Trigger effective acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbTiggerEn  -> Trigger ( TRUE : Enable,  FALSE : Disable )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetTriggerEffective( INT nDeviceID, BOOL* pbTriggerEn );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetTriggerPolarilty
//
// Summry		 : Trigger polarity setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bTiggerPol -> Trigger polarity ( TRUE : High active,  FALSE : Low active )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetTriggerPolarity( INT nDeviceID, BOOL bTiggerPol );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetTriggerEffective
//
// Summry		 : Trigger effective setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bTiggerEn  -> Trigger ( TRUE : Enable,  FALSE : Disable )
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetTriggerEffective( INT nDeviceID, BOOL bTriggerEn );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetStartPulseTime
//
// Summry		 : Sensor cycle value acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pulSensorCycle -> Sensor cycle value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetStartPulseTime( INT nDeviceID, DWORD* pulSensorCycle );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetStartPulseTime
//
// Summry		 : Sensor cycle value setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] ulSensorCycle -> Sensor cycle value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetStartPulseTime( INT nDeviceID, DWORD ulSensorCycle );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetLineTime
//
// Summry		 : Line cycle value acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pulLineTime -> Line time value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetLineTime( INT nDeviceID, DWORD* pulLineTime );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetLineTime										// 48
//
// Summry		 : Line cycle value setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] ulLineTime -> Line time value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetLineTime( INT nDeviceID, DWORD pulLineTime );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetHorizontalPixel
//
// Summry		 : Horizontal pixel size value acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwPixel -> Horizontal pixel size value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetHorizontalPixel( INT nDeviceID, WORD* pwPixel );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetHorizontalPixel
//
// Summry		 : Horizontal pixel size value setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] wPixel -> Horizontal pixel size value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetHorizontalPixel( INT nDeviceID, WORD wPixel );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetVerticalPixel
//
// Summry		 : Vertical pixel size value acquisition is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwPixel -> Vertical pixel size value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetVerticalPixel( INT nDeviceID, WORD* pwPixel );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetVerticalPixel
//
// Summry		 : Vertical pixel size value setting is carried out.
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] wPixel -> Vertical pixel size value
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetVerticalPixel( INT nDeviceID, WORD wPixel );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetLastError
//
// Summry		 : Get last error code
//
// Argument		 : none
//
// Return		 : error code
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC DWORD _DLLSTDCALL DcIc_GetLastError( );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOffset
//
// Summry		 : Get that is in offset
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwOffset
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOffset( INT nDeviceID, WORD* pwOffset );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOffset
//
// Summry		 : Set that is in offset
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] wOffset
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOffset( INT nDeviceID, WORD wOffset );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetBurstCount
//
// Summry		 : Get burst count
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwBurstCount
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetBurstCount( INT nDeviceID, WORD* pwBurstCount );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetBurstCount
//
// Summry		 : Set burst count
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] wBurstCount
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetBurstCount( INT nDeviceID, WORD wBurstCount );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulseMode
//
// Summry		 : Get out pulse mode
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwOutPulseMode
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulseMode( INT nDeviceID, WORD* pwOutPulseMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulseMode
//
// Summry		 : Set out pulse mode
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] wOutPulseMode
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulseMode( INT nDeviceID, WORD wOutPulseMode );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulsePolarity
//
// Summry		 : Get out pulse polarity
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbOutPulsePolarity
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulsePolarity( INT nDeviceID, BOOL* pbOutPulsePolarity );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulsePolarity
//
// Summry		 : Set out pulse  polarity
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bOutPulsePolarity
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulsePolarity( INT nDeviceID, BOOL bOutPulsePolarity );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulseCount
//
// Summry		 : Get out pulse count
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbOutPulseCount
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulseCount( INT nDeviceID, WORD* pwOutPulseCount );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulseCount
//
// Summry		 : Set out pulse count
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] pbOutPulseCount
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulseCount( INT nDeviceID, WORD wOutPulseCount );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulseAssert
//
// Summry		 : Get out pulse assert
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbOutPulseCAssert
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulseAssert( INT nDeviceID, WORD* pwOutPulseAssert );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulseAssert
//
// Summry		 : Set out pulse assert
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bOutPulseAssert
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulseAssert( INT nDeviceID, WORD wOutPulseAssert );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulseDeassert
//
// Summry		 : Get out pulse deassert
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwOutPulseDeassert
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulseDeassert( INT nDeviceID, WORD* pwOutPulseDeassert);

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulseDeassert
//
// Summry		 : Set out pulse deassert
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] bOutPulseDeassert
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulseDeassert( INT nDeviceID, WORD wOutPulseDeassert );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetOutPulseDelay
//
// Summry		 : Get out pulse Delay
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pwOutPulseDelay
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetOutPulseDelay( INT nDeviceID, WORD* pwOutPulseDelay );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetOutPulseDelay
//
// Summry		 : Set out pulse Delay
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] pwOutPulseDelay
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetOutPulseDelay( INT nDeviceID, WORD wOutPulseDelay );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetDLLVersion
//
// Summry		 : Get DLL versin
//
// Argument		 : [o] pData
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetDLLVersion( char* pData );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetDriverVersion
//
// Summry		 : Get driver version
//
// Argument		 : [o] pData
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetDriverVersion( char* pData );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetCommandTimeout
//
// Summry		 : Get command timeout
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pTimeout(ms)
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetCommandTimeout( INT nDeviceID, INT* pTimeout );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetCommandTimeout
//
// Summry		 : Set command timeout
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [i] nTimeout(ms)
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetCommandTimeout( INT nDeviceID, INT nTimeout );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetDataTimeout
//
// Summry		 : Get data timeout
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pTimeout(ms)
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetDataTimeout( INT nDeviceID, INT* pTimeout );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetDataTimeout
//
// Summry		 : Set data timeout
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] nTimeout(ms)
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetDataTimeout( INT nDeviceID, INT nTimeout );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetSensitivity
//
// Summry		 : Get sensitivity
//
// Argument		 : [i] nDeviceID -> Hardware ID
//          	 : [o] pbLow
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetSensitivity( INT nDeviceID, BOOL* pbLow );

//-----------------------------------------------------------------------------
// Function name : DcIc_SetSensitivity
//
// Summry		 : Set sensitivity
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] bLow
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetSensitivity( INT nDeviceID, BOOL bLow );

//-----------------------------------------------------------------------------
// Function name : DcIc_GetCoolingControl
//
// Summry		 : Get Cooling Control
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pbCoolingControl
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetCoolingControl( INT nDeviceID, BOOL* pbCoolingControl);

//-----------------------------------------------------------------------------
// Function name : DcIc_SetCoolingControl
//
// Summry		 : Set Cooling Control
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] bCoolingControl
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetCoolingControl( INT nDeviceID, BOOL bCoolingControl);

//-----------------------------------------------------------------------------
// Function name : DcIc_GetTemperature1
//
// Summry		 : Get Sensor's temperature 1
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pwTemperature1
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetTemperature1( INT nDeviceID, WORD* pwTemperature1);

//-----------------------------------------------------------------------------
// Function name : DcIc_GetTemperature2
//
// Summry		 : Get Sensor's temperature 2
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pwTemperature2
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetTemperature2( INT nDeviceID, WORD* pwTemperature2);

//-----------------------------------------------------------------------------
// Function name : DcIc_GetMPPMode
//
// Summry		 : Get MPP Mode
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pbMPPMode
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetMPPMode( INT nDeviceID, BYTE* pbMPPMode);

//-----------------------------------------------------------------------------
// Function name : DcIc_SetMPPMode
//
// Summry		 : Set MPP Mode
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] bMPPMode
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetMPPMode( INT nDeviceID, BYTE bMPPMode);

//-----------------------------------------------------------------------------
// Function name : DcIc_GetHorizontalBinning
//
// Summry		 : Get Horizontal Binning
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pwHorizontalBinning
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetHorizontalBinning( INT nDeviceID, WORD* pwHorizontalBinning);

//-----------------------------------------------------------------------------
// Function name : DcIc_SetHorizontalBinning
//
// Summry		 : Set Horizontal Binning
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] wHorizontalBinning
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetHorizontalBinning( INT nDeviceID, WORD wHorizontalBinning);

//-----------------------------------------------------------------------------
// Function name : DcIc_GetVerticalBinning
//
// Summry		 : Get Vertical Binning
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [o] pwVerticalBinning
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_GetVerticalBinning( INT nDeviceID, WORD* pwVerticalBinning);

//-----------------------------------------------------------------------------
// Function name : DcIc_SetVerticalBinning
//
// Summry		 : Set Vertical Binning
//
// Argument		 : [i] nDevice ID -> Hardware ID
//          	 : [i] wVerticalBinning
//
// Return		 : error code (TRUE -> NoError)
//
// History		 :
//-----------------------------------------------------------------------------
_DLLFUNC BOOL _DLLSTDCALL DcIc_SetVerticalBinning( INT nDeviceID, WORD wVerticalBinning);

#ifdef	__cplusplus
};
#endif
