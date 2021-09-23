Attribute VB_Name = "mdlDCamUSB"
Option Explicit

' ============================================================================
'  Target Name  : C10785/C11287/C11288 Driver Circuit for CCD Area Image Sensor
'               : Control Dynamic Link Library
'               :
'  Target Type  : DLL [DCamUSB.dll]
'               :   <<< Copyright(c) 2008 - 2011, HAMAMATSU PHOTONICS K.K. >>>
'               :
'  Created      : 12, May. 2008
'  Last Updated : 14, Feb. 2011
' ----------------------------------------------------------------------------

' ============================================================================
' CONSTANTS DECLARATION
' ============================================================================

' ////////////////////////////////////////////////////////////////////////////
' ////////////////////////////////////////////////////////////////////////////
' [The number of bits per pixel]
Public Const DCAM_BITPIXEL_8  As Long = (8)            '  8 Bit
Public Const DCAM_BITPIXEL_10 As Long = (10)           ' 10 Bit
Public Const DCAM_BITPIXEL_12 As Long = (12)           ' 12 Bit
Public Const DCAM_BITPIXEL_14 As Long = (14)           ' 14 Bit
Public Const DCAM_BITPIXEL_16 As Long = (16)           ' 16 Bit

' ////////////////////////////////////////////////////////////////////////////
' [Image acquisition]
Public Const DCAM_WAITSTATUS_COMPLETED   As Long = (0) ' Image acquisition is complete.
Public Const DCAM_WAITSTATUS_UNCOMPLETED As Long = (1) ' Image acquisition is not complete.

Public Const DCAM_WAIT_INFINITE          As Long = (-1) ' Wait until image acquisition is complete.


' ////////////////////////////////////////////////////////////////////////////
' [Device state]
Public Const DCAM_DEVSTATE_NON         As Long = (0)   ' Non-connection, No device found
Public Const DCAM_DEVSTATE_DEVICE      As Long = (1)   ' Non-connection, Device found
Public Const DCAM_DEVSTATE_NODEVICE    As Long = (2)   ' Connection, No device found
Public Const DCAM_DEVSTATE_CONNECT     As Long = (3)   ' Connection, Device found
Public Const DCAM_DEVSTATE_BOOT        As Long = (4)   ' Connection, Device found(during the boot process)

' ////////////////////////////////////////////////////////////////////////////
' [Binning type]
Public Const DCAM_BINNING_AREA As Long = (0)           ' Area scanning
Public Const DCAM_BINNING_FULL As Long = (1)           ' Full line binning


' ////////////////////////////////////////////////////////////////////////////
' [Trigger mode]
'For C10785 and C11287 and C11288
Public Const DCAM_TRIGMODE_INT       As Long = (0)     ' Internal Mode
Public Const DCAM_TRIGMODE_EXT_EDGE  As Long = (1)     ' External Trigger Edge Mode
Public Const DCAM_TRIGMODE_EXT_LEVEL As Long = (2)     ' External Trigger Level Mode

'For C11160 and C11165
Public Const DCAM_TRIGMODE_INT2      As Long = (0)     ' Internal Mode
Public Const DCAM_TRIGMODE_EXT_EDGE2 As Long = (5)     ' External Trigger Edge2 Mode

'For C11512
Public Const DCAM_TRIGMODE_IGA_GS_INT          As Long = (0)  ' InGaAs Sensor - Global Shutter Internal Mode
Public Const DCAM_TRIGMODE_IGA_GS_EXT_EDGE     As Long = (5)  ' InGaAs Sensor - Global Shutter External Trigger Edge Mode
Public Const DCAM_TRIGMODE_IGA_GS_EXT_GATED    As Long = (7)  ' InGaAs Sensor - Global Shutter External Gated Mode
Public Const DCAM_TRIGMODE_IGA_GS_EXT_ONE_SHOT As Long = (8)  ' InGaAs Sensor - Global Shutter External One Shot Mode
Public Const DCAM_TRIGMODE_IGA_RS_INT          As Long = (10) ' InGaAs Sensor - Rolling Shutter Internal Mode
Public Const DCAM_TRIGMODE_IGA_RS_EXT_EDGE     As Long = (15) ' InGaAs Sensor - Rolling Shutter External Trigger Edge Mode
Public Const DCAM_TRIGMODE_IGA_RS_EXT_GATED    As Long = (17) ' InGaAs Sensor - Rolling Shutter External Gated Mode
Public Const DCAM_TRIGMODE_IGA_RS_EXT_ONE_SHOT As Long = (18) ' InGaAs Sensor - Rolling Shutter External One Shot Mode

