/*=============================================================================
  Target Name	: Multichannel-Detector-Head and Driver-Circuit for Image Sensor
                : Control Dynamic Link Library
				:
  Target Type	: Header
				:	<<< Copyright(c) 2008-2011 HAMAMATSU PHOTONICS K.K. >>>
				:
  Created		: 01, Oct. 2009
  Last Updated	: 14, Feb. 2011
-------------------------------------------------------------------------------

=============================================================================*/

#if !defined(AFX_DCamStatusCode_H__INCLUDED_)
#define AFX_DCamStatusCode_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Execution Status ( Error Code )
#define dcCode_Success				(   0 )		// Normal termination
#define dcCode_Unknown				(   1 )		// An unknown error has occurred
#define dcCode_NoInit				(   2 )		// Library is not initialized
#define dcCode_AlreadyInit			(   3 )		// Already in-use
#define dcCode_NoDriver				(   4 )		// No driver was found
#define dcCode_NoMemory				(   5 )		// Memory is insufficient
#define dcCode_NotConnected			(   6 )		// The device is not connected

#define dcCode_InvalidParam			(   9 )		// Invalid parameter

#define dcCode_DeviceDefect			( 100 )		// The device is not functioning

#define dcCode_Overrun				( 110 )		// Overrun has occurred
#define dcCode_Timeout				( 111 )		// Timeout has occurred

#define dcCode_AlreadyStart			( 120 )		// Already started

#define dcCode_CoolingOn			( 200 )		// Already cooling control started. 
#define dcCode_CoolingOff			( 201 )		// Cooling control stopped.




#endif // !defined(AFX_DCamStatusCode_H__INCLUDED_)
