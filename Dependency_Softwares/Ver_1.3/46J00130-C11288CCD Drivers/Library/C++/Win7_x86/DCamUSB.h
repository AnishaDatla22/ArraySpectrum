/*=============================================================================
  Target Name	: Multichannel-Detector-Head and Driver-Circuit for Image Sensor
                : Control Dynamic Link Library
				:
  Target Type	: DLL [DCamUSB.dll]
				:	<<< Copyright(c) 2008-2011 HAMAMATSU PHOTONICS K.K. >>>
				:
  Created		: 01, Apl. 2008
  Last Updated	: 14, Feb. 2011
-------------------------------------------------------------------------------

=============================================================================*/

#if !defined(AFX_DCamUSB_H__INCLUDED_)
#define AFX_DCamUSB_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//============================================================================
// Execution Status ( Error Code ) Include
//============================================================================
#include "DCamStatusCode.h"

//============================================================================
// CONSTANTS DECLARATION
//============================================================================
#ifdef	__cplusplus
extern	"C" {
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// [Macros Definition]
#ifndef	_DCamUSBEXPORT
#define	_DCamUSBEXPORT	__declspec(dllimport)
#endif

#ifndef	_DCamUSBSTDCALL
#define	_DCamUSBSTDCALL	_stdcall
#endif



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// [The number of bits per pixel]
#define DCAM_BITPIXEL_8 				(8)		//  8 Bit
#define DCAM_BITPIXEL_10				(10)	// 10 Bit
#define DCAM_BITPIXEL_12				(12)	// 12 Bit
#define DCAM_BITPIXEL_14				(14)	// 14 Bit
#define DCAM_BITPIXEL_16				(16)	// 16 Bit


///////////////////////////////////////////////////////////////////////////////
// [Image acquisition]
#define DCAM_WAITSTATUS_COMPLETED		(0)		// Image acquisition is complete.
#define DCAM_WAITSTATUS_UNCOMPLETED		(1)		// Image acquisition is not complete.
#define DCAM_WAIT_INFINITE				(-1)	// Wait until image acquisition is complete.


///////////////////////////////////////////////////////////////////////////////
// [Device state]
#define DCAM_DEVSTATE_NON   			(0)		// Non-connection, No device found
#define DCAM_DEVSTATE_DEVICE			(1)		// Non-connection, Device found
#define DCAM_DEVSTATE_NODEVICE			(2)		// Connection, No device found
#define DCAM_DEVSTATE_CONNECT			(3)		// Connection, Device found
#define DCAM_DEVSTATE_BOOT  			(4)		// Connection, Device found(during the boot process)


///////////////////////////////////////////////////////////////////////////////
// [Binning type]
#define DCAM_BINNING_AREA				(0)		// Area Scanning
#define DCAM_BINNING_FULL				(1)		// Full Line Binning


///////////////////////////////////////////////////////////////////////////////
// [Trigger mode]
//  C10785
//  C11287
//  C11288 correspondence
#define DCAM_TRIGMODE_INT					(0)		// Internal Mode
#define DCAM_TRIGMODE_EXT_EDGE				(1)		// External Trigger Edge Mode
#define DCAM_TRIGMODE_EXT_LEVEL				(2)		// External Trigger Level Mode
//  C11160
//  C11165 correspondence
#define DCAM_TRIGMODE_INT2					(0)		// Internal Mode
#define	DCAM_TRIGMODE_EXT_EDGE2				(5)		// External Trigger Edge2 Mode
#define DCAM_TRIGMODE_EXT_LEVEL2			(6)		// External Trigger Level2 Mode
//  C11512 correspondence
#define	DCAM_TRIGMODE_IGA_GS_INT			(0)		// InGaAs Sensor - Global Shutter Internal Mode
#define	DCAM_TRIGMODE_IGA_GS_EXT_EDGE		(5)		// InGaAs Sensor - Global Shutter External Trigger Edge Mode
#define	DCAM_TRIGMODE_IGA_GS_EXT_GATED		(7)		// InGaAs Sensor - Global Shutter External Gated Mode
#define	DCAM_TRIGMODE_IGA_GS_EXT_ONE_SHOT	(8)		// InGaAs Sensor - Global Shutter External One Shot Mode
#define	DCAM_TRIGMODE_IGA_RS_INT			(10)	// InGaAs Sensor - Rolling Shutter Internal Mode
#define	DCAM_TRIGMODE_IGA_RS_EXT_EDGE		(15)	// InGaAs Sensor - Rolling Shutter External Trigger Edge Mode
#define	DCAM_TRIGMODE_IGA_RS_EXT_GATED		(17)	// InGaAs Sensor - Rolling Shutter External Gated Mode
#define	DCAM_TRIGMODE_IGA_RS_EXT_ONE_SHOT	(18)	// InGaAs Sensor - Rolling Shutter External One Shot Mode
//  C11513 correspondence
//  C11514 correspondence
#define	DCAM_TRIGMODE_IGA_INT				(0)		// InGaAs Sensor - Internal Mode
#define	DCAM_TRIGMODE_IGA_EXT_EDGE			(5)		// InGaAs Sensor - External Trigger Edge Mode
#define	DCAM_TRIGMODE_IGA_EXT_LEVEL			(6)		// InGaAs Sensor - External Trigger Level Mode
#define	DCAM_TRIGMODE_IGA_EXT_GATED			(7)		// InGaAs Sensor - External Gated Mode
#define	DCAM_TRIGMODE_IGA_EXT_ONE_SHOT		(8)		// InGaAs Sensor - External One Shot Mode
#define	DCAM_TRIGMODE_IGA_EXT_EDGE2			(20)	// InGaAs Sensor - External Trigger Edge2 Mode
#define	DCAM_TRIGMODE_IGA_EXT_LEVEL2		(21)	// InGaAs Sensor - External Trigger Level2 Mode



///////////////////////////////////////////////////////////////////////////////
// [Trigger polarity]
#define DCAM_TRIGPOL_POSITIVE			(0)		// Positive polarity
#define DCAM_TRIGPOL_NEGATIVE			(1)		// Negative polarity

///////////////////////////////////////////////////////////////////////////////
// [CCD drive mode]
#define DCAM_CCDDRVMODE_SUSPEND			(0)		// Suspend
#define DCAM_CCDDRVMODE_STANDBY			(1)		// Standby

///////////////////////////////////////////////////////////////////////////////
// [CCD operating mode]
#define DCAM_OPMODE_DARKCURRENT			(0)		// Low Dark Current Mode
#define DCAM_OPMODE_SATURATION			(1)		// High Saturation Charge Mode

///////////////////////////////////////////////////////////////////////////////
// [LED operating mode]
#define DCAM_LEDOPMODE_OFF				(0)		// LED Off Mode
#define DCAM_LEDOPMODE_ON				(1)		// LED On Mode

///////////////////////////////////////////////////////////////////////////////
// [Device information type]
#define DCAM_DEVINF_TYPE				(0)		// Device type
#define DCAM_DEVINF_SERIALNO			(1)		// Serial number of device
#define DCAM_DEVINF_VERSION				(2)		// Device version


///////////////////////////////////////////////////////////////////////////////
// [USB transfer rate type]
#define DCAM_TRANSRATE_USB11			(0)		// USB 1.1 standard
#define DCAM_TRANSRATE_USB20			(1)		// USB 2.0 standard

///////////////////////////////////////////////////////////////////////////////
// [External trigger output type]
#define DCAM_OUTMODE_NOTOUTPUT			(0)		// Not output
#define DCAM_OUTMODE_PLS_DT_PW			(1)		// Output pulse (Delay time + Pulse width)
#define DCAM_OUTMODE_PLS_ACCUM			(2)		// Output pulse (Accumulation time)

///////////////////////////////////////////////////////////////////////////////
// [External trigger output polarity]
#define DCAM_OUTPOL_POSITIVE			(0)		// Positive
#define DCAM_OUTPOL_NEGATIVE			(1)		// Negative

///////////////////////////////////////////////////////////////////////////////
// [CCD device type]
enum	{
	DCAM_CCD_TYPE0 = 0,	// 2068x70
	DCAM_CCD_TYPE1,		// 2068x38
	DCAM_CCD_TYPE2,		// 2068x22
	DCAM_CCD_TYPE3,		// 1044x70
	DCAM_CCD_TYPE4,		// 1044x38
	DCAM_CCD_TYPE5,		// 1044x22
	DCAM_CCD_TYPE6,		// 2118x120(for Evaluation)
	DCAM_CCD_TYPE7,		// 2118x190(for Evaluation)
	DCAM_CCD_TYPE8,		// 2068x1 : S11150
	DCAM_CCD_TYPE9,		// 2068x1 : S11151
	DCAM_CCD_TYPE10,	// 64x64 : G11097
	DCAM_CCD_TYPE11,	// 2118x1(for Evaluation)
	DCAM_CCD_TYPE12,	// 2068x1 : S11155
	DCAM_CCD_TYPE13,	// 2068x1 : S11156
	DCAM_CCD_TYPE14,	// 32x1 : G11135
	DCAM_CCD_TYPE15,	// 64x1 : G11134
	DCAM_CCD_TYPE16,	// 256x1 : G11477
	DCAM_CCD_TYPE17,	// 256x1 : G11478
	DCAM_CCD_TYPE18,	// 512x1 : G11135
	DCAM_CCD_TYPE19,	// 512x1 : G11477
	DCAM_CCD_TYPE20,	// 512x1 : G11478
	DCAM_CCD_TYPE21,	// 562x1 : G11477/8-256D(for Evaluation)
	DCAM_CCD_TYPE22,	// 562x1 : G11135-512D(for Evaluation)
	DCAM_CCD_TYPE23,	// 562x1 : G11477/8-512D(for Evaluation)
	DCAM_CCD_TYPE24,	// 256x1 : G11135
	DCAM_CCD_TYPE25,	// 562x1 : G11135-256D(for Evaluation)
	DCAM_CCD_TYPE26,	// 256x1 : G11608-256DA
	DCAM_CCD_TYPE27,	// 512x1 : G11608-512DA
	DCAM_CCD_TYPE28,	// 256x1 : G11620-256DA
	DCAM_CCD_TYPE29,	// 512x1 : G11620-512DA
	DCAM_CCD_TYPE30,	// 562x1 : G11608-256DA(for Evaluation)
	DCAM_CCD_TYPE31,	// 562x1 : G11608-512DA(for Evaluation)
	DCAM_CCD_TYPE32,	// 562x1 : G11620-256DA(for Evaluation)
	DCAM_CCD_TYPE33,	// 562x1 : G11620-512DA(for Evaluation)
	DCAM_CCD_TYPE34,	// 2056x1 : S11151
	DCAM_CCD_TYPE35,	// 2106x1 : S11151(for Evaluation)
	DCAM_CCD_TYPE36,	// 128x128 : G11097-0707
	DCAM_CCD_TYPE37,	// 256x1 : G9203-256D
	DCAM_CCD_TYPE38,	// 512x1 : G9204-512D
	DCAM_CCD_TYPE39,	// 562x1 : G9204-256D(for Evaluation)
	DCAM_CCD_TYPE40,	// 562x1 : G9204-512D(for Evaluation)
	DCAM_CCD_TYPE41,	// 256x1 : G9494-256D
	DCAM_CCD_TYPE42,	// 512x1 : G9494-512D
	DCAM_CCD_TYPE43,	// 562x1 : G9494-256D(for Evaluation)
	DCAM_CCD_TYPE44,	// 562x1 : G9494-512D(for Evaluation)
	DCAM_CCD_TYPE45,	// 128x1 : G11620-128DA
	DCAM_CCD_TYPE46,	// 256x1 : G11620-256DF
	DCAM_CCD_TYPE47,	// 562x1 : G11620-128DA(for Evaluation)
	DCAM_CCD_TYPE48,	// 562x1 : G11620-128DF(for Evaluation)

	DCAM_CCD_LISTS
};

///////////////////////////////////////////////////////////////////////////////
// [Standard time unit]
#define DCAM_TIME_UNIT_TYPE1			(0)		// Trigger setting = [mSec], Pulse Out setting = [mSec]
#define DCAM_TIME_UNIT_TYPE2			(1)		// Trigger setting = [uSec], Pulse Out setting = [uSec]
#define DCAM_TIME_UNIT_TYPE3			(2)		// Trigger setting = [mSec], Pulse Out setting = [uSec]
#define DCAM_TIME_UNIT_TYPE4			(3)		// Trigger setting = [Clock], Pulse Out setting = [Clock]

///////////////////////////////////////////////////////////////////////////////
// [MPP mode]
#define DCAM_CCDMPPMODE_OFF				(0)		// Off
#define DCAM_CCDMPPMODE_ON				(1)		// On

///////////////////////////////////////////////////////////////////////////////
// [Electronic Shutter mode]
#define DCAM_CCDESHUTTER_OFF			(0)		// Off
#define DCAM_CCDESHUTTER_ON				(1)		// On

//============================================================================
// DcamInitialize()
//	Initialize the library.
// ---------------------------------------------------------------------------
// [Argument]
//			None. 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			1.	This function must first be run before running other functions.
//			2.	An error is issued if the library has already been initialized.
//			3.	Only one process can use this library.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamInitialize( VOID );

//============================================================================
// DcamUninitialize()
//	Unload the library resources and close the device driver.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			Call this function when quitting the program or the DCamLIB library is not needed.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamUninitialize( VOID );

//============================================================================
// DcamOpen()
//	Open the device.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamOpen( VOID );

//============================================================================
// DcamOpenIntendDev()
//	Open the device.
// ---------------------------------------------------------------------------
// [Argument]
//			nDevIndex : To open device index of intended.
//						If this index is "-1", this function open the device select dialog.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT BOOL _DCamUSBSTDCALL DcamOpenIntendDev( INT nDevIndex );

//============================================================================
// DcamClose()
//	Close the device.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamClose( VOID );

//============================================================================
// DcamGetDeviceState()
//	Obtain the type of device state.
// ---------------------------------------------------------------------------
// [Argument]
//			pState   	: /O: Specify the address of the variable where the type 
//							  of device state is to be stored. One of the 
//							  following values is obtained.
//								DCAM_DEVSTATE_NON   	: Non-connection, No device found
//								DCAM_DEVSTATE_DEVICE	: Non-connection, Device found
//								DCAM_DEVSTATE_NODEVICE	: Connection, No device found
//								DCAM_DEVSTATE_CONNECT	: Connection, Device found
//								DCAM_DEVSTATE_BOOT	: Connection, Device found(during the boot process)
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetDeviceState( INT* pState );

//============================================================================
// DcamGetImageSize()
//	Obtain the width and height of image data to acquire from the USB Driver Board.
// ---------------------------------------------------------------------------
// [Argument]
//			pWidth		: /O: Specify the address of the variable where the image 
//							  width is to be stored. 
//			pHeight		: /O: Specify the address of the variable where the image 
//							   height is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetImageSize( INT* pWidth, INT* pHeight );

//============================================================================
// DcamGetBitPerPixel()
//	Obtain the number of bits per pixel.
// ---------------------------------------------------------------------------
// [Argument]
//			pBit		: /O: Specify the address of the variable where the number 
//							  of bits per pixel is to be stored. One of the following 
//							  values is obtained.
//								DCAM_BITPIXEL_8 	: 8 Bit
//								DCAM_BITPIXEL_10	: 10 Bit
//								DCAM_BITPIXEL_12	: 12 Bit
//								DCAM_BITPIXEL_14	: 14 Bit
//								DCAM_BITPIXEL_16	: 16 Bit
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetBitPerPixel( INT* pBit );

//============================================================================
// DcamSetMeasureDataCount()
//	Set the measurement line count.
// ---------------------------------------------------------------------------
// [Argument]
//			nCount		:I/ : Specify an measurement line count from 1 to 100 [line].
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			When this function is run, the number of bytes per capture size may change. 
//			Check the capture size with the DcamGetCaptureBytes function.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetMeasureDataCount( INT nCount );

//============================================================================
// DcamGetMeasureDataCount()
//	Obtain the measurement line count.
// ---------------------------------------------------------------------------
// [Argument]
//			pCount		: /O: Specify the address of the variable where the  
//							  currently set measurement line count is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetMeasureDataCount( INT* pCount );

//============================================================================
// DcamGetCaptureBytes()
//	Obtain the number of bytes of one frame.
// ---------------------------------------------------------------------------
// [Argument]
//			pBytes  	: /O: Specify the address of the variable where the
//							  number of bytes of one frame is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetCaptureBytes( INT* pBytes );

//============================================================================
// DcamGetTotalCaptureBytes()
//	Obtain the total number of bytes per capture size.
// ---------------------------------------------------------------------------
// [Argument]
//			pBytes  	: /O: Specify the address of the variable where the total 
//							  number of bytes per capture size is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetTotalCaptureBytes( INT* pBytes );

//============================================================================
// DcamCapture()
//	Start to acquire one image from the USB Driver Board.
// ---------------------------------------------------------------------------
// [Argument]
//			pImageBuff	: /O: Specify the start address in the buffer where image 
//							  data is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes).
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			1. This function issues an instruction to start image acquisition. 
//             Since image acquisition is not complete even when this function ends, 
//			   use the DcamWait function to check whether image acquisition is complete.
//			2. The necessary buffer size can be obtained with the DcamGetCaptureBytes function.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamCapture( LPVOID pImageBuff, INT nBuffSize );
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamCaptureEx( WORD* pImageBuff, INT nBuffSize );

//============================================================================
// DcamCaptureReverseX()
//	Start to acquire one image from the USB Driver Board.
//  The X axis of the acquired image data is reversed.
// ---------------------------------------------------------------------------
// [Argument]
//			pImageBuff	: /O: Specify the start address in the buffer where image 
//							  data is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes).
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			1. This function issues an instruction to start image acquisition. 
//             Since image acquisition is not complete even when this function ends, 
//			   use the DcamWait function to check whether image acquisition is complete.
//			2. The necessary buffer size can be obtained with the DcamGetCaptureBytes function.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamCaptureReverseX( LPVOID pImageBuff, INT nBuffSize );

//============================================================================
// DcamStop()
//	Stop image acquisition.
// ---------------------------------------------------------------------------
// [Argument]
//			None. 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamStop( VOID );

//============================================================================
// DcamStopEx()
//  This function stop image acquisition, and wait the reset of acquiring process 
//  in camera will be done.
// ---------------------------------------------------------------------------
// [Argument]
//			None. 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================*/
_DCamUSBEXPORT BOOL _DCamUSBSTDCALL DcamStopEx( VOID );

//============================================================================
// DcamWait()
//	Wait for image acquisition to complete.
// ---------------------------------------------------------------------------
// [Argument]
//			pStatus		: /O: Specify the address of the variable where image 
//							  acquisition end status is to be stored. Whether 
//							  image acquisition is complete or not can be checked 
//							  by the value in this variable. 
//							  The value is one of the following:
//								DCAM_WAITSTATUS_COMPLETED	: Image acquisition is complete.
//								DCAM_WAITSTATUS_UNCOMPLETED	: Image acquisition is not complete.
//
//							  This may be set to NULL when "DCAM_WAIT_INFINITE" is 
//							  specified for "nTimeout".
//								
//			nTimeout	:I/ : Specify the length of timeout in milliseconds.
//							  When "DCAM_WAIT_INFINITE" is specified here, the process 
//							  waits until image acquisition is finished.
//							  When "0" is specified, control is returned immediately 
//							  after checking the status.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamWait( DWORD* pStatus, INT nTimeout = 0 );

//============================================================================
// DcamSetGain()
//	Set the gain.
// ---------------------------------------------------------------------------
// [Argument]
//			nGain		:I/ : Specify the gain value in the range from 1 to 10
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetGain( INT nGain );

//============================================================================
// DcamGetGain()
//	Obtain the gain.
// ---------------------------------------------------------------------------
// [Argument]
//			pGain		: /O: Specify the address of the variable where the gain is 
//							  to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetGain( INT* pGain );

//============================================================================
// DcamSetOffset()
//	Set the offset.
// ---------------------------------------------------------------------------
// [Argument]
//			nOffset		:I/ : Specify the offset value in the range from 0 to 255
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetOffset( INT nOffset );

//============================================================================
// DcamGetOffset()
//	Obtain the offset.
// ---------------------------------------------------------------------------
// [Argument]
//			pOffset		: /O: Specify the address of the variable where the offset is 
//							  to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetOffset( INT* pOffset );

//============================================================================
// DcamSetDriveMode()
//	Set the CCD drive mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the CCD drive mode.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetDriveMode( INT  nMode, INT nTime  );

//============================================================================
// DcamGetDriveMode()
//	Obtain the CCD drive mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pMode		: /O: Specify the address of the variable where 
//							  the CCD drive mode is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetDriveMode( INT* pMode );

//============================================================================
// DcamSetBinning()
//	Set the binning.
// ---------------------------------------------------------------------------
// [Argument]
//			nBinning	:I/ : Specify the binning. One of the following can be 
//							  specified. 
//								DCAM_BINNING_AREA	: Area Scaning
//								DCAM_BINNING_FULL	: Full line binning
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//			When this function is run, the number of bytes per capture size may change. 
//			Check the capture size with the DcamGetCaptureBytes function.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetBinning( INT nBinning );

//============================================================================
// DcamGetBinning()
//	Obtain the binning.
// ---------------------------------------------------------------------------
// [Argument]
//			pBinning	: /O: Specify the address of the variable where the 
//							  currently set 
//							  binning is to be stored. One of the following values 
//							  is obtained.
//								DCAM_BINNING_AREA	: Area Scaning
//								DCAM_BINNING_FULL	: Full line binning
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetBinning( INT* pBinning );

//============================================================================
// DcamSetTriggerMode()
//	Set the trigger mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the trigger mode. One of the following 
//							  can be specified. 
//								C10785
//								C11287
//								C11288 correspondence
//								DCAM_TRIGMODE_INT      	 			: Internal Mode
//								DCAM_TRIGMODE_EXT_EDGE   			: External Trigger Edge Mode
//								DCAM_TRIGMODE_EXT_LEVEL  			: External Trigger Level Mode
//								C11160
//								C11165 correspondence
//								DCAM_TRIGMODE_INT      	 			: Internal Mode
//								DCAM_TRIGMODE_EXT_EDGE2				: External Trigger Edge2 Mode
//								DCAM_TRIGMODE_EXT_LEVEL2			: External Trigger Level2 Mode
//								C11512 correspondence
//								DCAM_TRIGMODE_IGA_GS_INT			: InGaAs Sensor - Global Shutter Internal Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_EDGE		: InGaAs Sensor - Global Shutter External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_GATED		: InGaAs Sensor - Global Shutter External Gated Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_ONE_SHOT	: InGaAs Sensor - Global Shutter External One Shot Mode
//								DCAM_TRIGMODE_IGA_RS_INT			: InGaAs Sensor - Rolling Shutter Internal Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_EDGE		: InGaAs Sensor - Rolling Shutter External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_GATED		: InGaAs Sensor - Rolling Shutter External Gated Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_ONE_SHOT	: InGaAs Sensor - Rolling Shutter External One Shot Mode
//  							C11513 correspondence
//  							C11514 correspondence
//								DCAM_TRIGMODE_IGA_INT				: InGaAs Sensor - Internal Mode
//								DCAM_TRIGMODE_IGA_EXT_EDGE			: InGaAs Sensor - External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_EXT_GATED			: InGaAs Sensor - External Gated Mode
//								DCAM_TRIGMODE_IGA_EXT_EDGE2			: InGaAs Sensor - External Trigger Edge2 Mode
//								DCAM_TRIGMODE_IGA_EXT_LEVEL2		: InGaAs Sensor - External Trigger Level2 Mode
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetTriggerMode( INT nMode );

//============================================================================
// DcamGetTriggerMode()
//	Obtain the trigger mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pMode		: /O: Specify the address of the variable where the 
//							  currently set trigger mode 
//							  is to be stored. One of the following values is obtained.
//								C10785
//								C11287
//								C11288 correspondence
//								DCAM_TRIGMODE_INT      				: Internal Mode
//								DCAM_TRIGMODE_EXT_EDGE				: External Trigger Edge Mode
//								DCAM_TRIGMODE_EXT_LEVEL				: External Trigger Level Mode
//								C11160
//								C11165 correspondence
//								DCAM_TRIGMODE_INT      	 			: Internal Mode
//								DCAM_TRIGMODE_EXT_EDGE2				: External Trigger Edge2 Mode
//								DCAM_TRIGMODE_EXT_LEVEL2			: External Trigger Level2 Mode
//								C11512 correspondence
//								DCAM_TRIGMODE_IGA_GS_INT			: Global Shutter Internal Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_EDGE		: Global Shutter External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_GATED		: Global Shutter External Gated Mode
//								DCAM_TRIGMODE_IGA_GS_EXT_ONE_SHOT	: Global Shutter External One Shot Mode
//								DCAM_TRIGMODE_IGA_RS_INT			: Rolling Shutter Internal Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_EDGE		: Rolling Shutter External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_GATED		: Rolling Shutter External Gated Mode
//								DCAM_TRIGMODE_IGA_RS_EXT_ONE_SHOT	: Rolling Shutter External One Shot Mode
//  							C11513 correspondence
//  							C11514 correspondence
//								DCAM_TRIGMODE_IGA_INT				: InGaAs Sensor - Internal Mode
//								DCAM_TRIGMODE_IGA_EXT_EDGE			: InGaAs Sensor - External Trigger Edge Mode
//								DCAM_TRIGMODE_IGA_EXT_GATED			: InGaAs Sensor - External Gated Mode
//								DCAM_TRIGMODE_IGA_EXT_EDGE2			: InGaAs Sensor - External Trigger Edge2 Mode
//								DCAM_TRIGMODE_IGA_EXT_LEVEL2		: InGaAs Sensor - External Trigger Level2 Mode
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetTriggerMode( INT* pMode );

//============================================================================
// DcamSetTriggerPolarity()
//	Set the trigger polarity.
// ---------------------------------------------------------------------------
// [Argument]
//			nPolarity	:I/ : Specify the trigger polarity. One of the following 
//							  can be specified. 
//								DCAM_TRIGPOL_POSITIVE	: Positive
//								DCAM_TRIGPOL_NEGATIVE 	: Negative
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetTriggerPolarity( INT nPolarity );

//============================================================================
// DcamGetTriggerPolarity()
//	Obtain the trigger polarity.
// ---------------------------------------------------------------------------
// [Argument]
//			pPolarity	: /O: Specify the address of the variable where the 
//							  currently set trigger polarity is to be stored. 
//							  One of the following values is obtained.
//								DCAM_TRIGPOL_POSITIVE	: Positive
//								DCAM_TRIGPOL_NEGATIVE 	: Negative
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetTriggerPolarity( INT* pPolarity );

//============================================================================
// DcamSetExposureTime()
//	Set the exposure time.
// ---------------------------------------------------------------------------
// [Argument]
//			nTime		:I/ : Specify an exposure time from 0 to 65535 [msec].
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetExposureTime( INT nTime );

//============================================================================
// DcamGetExposureTime()
//	Obtain the exposure time.
// ---------------------------------------------------------------------------
// [Argument]
//			pTime		: /O: Specify the address of the variable where the  
//							  currently setexposure time [msec] is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetExposureTime( INT* pTime );

//============================================================================
// DcamSetCCDType()
//	Set the CCD sensor type.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the CCD sensor type from among the following types. 
//								DCAM_CCD_TYPE0	:S10420-1106 (2068x70)
//								DCAM_CCD_TYPE3	:S10420-1006 (1044x70)
//								DCAM_CCD_TYPE10	:G11097 (64x64)
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetCCDType( INT  nType );

//============================================================================
// DcamGetCCDType()
//	Obtain the CCD sensor type.
// ---------------------------------------------------------------------------
// [Argument]
//			pType		: /O: Specify the address of the variable where the  
//							  currently set the CCD sensor type is to be stored. 
//							  One of the following values is obtained.
//								DCAM_CCD_TYPE0	:S10420-1106 (2068x70)
//								DCAM_CCD_TYPE3	:S10420-1006 (1044x70)
//								DCAM_CCD_TYPE10	:G11097 (64x64)
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetCCDType( INT* pType );

//============================================================================
// DcamSetOperatingMode()
//	Set the CCD operating mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the CCD Operating from among the following modes. 
//								DCAM_OPMODE_DARKCURRENT	: Low Dark Current Mode
//								DCAM_OPMODE_SATURATION	: High Saturation Charge Mode
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetOperatingMode( INT nMode );

//============================================================================
// DcamGetOperatingMode()
//	Obtain the CCD operating mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pType		: /O: Specify the address of the variable where the  
//							  currently set the CCD Operating mode is to be stored. 
//							  One of the following values is obtained.
//								DCAM_OPMODE_DARKCURRENT	: Low Dark Current Mode
//								DCAM_OPMODE_SATURATION	: High Saturation Charge Mode
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetOperatingMode( INT* pMode );

//============================================================================
// DcamSetLEDOperatingMode()
//	Set the LED operating mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the LED Operating from among the following modes. 
//								DCAM_LEDOPMODE_OFF	: Off Mode
//								DCAM_LEDOPMODE_ON	: On Mode
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetLEDOperatingMode( INT nMode );

//============================================================================
// DcamGetLEDOperatingMode()
//	Obtain the LED operating mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pType		: /O: Specify the address of the variable where the  
//							  currently set the LED Operating mode is to be stored. 
//							  One of the following values is obtained.
//								DCAM_LEDOPMODE_OFF	: Off Mode
//								DCAM_LEDOPMODE_ON	: On Mode
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetLEDOperatingMode( INT* pMode );

//============================================================================
// DcamSetOutPulse()
//	Set The information on an external output
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specifies the output mode to set up
//								DCAM_OUTMODE_NOTOUTPUT   ： No Output
//								DCAM_OUTMODE_PLS_DT_PW   ： Output(Delay Time + Pulse width)
//								DCAM_OUTMODE_PLS_ACCUM   ： Output(Accumulation time)
//			nPolarity	:I/ : The polarity to set up is specified.
//								DCAM_OUTPOL_POSITIVE	： Positive
//								DCAM_OUTPOL_NEGATIVE	： Negative
//			nDelayTime	:I/ : The delay time to set up is specified.  
//			nPulseWidth	:I/ : The pulse width to set up is specified. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetOutPulse(INT nMode, INT nPolarity,
									INT nDelayTime, INT nPulseWidth);