'For C11513 and C11514
Public Const DCAM_TRIGMODE_IGA_INT          As Long = (0)  ' InGaAs Sensor - Internal Mode
Public Const DCAM_TRIGMODE_IGA_EXT_EDGE     As Long = (5)  ' InGaAs Sensor - External Trigger Edge Mode
Public Const DCAM_TRIGMODE_IGA_EXT_LEVEL    As Long = (6)  ' InGaAs Sensor - External Trigger Level Mode
Public Const DCAM_TRIGMODE_IGA_EXT_GATED    As Long = (7)  ' InGaAs Sensor - External Gated Mode
Public Const DCAM_TRIGMODE_IGA_EXT_ONE_SHOT As Long = (8)  ' InGaAs Sensor - External One Shot Mode
Public Const DCAM_TRIGMODE_IGA_EXT_EDGE2    As Long = (20) ' InGaAs Sensor - External Trigger Edge2 Mode
Public Const DCAM_TRIGMODE_IGA_EXT_LEVEL2   As Long = (21) ' InGaAs Sensor - External Trigger Level2 Mode


' ////////////////////////////////////////////////////////////////////////////
' [Trigger polarity]
Public Const DCAM_TRIGPOL_POSITIVE As Long = (0)       ' Positive polarity
Public Const DCAM_TRIGPOL_NEGATIVE As Long = (1)       ' Negative polarity


' ////////////////////////////////////////////////////////////////////////////
' [CCD drive mode]
Public Const DCAM_CCDDRVMODE_SUSPEND As Long = (0)     ' Suspend
Public Const DCAM_CCDDRVMODE_STANDBY As Long = (1)     ' Standby


' ////////////////////////////////////////////////////////////////////////////
' [CCD operating mode]
Public Const DCAM_OPMODE_DARKCURRENT As Long = (0)     ' Low Dark Current Mode
Public Const DCAM_OPMODE_SATURATION  As Long = (1)     ' High Saturation Charge Mode


' ////////////////////////////////////////////////////////////////////////////
' [LED operating mode]
Public Const DCAM_LEDOPMODE_OFF As Long = (0)          '  LED Off Mode
Public Const DCAM_LEDOPMODE_ON  As Long = (1)          '  LED On Mode


' ////////////////////////////////////////////////////////////////////////////
' [Device information type]
Public Const DCAM_DEVINF_TYPE     As Long = (0)        ' Device type
Public Const DCAM_DEVINF_SERIALNO As Long = (1)        ' Serial number of device
Public Const DCAM_DEVINF_VERSION  As Long = (2)        ' Device version

' ////////////////////////////////////////////////////////////////////////////
' [USB transfer rate type]
Public Const DCAM_TRANSRATE_USB11 As Long = (0)        ' USB 1.1 standard
Public Const DCAM_TRANSRATE_USB20 As Long = (1)        ' USB 2.0 standard


' ////////////////////////////////////////////////////////////////////////////
' [External trigger output Type]
Public Const DCAM_OUTMODE_NOTOUTPUT As Long = (0)      ' Not output
Public Const DCAM_OUTMODE_PLS_DT_PW As Long = (1)      ' Output pulse (Delay time + Pulse width)
Public Const DCAM_OUTMODE_PLS_ACCUM As Long = (2)      ' Output pulse (Accumulation time)


