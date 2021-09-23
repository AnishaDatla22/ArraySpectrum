/*=============================================================================
  Target Name	: DCam  Driver Circuit for Area Image Sensor
                : Control Dynamic Link Library
				:
  Target Type	: DLL [DCamTmpCtrl.dll]
				:	<<< Copyright(c) 2008-2009, HAMAMATSU PHOTONICS K.K. >>>
				:
  Created		: 21, Aug. 2009
  Last Updated	: 24, Aug. 2009
-------------------------------------------------------------------------------

=============================================================================*/

#if !defined(AFX_DCamTmpCtrl_H__INCLUDED_)
#define AFX_DCamTmpCtrl_H__INCLUDED_

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
#ifndef	_DCamTmpCtrlEXPORT
#define	_DCamTmpCtrlEXPORT	__declspec(dllimport)
#endif

#ifndef	_DCamTmpCtrlSTDCALL
#define	_DCamTmpCtrlSTDCALL	_stdcall
#endif

///////////////////////////////////////////////////////////////////////////////
// [Cooling Contorl status]
#define DCAM_COOLING_CONTROL_OFF		(0)		// Cooling control off
#define	DCAM_COOLING_CONTROL_ON			(1)		// Cooling cooling on

///////////////////////////////////////////////////////////////////////////////
// [Cooling Temperature status]
#define DCAM_COOLING_STATUS_NORMAL		(0)		// The cooling temperature is normal
#define	DCAM_COOLING_STATUS_LOWER		(1)		// The cooling temperature is lower
#define	DCAM_COOLING_STATUS_HIGHER		(2)		// The cooling temperature is higher

///////////////////////////////////////////////////////////////////////////////
// [Thermistor status]
#define	DCAM_THERMISTOR_STATUS_NOERROR	(0)		// Thermistor no error
#define DCAM_THERMISTOR_STATUS_ERROR	(1)		// Thermistor error 
#define DCAM_THERMISTOR_STATUS_OVER		(2)		// Thermistor temperature over


//============================================================================
// DcamTmpCtrlInitialize()
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
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlInitialize( VOID );

//============================================================================
// DcamTmpCtrlUninitialize()
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
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlUninitialize( VOID );

//============================================================================
// DcamTmpCtrlGetLastError()
//	Obtain the last-error code.
// ---------------------------------------------------------------------------
// [Argument]
//			None. 
// [Return values]
//			The latest error code is returned. See the error code table for 
//			descriptions of error codes.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  DWORD _DCamTmpCtrlSTDCALL DcamTmpCtrlGetLastError( VOID );

//+ 2009.09.30
//============================================================================
// DcamTmpCtrlSetCoolingControl()
//	Set the cooling control status.
// ---------------------------------------------------------------------------
// [Argument]
//			nStatus		:I/ : Specify the Cooling control status from among the following modes. 
//							DCAM_COOLING_CONTROL_OFF	: Cooling control off
//							DCAM_COOLING_CONTROL_ON		: Cooling control on
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlSetCoolingControl( BOOL bOnOff );

//============================================================================
// DcamTmpCtrlGetCoolingControl()
//	Obtain the cooling control status.
// ---------------------------------------------------------------------------
// [Argument]
//			nStatus		: /O: Specify the address of the variable where the  
//							  currently set the cooling control status is to be stored. 
//							DCAM_COOLING_CONTROL_OFF	: Cooling control off
//							DCAM_COOLING_CONTROL_ON		: Cooling control on
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetCoolingControl( BOOL *pbOnOff );

//============================================================================
// DcamGetThermistorTemperature()
//	Obtain the thermistor temperature.
// ---------------------------------------------------------------------------
// [Argument]
//			nType		:I/ : Specify the thermistor temperature from among 
//							  the following modes. 
//							DCAM_THERMISTOR_TYPE_1	: Thermistor Type1
//							DCAM_THERMISTOR_TYPE_2	: Thermistor Type2
//			pValue		: /O: Specify the address of the variable where the 
//							  thermistor temperature is to be stored. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
//_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetThermistorTemperature(INT nType, INT *pValue );

//+ 2009.09.30
//============================================================================
// DcamTmpCtrlLoadCoolingTemperature()
//	Load the cooling temperature.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlLoadCoolingTemperature();

//============================================================================
// DcamTmpCtrlSaveCoolingTemperature()
//	Obtain the cooling temperature status.
// ---------------------------------------------------------------------------
// [Argument]
//			None.
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlSaveCoolingTemperature();

//============================================================================
// DcamTmpCtrlGetCoolingTemperature()
//	Obtain the cooling temperature.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  cooling temperature is to be stored. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetCoolingTemperature( INT *pValue );

//============================================================================
// DcamTmpCtrlSetCoolingTemperature()
//	Sets. the cooling temperature.
// ---------------------------------------------------------------------------
// [Argument]
//			nValue		:I/O: Specify the cooling temperature. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlSetCoolingTemperature( INT nValue );

//============================================================================
// DcamTmpCtrlGetCoolingTemperatureCurrent()
//	Obtain the cooling current temperature.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  cooling temperature is to be stored. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetCoolingTemperatureCurrent( INT *pValue );

//============================================================================
// DcamTmpCtrlGetCoolingControlConsumptionCurrent()
//	Obtain the cooling control consumption current.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  cooling control consumption current is to be stored. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
//_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetCoolingControlConsumptionCurrent( INT *pValue );

//============================================================================
// DcamTmpCtrlGetPeltierConsumptionCurrent()
//	Obtain the peltier consumption current.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  peltier consumption current is to be stored. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
//_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetPeltierConsumptionCurrent( INT *pValue );

//============================================================================
// DcamTmpCtrlGetCoolingStatus()
//	Obtain the cooling temperature status.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  cooling status is to be stored. 
//							  One of the  following values is obtained.
//								DCAM_COOLING_STATUS_LOWER	: The cooling temperature is lower. 
//								DCAM_COOLING_STATUS_HIGHER	: The cooling temperature is higher. 
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetCoolingStatus( INT *pValue );

//============================================================================
// DcamTmpCtrlGetThermistorStatus()
//	Obtain the cooling temperature status.
// ---------------------------------------------------------------------------
// [Argument]
//			pValue		: /O: Specify the address of the variable where the 
//							  thermistor status is to be stored. 
//							  One of the  following values is obtained.
//								DCAM_THERMISTOR_STATUS_ERROR : Thermistor error. 
//								DCAM_THERMISTOR_STATUS_OVER	 : Thermistor temperature over.
//
// [Return values]
//			If the function succeeds the return value is TRUE (1). 
//			If the function fails the return value is FALSE (0).
//			To obtain detailed error information, use the DcamGetLastError function.
// [Note]
//============================================================================
_DCamTmpCtrlEXPORT  BOOL _DCamTmpCtrlSTDCALL DcamTmpCtrlGetThermistorStatus( INT *pValue );

#ifdef __cplusplus
}
#endif

#endif	// !AFX_DCamTmpCtrl_H__INCLUDED_