//============================================================================
// DcamGetOutPulse()
//	Get The information on an external output
// ---------------------------------------------------------------------------
// [Argument]
//			pMode			: /O: Pointer to variable to store the output mode
//								DCAM_OUTMODE_NOTOUTPUT   ： No Output
//								DCAM_OUTMODE_PLS_DT_PW   ： Output(Delay Time + Pulse width)
//								DCAM_OUTMODE_PLS_ACCUM   ： Output(Accumulation time)
//			pPolarity		: /O: Pointer to variable to store the output polarity
//								DCAM_OUTPOL_POSITIVE	： Positive
//								DCAM_OUTPOL_NEGATIVE	： Negative
//			pDelayTime		: /O: Pointer to variable to store the delay time
//			pPulseWidth		: /O: Pointer to variable to store the pulse width
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetOutPulse(INT* pMode, INT* pPolarity, 
									INT* pDelayTime, INT* pPulseWidth);

//============================================================================
// DcamLoadParameters()
//	Load parameters to the device.
// ---------------------------------------------------------------------------
// [Argument]
//			nTimeout	:I/ : Specify the length of timeout in milliseconds. 
//							  Please set one or more values.
//							  When "0" is specified, processing is carried out 
//							  by the standard timeout.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamLoadParameters( INT nTimeout );