' ////////////////////////////////////////////////////////////////////////////
' [External trigger output Polarity]
Public Const DCAM_OUTPOL_POSITIVE As Long = (0)        ' Positive
Public Const DCAM_OUTPOL_NEGATIVE As Long = (1)        ' Negative


' ////////////////////////////////////////////////////////////////////////////
' [CCD device type]
Public Const DCAM_CCD_TYPE0 As Long = (0)              ' S10420-1106 (2068x70)
Public Const DCAM_CCD_TYPE3 As Long = (3)              ' S10420-1006 (1044x70)


' ////////////////////////////////////////////////////////////////////////////
' ////////////////////////////////////////////////////////////////////////////
' Error Code ( Run Status Code )
Public Const dcCode_Success       As Long = (0)       ' Ended successfully
Public Const dcCode_Unknown       As Long = (1)       ' An unknown error has occurred
Public Const dcCode_NoInit        As Long = (2)       ' Library is not initialized
Public Const dcCode_AlreadyInit   As Long = (3)       ' Already used by other
Public Const dcCode_NoDriver      As Long = (4)       ' No driver was found
Public Const dcCode_NoMemory      As Long = (5)       ' Memory is insufficient
Public Const dcCode_NotConnected  As Long = (6)       ' Not connected

Public Const dcCode_InvalidParam  As Long = (9)       ' Invalid Argument

Public Const dcCode_DeviceDefect  As Long = (100)     ' Device is not functioning

Public Const dcCode_Overrun       As Long = (110)     ' Overrun error
Public Const dcCode_Timeout       As Long = (111)     ' Timeout error

Public Const dcCode_AlreadyStart  As Long = (120)     ' Already start

' ============================================================================
'  DcamInitialize()
'   Initialize the library.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           1.  This function must first be run before running other functions.
'           2.  An error is issued if the library has already been initialized.
'           3.  Only one process can use this library.
' ============================================================================
Public Declare Function DcamInitialize Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamUninitialize()
'   Unload the library resources and close the device driver.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           Call this function when quitting the program or the DCamCtl library is not needed.
' ============================================================================
Public Declare Function DcamUninitialize Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamOpen()
'   Open the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamOpen Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamClose()
'   Close the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamClose Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamGetDeviceState()
'    Obtain the type of device state.
'  ---------------------------------------------------------------------------
'  [Argument]
'            pState      : /O: Specify the address of the variable where the type
'                              of device state is to be stored. One of the
'                              following values is obtained.
'                                DCAM_DEVSTATE_NON       : Non-connection, No device found
'                                DCAM_DEVSTATE_DEVICE    : Non-connection, Device found
'                                DCAM_DEVSTATE_NODEVICE  : Connection, No device found
'                                DCAM_DEVSTATE_CONNECT   : Connection, Device found
'                                DCAM_DEVSTATE_BOOT  : Connection, Device found(during the boot process)
'  [Return values]
'            If the function succeeds the return value is TRUE (1).
'            If the function fails the return value is FALSE (0).
'            To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetDeviceState Lib "DCamUSB.dll" (ByRef pState As Long) As Long

' ============================================================================
'  DcamGetImageSize()
'   Obtain the width and height of image data to acquire from the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pWidth      : /O: Specify the address of the variable where the image
'                             width is to be stored.
'           pHeight     : /O: Specify the address of the variable where the image
'                              height is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetImageSize Lib "DCamUSB.dll" (ByRef pWidth As Long, ByRef pHeight As Long) As Long

' ============================================================================
'  DcamGetBitPerPixel()
'   Obtain the number of bits per pixel.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pBit        : /O: Specify the address of the variable where the number
'                             of bits per pixel is to be stored. One of the following
'                             values is obtained.
'                               DCAM_BITPIXEL_8  : 8 Bit
'                               DCAM_BITPIXEL_10 : 10 Bit
'                               DCAM_BITPIXEL_12 : 12 Bit
'                               DCAM_BITPIXEL_14 : 14 Bit
'                               DCAM_BITPIXEL_16 : 16 Bit
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetBitPerPixel Lib "DCamUSB.dll" (ByRef pBit As Long) As Long