//============================================================================
// DcamStoreParameters()
//	Store parameters to the device.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamStoreParameters( VOID );

//============================================================================
// DcamGetVersion()
//	Obtain the library version number, in string format.
// ---------------------------------------------------------------------------
// [Argument]
//			szVersion	: /O: Specify the start address in the character string 
//							  buffer where the version of the library is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes). 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetVersion( char* szVersion, INT nBuffSize );

//============================================================================
// DcamGetDriverVersion()
//	Obtain the driver version number, in string format.
// ---------------------------------------------------------------------------
// [Argument]
//			szVersion	: /O: Specify the start address in the character string 
//							  buffer where the version of the driver is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes). 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetDriverVersion( char* szVersion, INT nBuffSize );

//============================================================================
// DcamGetFirmwareVersion()
//	Obtain the firmware version number, in string format.
// ---------------------------------------------------------------------------
// [Argument]
//			szVersion	: /O: Specify the start address in the character string 
//							  buffer where the version of the firmware is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes). 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetFirmwareVersion( char* szFirmVersion, INT nBuffSize );

//============================================================================
// DcamGetDeviceInformation()
//	Obtain the device information, in string format.
// ---------------------------------------------------------------------------
// [Argument]
//			nType		:I/ : Specify the Information Type from among the following types.
//								DCAM_DEVINF_TYPE		: Device type
//								DCAM_DEVINF_SERIALNO	: Serial number of device
//								DCAM_DEVINF_VERSION		: Device version
//			szBuff		: /O: Specify the start address in the character string buffer  
//							  where the information of device is to be stored.
//			nBuffSize	:I/ : Specify the buffer size (number of bytes). 
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetDeviceInformation( INT nType, char* szBuff, INT nBuffSize );

//============================================================================
// DcamGetTransferRateType()
//	Obtain the USB transfar rate type.
// ---------------------------------------------------------------------------
// [Argument]
//			pType   	: /O: Specify the address of the variable where the USB
//							  transfar rate type is to be stored. One of the 
//							  following values is obtained.
//								DCAM_TRANSRATE_USB11	: USB 1.1 standard
//								DCAM_TRANSRATE_USB20	: USB 2.0 standard
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetTransferRateType( INT* pType );

//============================================================================
// DcamGetLastError()
//	Obtain the last-error code.
// ---------------------------------------------------------------------------
// [Argument]
//			None. 
// [Return values]
//			The latest error code is returned. See the error code table for 
//			descriptions of error codes.
// [Note]
//============================================================================
_DCamUSBEXPORT  DWORD _DCamUSBSTDCALL DcamGetLastError( VOID );

//============================================================================
// DcamSetStandardTimeUnit()
//	Set the standard time unit.
// ---------------------------------------------------------------------------
// [Argument]
//			nType		:I/ : Specify the standard unit type from among the following types.
//								DCAM_TIME_UNIT_TYPE1	: Trigger setting = [mSec], Pulse Out setting = [mSec]
//								DCAM_TIME_UNIT_TYPE2	: Trigger setting = [uSec], Pulse Out setting = [uSec]
//								DCAM_TIME_UNIT_TYPE3	: Trigger setting = [mSec], Pulse Out setting = [uSec]
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetStandardTimeUnit(INT nType);