' ============================================================================
'  DcamSetMeasureDataCount()
'   Set the measurement line count.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nCount      :I/ : Specify an measurement line count from 1 to 100 [line].
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetMeasureDataCount Lib "DCamUSB.dll" (ByVal nCount As Long) As Long

' ============================================================================
'  DcamGetMeasureDataCount()
'   Obtain the measurement line count.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pCount      : /O: Specify the address of the variable where the currently
'                             set measurement line count is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetMeasureDataCount Lib "DCamUSB.dll" (ByRef pCount As Long) As Long

' ============================================================================
'  DcamGetCaptureBytes()
'   Obtain the total number of bytes per capture size.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pBytes      : /O: Specify the address of the variable where the total
'                             number of bytes per capture size is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetCaptureBytes Lib "DCamUSB.dll" (ByRef pBytes As Long) As Long

' ============================================================================
'  DcamCapture()
'   Start to acquire one image from the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pImageBuff  : /O: Specify the start address in the buffer where image
'                             data is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           1. This function issues an instruction to start image acquisition.
'              Since image acquisition is not complete even when this function ends,
'              use the DcamWait function to check whether image acquisition is complete.
'           2. The necessary buffer size can be obtained with the DcamGetFrameBytes function.
' ============================================================================
Public Declare Function DcamCapture Lib "DCamUSB.dll" (pImageBuff As Any, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamCaptureReverseX()
'   Start to acquire one image from the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pImageBuff  : /O: Specify the start address in the buffer where image
'                             data is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           1. This function issues an instruction to start image acquisition.
'              Since image acquisition is not complete even when this function ends,
'              use the DcamWait function to check whether image acquisition is complete.
'           2. The necessary buffer size can be obtained with the DcamGetFrameBytes function.
' ============================================================================
Public Declare Function DcamCaptureReverseX Lib "DCamUSB.dll" (pImageBuff As Any, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamStop()
'   Stop image acquisition.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamStop Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamWait()
'   Wait for image acquisition to complete.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pStatus     : /O: Specify the address of the variable where image
'                             acquisition end status is to be stored. Whether
'                             image acquisition is complete or not can be checked
'                             by the value in this variable.
'                             The value is one of the following:
'                               DCAM_WAITSTATUS_COMPLETED   : Image acquisition is complete.
'                               DCAM_WAITSTATUS_UNCOMPLETED : Image acquisition is not complete.
'
'                             This may be set to NULL when "DCAM_WAIT_INFINITE" is
'                             specified for "nTimeout".
'
'           nTimeout    :I/ : Specify the length of timeout in milliseconds.
'                             When "DCAM_WAIT_INFINITE" is specified here, the process
'                             waits until image acquisition is finished.
'                             When "0" is specified, control is returned immediately
'                             after checking the status.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamWait Lib "DCamUSB.dll" (ByRef pStatus As Long, ByVal nTimeout As Long) As Long

' ============================================================================
'  DcamSetGain()
'   Set the gain.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nGain       :I/ : Specify the gain value in the range from 1 to 10
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetGain Lib "DCamUSB.dll" (ByVal nGain As Long) As Long

' ============================================================================
'  DcamGetGain()
'   Obtain the gain.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pGain       : /O: Specify the address of the variable where the gain is
'                             to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetGain Lib "DCamUSB.dll" (ByRef pGain As Long) As Long

' ============================================================================
'  DcamSetOffset()
'   Set the offset.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nOffset     :I/ : Specify the offset value in the range from 0 to 255
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetOffset Lib "DCamUSB.dll" (ByVal nOffset As Long) As Long

' ============================================================================
'  DcamGetOffset()
'   Obtain the offset.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pOffset     : /O: Specify the address of the variable where the offset is
'                             to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetOffset Lib "DCamUSB.dll" (ByRef pOffset As Long) As Long

' ============================================================================
'  DcamSetBinning()
'   Set the binning.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nBinning    :I/ : Specify the binning. One of the following can be
'                             specified.
'                               DCAM_BINNING_AREA   : Area scanning
'                               DCAM_BINNING_FULL   : Full line binning
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           When this function is run, the number of bytes per frame size may change.
'           Check the frame size with the DcamGetFrameBytes function.
' ============================================================================
Public Declare Function DcamSetBinning Lib "DCamUSB.dll" (ByVal nBinning As Long) As Long

' ============================================================================
'  DcamGetBinning()
'   Obtain the binning.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pBinning    : /O: Specify the address of the variable where the
'                             currently set
'                             binning is to be stored. One of the following values
'                             is obtained.
'                               DCAM_BINNING_AREA   : Area scanning
'                               DCAM_BINNING_FULL   : Full line binning
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetBinning Lib "DCamUSB.dll" (ByRef pBinning As Long) As Long

' ============================================================================
'  DcamSetTriggerMode()
'   Set the trigger mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the trigger mode. One of the following
'                             can be specified.
'                               DCAM_TRIGMODE_INT        : Internal Mode
'                               DCAM_TRIGMODE_EXT_EDGE   : External Trigger Edge Mode
'                               DCAM_TRIGMODE_EXT_LEVEL  : External Trigger Level Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetTriggerMode Lib "DCamUSB.dll" (ByVal nMode As Long) As Long

' ============================================================================
'  DcamGetTriggerMode()
'   Obtain the trigger mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pMode       : /O: Specify the address of the variable where the
'                             currently set trigger mode
'                             is to be stored. One of the following values is obtained.
'                               DCAM_TRIGMODE_INT        : Internal Mode
'                               DCAM_TRIGMODE_EXT_EDGE   : External Trigger Edge Mode
'                               DCAM_TRIGMODE_EXT_LEVEL  : External Trigger Level Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetTriggerMode Lib "DCamUSB.dll" (ByRef pMode As Long) As Long

' ============================================================================
'  DcamSetTriggerPolarity()
'   Set the trigger polarity.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nPolarity   :I/ : Specify the trigger polarity. One of the following
'                             can be specified.
'                               DCAM_TRIGPOL_POSITIVE   : Positive
'                               DCAM_TRIGPOL_NEGATIVE   : Negative
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetTriggerPolarity Lib "DCamUSB.dll" (ByVal nPolarity As Long) As Long

' ============================================================================
'  DcamGetTriggerPolarity()
'   Obtain the trigger polarity.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pPolarity   : /O: Specify the address of the variable where the
'                             currently set trigger polarity is to be stored.
'                             One of the following values is obtained.
'                               DCAM_TRIGPOL_POSITIVE   : Positive
'                               DCAM_TRIGPOL_NEGATIVE   : Negative
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetTriggerPolarity Lib "DCamUSB.dll" (ByRef pPolarity As Long) As Long

' ============================================================================
'  DcamSetExposureTime()
'   Set the exposure time.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nTime       :I/ : Specify an exposure time from 0 to 65535 [msec].
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetExposureTime Lib "DCamUSB.dll" (ByVal nTime As Long) As Long

' ============================================================================
'  DcamGetExposureTime()
'   Obtain the exposure time.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pTime       : /O: Specify the address of the variable where the
'                             currently setexposure time [msec] is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetExposureTime Lib "DCamUSB.dll" (ByRef pTime As Long) As Long

' ============================================================================

' ============================================================================
'  DcamSetCCDType()
'   Set the CCD sensor type.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the CCD sensor type from among the following types.
'                               DCAM_CCD_TYPE0  :S10420-1106 (2068x70)
'                               DCAM_CCD_TYPE3  :S10420-1006 (1044x70)
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetCCDType Lib "DCamUSB.dll" (ByVal nType As Long) As Long

' ============================================================================
'  DcamGetCCDType()
'   Obtain the CCD sensor type.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pType       : /O: Specify the address of the variable where the
'                             currently set the CCD sensor type is to be stored.
'                             One of the following values is obtained.
'                               DCAM_CCD_TYPE0  :S10420-1106 (2068x70)
'                               DCAM_CCD_TYPE3  :S10420-1006 (1044x70)
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetCCDType Lib "DCamUSB.dll" (ByRef pType As Long) As Long

' ============================================================================
'  DcamSetDriveMode()
'   Set the CCD drive mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the CCD drive mode. One of the following can
'                             be specified.
'                               DCAM_CCDDRVMODE_IDLE        : Idle
'                               DCAM_CCDDRVMODE_STANDBY     : Standby
'           nTimeout    :I/ : Specify the length of timeout in milliseconds.
'                             Please set one or more values.
'                             When "0" is specified, processing is carried out
'                             by the standard timeout.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetDriveMode Lib "DCamUSB.dll" (ByVal nMode As Long, ByVal nTime As Long) As Long

' ============================================================================
'  DcamGetDriveMode()
'   Obtain the CCD drive mode.
'  -----------------------------------------------------------------------------
'  [Argument]
'           pMode       : /O: Specify the address of the variable where the CCD drive
'                             mode is to be stored. One of the following values is
'                             obtained.
'                               DCAM_CCDDRVMODE_SUSPEND     : Suspend
'                               DCAM_CCDDRVMODE_STANDBY     : Standby
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetDriveMode Lib "DCamUSB.dll" (ByRef pMode As Long) As Long

' ============================================================================
'  DcamSetOperatingMode()
'   Set the CCD operating mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the CCD Operating from among the following modes.
'                               DCAM_OPMODE_DARKCURRENT : Low Dark Current Mode
'                               DCAM_OPMODE_SATURATION  : High Saturation Charge Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
'           When this function is run, the number of bytes per frame size may change.
'           Check the frame size with the DcamGetFrameBytes function.
' ============================================================================
Public Declare Function DcamSetOperatingMode Lib "DCamUSB.dll" (ByVal nMode As Long) As Long

' ============================================================================
'  DcamGetOperatingMode()
'   Obtain the CCD operating mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pMode       : /O: Specify the address of the variable where the
'                             currently set the CCD Operating mode is to be stored.
'                             One of the following values is obtained.
'                               DCAM_OPMODE_DARKCURRENT : Low Dark Current Mode
'                               DCAM_OPMODE_SATURATION  : High Saturation Charge Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetOperatingMode Lib "DCamUSB.dll" (ByRef pMode As Long) As Long

' ============================================================================
'  DcamSetLEDOperatingMode()
'   Set the LED operating mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the LED Operating from among the following modes.
'                               DCAM_LEDOPMODE_OFF  : Off Mode
'                               DCAM_LEDOPMODE_ON   : On Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetLEDOperatingMode Lib "DCamUSB.dll" (ByVal nMode As Long) As Long

' ============================================================================
'  DcamGetLEDOperatingMode()
'   Obtain the LED operating mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pType       : /O: Specify the address of the variable where the
'                             currently set the LED Operating mode is to be stored.
'                             One of the following values is obtained.
'                               DCAM_LEDOPMODE_OFF  : Off Mode
'                               DCAM_LEDOPMODE_ON   : On Mode
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetLEDOperatingMode Lib "DCamUSB.dll" (ByRef pMode As Long) As Long

' ============================================================================
'  DcamSetOutPulse()
'   Set The information on an external output
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specifies the output mode to set up
'                               DCAM_OUTMODE_NOTOUTPUT   ： No Output
'                               DCAM_OUTMODE_PLS_DT_PW   ： Output(Delay Time + Pulse width)
'                               DCAM_OUTMODE_PLS_ACCUM   ： Output(Accumulation time)
'           nPolarity   :I/ : The polarity to set up is specified.
'                               DCAM_OUTPOL_POSITIVE    ： Positive
'                               DCAM_OUTPOL_NEGATIVE    ： Negative
'           nDelayTime  :I/ : The delay time to set up is specified.
'           nPulseWidth :I/ : The pulse width to set up is specified.
'
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetOutPulse Lib "DCamUSB.dll" (ByVal nMode As Long, ByVal nPolarity As Long, _
                                    ByVal nDelayTime As Long, ByVal nPulseWidth As Long) As Long

' ============================================================================
'  DcamGetOutPulse()
'   Get The information on an external output
'  ---------------------------------------------------------------------------
'  [Argument]
'           pMode           : /O: Pointer to variable to store the output mode
'                               DCAM_OUTMODE_NOTOUTPUT   ： No Output
'                               DCAM_OUTMODE_PLS_DT_PW   ： Output(Delay Time + Pulse width)
'                               DCAM_OUTMODE_PLS_ACCUM   ： Output(Accumulation time)
'           pPolarity       : /O: Pointer to variable to store the output polarity
'                               DCAM_OUTPOL_POSITIVE    ： Positive
'                               DCAM_OUTPOL_NEGATIVE    ： Negative
'           pDelayTime      : /O: Pointer to variable to store the delay time
'           pPulseWidth     : /O: Pointer to variable to store the pulse width
'
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetOutPulse Lib "DCamUSB.dll" (ByRef pMode As Long, ByRef pPolarity As Long, _
                                    ByRef pDelayTime As Long, ByRef pPulseWidth As Long) As Long


' ============================================================================
'  DcamLoadParameters()
'   Load parameters to the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nTimeout    :I/ : Specify the length of timeout in milliseconds.
'                             Please set one or more values.
'                             When "0" is specified, processing is carried out
'                             by the standard timeout.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamLoadParameters Lib "DCamUSB.dll" (ByVal nTimeout As Long) As Long

' ============================================================================
'  DcamStoreParameters()
'   Store parameters to the device.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamStoreParameters Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamGetVersion()
'   Obtain the library version number, in string format.
'  ---------------------------------------------------------------------------
'  [Argument]
'           szVersion   : /O: Specify the start address in the character string
'                             buffer where the version of the library is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetVersion Lib "DCamUSB.dll" (ByVal szVersion As String, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamGetDriverVersion()
'   Obtain the driver version number, in string format.
'  ---------------------------------------------------------------------------
'  [Argument]
'           szVersion   : /O: Specify the start address in the character string
'                             buffer where the version of the driver is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetDriverVersion Lib "DCamUSB.dll" (ByVal szVersion As String, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamGetFirmwareVersion()
'   Obtain the firmware version number, in string format.
'  ---------------------------------------------------------------------------
'  [Argument]
'           szVersion   : /O: Specify the start address in the character string
'                             buffer where the version of the firmware is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetFirmwareVersion Lib "DCamUSB.dll" (ByVal szVersion As String, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamGetDeviceInformation()
'   Obtain the device information, in string format.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nType       :I/ : Specify the Information Type from among the following types.
'                               DCAM_DEVINF_TYPE        : Device type
'                               DCAM_DEVINF_SERIALNO    : Serial number of device
'                               DCAM_DEVINF_VERSION     : Device version
'           szBuff      : /O: Specify the start address in the character string buffer
'                             where the information of device is to be stored.
'           nBuffSize   :I/ : Specify the buffer size (number of bytes).
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetDeviceInformation Lib "DCamUSB.dll" (ByVal nType As Long, ByVal szBuff As String, ByVal nBuffSize As Long) As Long

' ============================================================================
'  DcamGetTransferRateType()
'   Obtain the USB transfar rate type.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pType       : /O: Specify the address of the variable where the USB
'                             transfar rate type is to be stored. One of the
'                             following values is obtained.
'                               DCAM_TRANSRATE_USB11    : USB 1.1 standard
'                               DCAM_TRANSRATE_USB20    : USB 2.0 standard
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetTransferRateType Lib "DCamUSB.dll" (ByRef pType As Long) As Long

' ============================================================================
'  DcamGetLastError()
'   Obtain the last-error code.
'  ---------------------------------------------------------------------------
'  [Argument]
'           None.
'  [Return values]
'           The latest error code is returned. See the error code table for
'           descriptions of error codes.
'  [Note]
' ============================================================================
Public Declare Function DcamGetLastError Lib "DCamUSB.dll" () As Long

' ============================================================================
'  DcamSetStandardTimeUnit()
'   Set the standard time unit.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nType       :I/ : Specify the standard unit type from among the following types.
'                               DCAM_TIME_UNIT_TYPE1    : Trigger setting = [mSec], Pulse Out setting = [mSec]
'                               DCAM_TIME_UNIT_TYPE2    : Trigger setting = [uSec], Pulse Out setting = [uSec]
'                               DCAM_TIME_UNIT_TYPE3    : Trigger setting = [mSec], Pulse Out setting = [uSec]
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetStandardTimeUnit Lib "DCamUSB.dll" (ByVal nType As Long) As Long

' ============================================================================
'  DcamGetStandardTimeUnit()
'   Obtain the standard time unit.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pType       : /O: Specify the address of the variable
'                             where the standard time unit is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetStandardTimeUnit Lib "DCamUSB.dll" (ByRef pType As Long) As Long

' ============================================================================
'  DcamSetOverClock()
'   Set the over clock.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nClock      :I/ : Specify the length of over clock in clock (number of MCLK).
'
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamSetOverClock Lib "DCamUSB.dll" (ByVal nClock As Long) As Long

' ============================================================================
'  DcamGetOverClock()
'   Obtain the over clock.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pClock      : /O: Specify the length of over clock in clock(number of MCLK).
'
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]
' ============================================================================
Public Declare Function DcamGetOverClock Lib "DCamUSB.dll" (ByRef pClock As Long) As Long

' ============================================================================
'  DCamSetMPPMode()
'   Set MPP mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nMode       :I/ : Specify the MPP mode.
'                               DCAM_CCDMPPMODE_OFF : MPP mode is off.
'                               DCAM_CCDMPPMODE_ON  : MPP mode is on.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11165 correspondence.
' ============================================================================
Public Declare Function DcamSetMPPMode Lib "DCamUSB.dll" (ByVal nMode As Long) As Long

' ============================================================================
'  DCamGetMPPMode()
'   Get MPP mode.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pMode       : /O: Specify the address of the variable
'                             where the MPP mode is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11165 correspondence.
' ============================================================================
Public Declare Function DcamGetMPPMode Lib "DCamUSB.dll" (ByRef pMode As Long) As Long

' ============================================================================
'  DCamSetLineTime()
'   Set line time.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nTime       :I/ : Specify the line time.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11160,C11165 correspondence.
' ============================================================================
Public Declare Function DcamSetLineTime Lib "DCamUSB.dll" (ByVal nTime As Long) As Long

' ============================================================================
'  DCamGetLineTime()
'   Get line time.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pTime       : /O: Specify the address of the variable
'                             where the line time is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11160,C11165 correspondence.
' ============================================================================
Public Declare Function DcamGetLineTime Lib "DCamUSB.dll" (ByRef pTime As Long) As Long

' ============================================================================
'  DcamSetIntegralCapacity()
'   Set integral capacity.
'  ---------------------------------------------------------------------------
'  [Argument]
'           nType       :I/ : Specify the type of integral capacity.
'                                   0-7 -> G11477,G11478
'                                   0-3 -> G11135
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11512,C11513 correspondence.
' ============================================================================
Public Declare Function DcamSetIntegralCapacity Lib "DCamUSB.dll" (ByVal nType As Long) As Long

' ============================================================================
'  DcamGetIntegralCapacity()
'   Get integral capacity.
'  ---------------------------------------------------------------------------
'  [Argument]
'           pType       : /O: Specify the address of the variable
'                             where the integral capacity is to be stored.
'  [Return values]
'           If the function succeeds the return value is TRUE (1).
'           If the function fails the return value is FALSE (0).
'           To obtain detailed error information, use the DcamGetLastError function.
'  [Note]   C11512,C11513 correspondence.
' ============================================================================
Public Declare Function DcamGetIntegralCapacity Lib "DCamUSB.dll" (ByRef pType As Long) As Long