//============================================================================
// DcamGetStandardTimeUnit()
//	Obtain the standard time unit.
// ---------------------------------------------------------------------------
// [Argument]
//			pType		: /O: Specify the address of the variable  
//							  where the standard time unit is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetStandardTimeUnit(INT* pType);

//============================================================================
// DcamSetOverClock()
//	Set the over clock.
// ---------------------------------------------------------------------------
// [Argument]
//			nClock		:I/ : Specify the length of over clock in clock (number of MCLK).
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetOverClock(INT nClock);

//============================================================================
// DcamGetOverClock()
//	Obtain the over clock.
// ---------------------------------------------------------------------------
// [Argument]
//			pClock		: /O: Specify the length of over clock in clock(number of MCLK).
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetOverClock(INT *pClock);

//============================================================================
// DcamSetMPPMode()
//	Set MPP mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the MPP mode.
//								DCAM_CCDMPPMODE_OFF	: MPP mode is off.
//								DCAM_CCDMPPMODE_ON	: MPP mode is on.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetMPPMode( INT nMode ) ;

//============================================================================
// DcamGetMPPMode()
//	Get MPP mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pMode		: /O: Specify the address of the variable  
//							  where the MPP mode is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetMPPMode( INT* pMode ) ;

//============================================================================
// DcamSetLineTime()
//	Set line time.
// ---------------------------------------------------------------------------
// [Argument]
//			nTime		:I/ : Specify the line time.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11160,C11165 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetLineTime( INT nTime ) ;

//============================================================================
// DcamGetLineTime()
//	Get line time.
// ---------------------------------------------------------------------------
// [Argument]
//			pTime		: /O: Specify the address of the variable  
//							  where the line time is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11160,C11165 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetLineTime( INT* pTime ) ;

//============================================================================
// DcamSetIntegralCapacity()
//	Set integral capacity.
// ---------------------------------------------------------------------------
// [Argument]
//			nType		:I/ : Specify the type of integral capacity.
//									0-7 -> G11477,G11478
//									0-3 -> G11135
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11512,C11513 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetIntegralCapacity(INT nType);

//============================================================================
// DcamGetIntegralCapacity()
//	Get integral capacity.
// ---------------------------------------------------------------------------
// [Argument]
//			pType		: /O: Specify the address of the variable  
//							  where the integral capacity is to be stored.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11512,C11513 correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetIntegralCapacity(INT* pType);

//============================================================================
// DcamSetElectronicShutter()
//	Set Electronic Shutter mode.
// ---------------------------------------------------------------------------
// [Argument]
//			nMode		:I/ : Specify the Electronic Shutter mode.
//								DCAM_CCDESHUTTER_OFF	: Electronic Shutter mode is off.
//								DCAM_CCDESHUTTER_ON		: Electronic Shutter mode is on.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165-01(X) correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetElectronicShutter( INT nMode ) ;

//============================================================================
// DcamGetElectronicShutter()
//	Get Electronic Shutter mode.
// ---------------------------------------------------------------------------
// [Argument]
//			pMode		: /O: Specify the address of the variable  
//							  where the Electronic Shutter mode is to be stored.
//								DCAM_CCDESHUTTER_OFF	: Electronic Shutter mode is off.
//								DCAM_CCDESHUTTER_ON		: Electronic Shutter mode is on.
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165-01(X) correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetElectronicShutter( INT* pMode ) ;

//============================================================================
// DcamSetSensorSignalPulseWidth()
//	Set pulse width of sensor signal.
// ---------------------------------------------------------------------------
// [Argument]
//			nSignalSensor	:I/ : Specify the signal type.	* only '0'
//								0 : TG
//
//			nWidth			:I/ : Specify the pulse width.  * "usec"
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165-01(X) correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamSetSensorSignalPulseWidth( INT nSignalSensor, INT nWidth );

//============================================================================
// DcamGetSensorSignalPulseWidth()
//	Get pulse width of sensor signal.
// ---------------------------------------------------------------------------
// [Argument]
//			nSignalSensor	:I/ : Specify the signal type.	* only '0'
//								0 : TG
//
//			pWidth			: /O: Specify the address of the variable  
//							  where the Pulse Width is to be stored.
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]	C11165-01(X) correspondence.
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamGetSensorSignalPulseWidth( INT nSignalSensor, INT* pWidth );

//============================================================================
// DcamDeviceIsAlive()
//	Get Device Connection Status.
// ---------------------------------------------------------------------------
// [Argument]
// [Return values]
//			If the device alived(connect) : TRUE (1). 
//			If the device is not connect : FALSE (0).
// [Note]
//============================================================================
_DCamUSBEXPORT  BOOL _DCamUSBSTDCALL DcamDeviceIsAlive(VOID);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_DCamUSB_H__INCLUDED_)
