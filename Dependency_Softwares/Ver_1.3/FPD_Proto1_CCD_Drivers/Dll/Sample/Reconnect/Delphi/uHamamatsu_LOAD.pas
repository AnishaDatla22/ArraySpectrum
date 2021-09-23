//=============================================================================
//  Target Name 	: C10785/C11287/C11288 Driver Circuit for CCD Area Image Sensor
//	        			: Control Dynamic Link Library
//	        			:
//  Target Type 	: DLL [DCamUSB.dll]
//        				:	<<< Copyright(c) 2008, HAMAMATSU PHOTONICS K.K. >>>
//	        			:
//  Created   		: 12, May. 2008
//  Last Updated	: 12, May. 2008
//-------------------------------------------------------------------------------
//
//=============================================================================
unit uHamamatsu_LOAD;

interface

  uses Windows;
  type
   LPVOID = PChar;

   // DCamUSB.dll
   DC_Initialize = function : Boolean; stdcall;
   DC_UnInitialize = function : Boolean; stdcall;
   DC_Open = function : Boolean; stdcall;
   DC_Close = function : Boolean; stdcall;
   DC_GetDeviceState = function (Var nState: Integer) : Boolean; stdcall;
   DC_GetImageSize = function (Var nWidth, nHeight: Integer) : Boolean; stdcall;
   DC_GetBitPerPixel = function (Var pBit: Integer) : Boolean; stdcall;
   DC_SetMeasureDataCount = function (nCount: Integer) : Boolean; stdcall;
   DC_GetMeasureDataCount = function (Var nCount: Integer) : Boolean; stdcall;
   DC_GetCaptureBytes = function (Var pFrameBytes: Integer) : Boolean; stdcall;
   DC_Capture = function (pImageBuff: LPVOID; nBuffSize: Integer) : Boolean; stdcall;
   DC_CaptureReverseX = function (pImageBuff: LPVOID; nBuffSize: Integer) : Boolean; stdcall;
   DC_Stop = function : Boolean; stdcall;
   DC_Wait = function (Var pStatus: DWord; nTimeOut: Integer) : Boolean; stdcall;
   DC_SetGain = function (nGain: Integer) : Boolean; stdcall;
   DC_GetGain = function (Var nGain: Integer) : Boolean; stdcall;
   DC_SetOffset = function (nOffset: Integer) : Boolean; stdcall;
   DC_GetOffset = function (Var nOffset: Integer) : Boolean; stdcall;
   DC_SetBinning = function (nBinning: Integer) : Boolean; stdcall;
   DC_GetBinning = function (Var nBinning: Integer) : Boolean; stdcall;
   DC_SetTriggerMode = function (nMode: Integer) : Boolean; stdcall;
   DC_GetTriggerMode = function (Var nMode: Integer) : Boolean; stdcall;
   DC_SetTriggerPolarity = function (nPolarity: Integer) : Boolean; stdcall;
   DC_GetTriggerPolarity = function (Var nPolarity: Integer) : Boolean; stdcall;
   DC_SetExposureTime = function (nTime: Integer) : Boolean; stdcall;
   DC_GetExposureTime = function (Var nTime: Integer) : Boolean; stdcall;
   DC_SetCCDType = function (nType: Integer) : Boolean; stdcall;
   DC_GetCCDType = function (Var nType: Integer) : Boolean; stdcall;
   DC_SetDriveMode = function (nMode: Integer; nTimeOut: Integer) : Boolean; stdcall;
   DC_GetDriveMode = function (Var nMode: Integer) : Boolean; stdcall;
   DC_SetOperatingMode = function (nMode: Integer) : Boolean; stdcall;
   DC_GetOperatingMode = function (Var nMode: Integer) : Boolean; stdcall;
   DC_SetLEDOperatingMode = function (nMode: Integer) : Boolean; stdcall;
   DC_GetLEDOperatingMode = function (Var nMode: Integer) : Boolean; stdcall;
   DC_SetOutPulse = function (nMode: Integer; nPolarity: Integer; nDelayTime: Integer; nPulseWidth: Integer) : Boolean; stdcall;
   DC_GetOutPulse = function (Var pMode: Integer; Var pPolarity: Integer; Var pDelayTime: Integer; Var pPulseWidth: Integer) : Boolean; stdcall;
   DC_LoadParameters = function (nTimeOut: Integer) : Boolean; stdcall;
   DC_StoreParameters = function : Boolean; stdcall;
   DC_GetVersion = function (pVersion: PChar; nBuffSize: Integer) : Boolean; stdcall;
   DC_GetDriverVersion = function (pVersion: PChar; nBuffSize: Integer) : Boolean; stdcall;
   DC_GetFirmwareVersion = function (pFirmVersion: PChar; nBuffSize: Integer) : Boolean; stdcall;
   DC_GetDeviceInformation = function (nType: Integer; pBuffer: PChar; nBuffSize: Integer) : Boolean; stdcall;
   DC_GetTransferRateType = function (Var nType: Integer) : Boolean; stdcall;
   DC_GetLastError = function : DWord; stdcall;
   DC_SetStandardTimeUnit = function (nType: Integer) : Boolean; stdcall;
   DC_GetStandardTimeUnit = function (Var nType: Integer) : Boolean; stdcall;
   DC_SetOverClock = function (nClock: Integer) : Boolean; stdcall;
   DC_GetOverClock = function (Var nClock: Integer) : Boolean; stdcall;
   DC_SetMPPMode = function (nMode: Integer) : Boolean; stdcall;
   DC_GetMPPMode = function (Var nMode: Integer) : Boolean; stdcall;
   DC_SetLineTime = function (nTime: Integer) : Boolean; stdcall;
   DC_GetLineTime = function (Var nTime: Integer) : Boolean; stdcall;
   DC_SetIntegralCapacity = function (nType: Integer) : Boolean; stdcall;
   DC_GetIntegralCapacity = function (Var nType: Integer) : Boolean; stdcall;

  const

//============================================================================
// CONSTANTS DECLARATION
//============================================================================

    // Device state
    DCAM_DEVSTATE_NON      = 0;  // Non-connection, No device found
    DCAM_DEVSTATE_DEVICE	 = 1;  // Non-connection, Device found
    DCAM_DEVSTATE_NODEVICE = 2;  // Connection, No device found
    DCAM_DEVSTATE_CONNECT	 = 3;  // Connection, Device found
    DCAM_DEVSTATE_BOOT	   = 4;  // Connection, Device found(during the boot process)

    // Number of bits per pixel
    DCAM_BITPIXEL_8  = 8;   //  8 bits
    DCAM_BITPIXEL_10 = 10;  // 10 bits
    DCAM_BITPIXEL_12 = 12;  // 12 bits
    DCAM_BITPIXEL_14 = 14;  // 14 bits
    DCAM_BITPIXEL_16 = 16;  // 16 bits

    // Image Acquisition
    DCAM_WAITSTATUS_COMPLETED   = 0; // Image acquisition is complete
    DCAM_WAITSTATUS_UNCOMPLETED = 1; // Image acquisition is not complete

    // Image Acquisition
    DCAM_WAIT_INFINITE = -1; // Wait until image acquisition is complete

    // Binning
    DCAM_BINNING_AREA = 0; // Area scanning
    DCAM_BINNING_FULL = 1; // Full line binning

    // Trigger Mode
    // For C10785 and C11287 and C11288
    DCAM_TRIGMODE_INT        = 0; // Internal Mode
    DCAM_TRIGMODE_EXT_EDGE   = 1; // External Trigger Edge Mode
    DCAM_TRIGMODE_EXT_LEVEL  = 2; // External Trigger Level Mode
    // For C11160 and C11165
    DCAM_TRIGMODE_INT2       = 0; // Internal Mode
    DCAM_TRIGMODE_EXT_EDGE2  = 5; // External Trigger Edge2 Mode
    // For C11512
    DCAM_TRIGMODE_IGA_GS_INT          = 0;  // InGaAs Sensor - Global Shutter Internal Mode
    DCAM_TRIGMODE_IGA_GS_EXT_EDGE     = 5;  // InGaAs Sensor - Global Shutter External Trigger Edge Mode
    DCAM_TRIGMODE_IGA_GS_EXT_GATED    = 7;  // InGaAs Sensor - Global Shutter External Gated Mode
    DCAM_TRIGMODE_IGA_GS_EXT_ONE_SHO  = 8;  // InGaAs Sensor - Global Shutter External One Shot Mode
    DCAM_TRIGMODE_IGA_RS_INT          = 10; // InGaAs Sensor - Rolling Shutter Internal Mode
    DCAM_TRIGMODE_IGA_RS_EXT_EDGE     = 15; // InGaAs Sensor - Rolling Shutter External Trigger Edge Mode
    DCAM_TRIGMODE_IGA_RS_EXT_GATED    = 17; // InGaAs Sensor - Rolling Shutter External Gated Mode
    DCAM_TRIGMODE_IGA_RS_EXT_ONE_SHOT = 18; // InGaAs Sensor - Rolling Shutter External One Shot Mode
    // For C11513 and C11514
    DCAM_TRIGMODE_IGA_INT          = 0;  // InGaAs Sensor - Internal Mode
    DCAM_TRIGMODE_IGA_EXT_EDGE     = 5;  // InGaAs Sensor - External Trigger Edge Mode
    DCAM_TRIGMODE_IGA_EXT_LEVEL    = 6;  // InGaAs Sensor - External Trigger Level Mode
    DCAM_TRIGMODE_IGA_EXT_GATED    = 7;  // InGaAs Sensor - External Gated Mode
    DCAM_TRIGMODE_IGA_EXT_ONE_SHOT = 8;  // InGaAs Sensor - External One Shot Mode
    DCAM_TRIGMODE_IGA_EXT_EDGE2    = 20; // InGaAs Sensor - External Trigger Edge2 Mode
    DCAM_TRIGMODE_IGA_EXT_LEVEL2   = 21; // InGaAs Sensor - External Trigger Level2 Mode

    // Trigger Polarity
    DCAM_TRIGPOL_POSITIVE = 0; // Positive
    DCAM_TRIGPOL_NEGATIVE = 1; // Negative

    // CCD Drive Mode
    DCAM_CCDDRVMODE_SUSPEND   = 0; // Suspend
    DCAM_CCDDRVMODE_STANDBY   = 1; // Standby

    // CCD operating mode
    DCAM_OPMODE_DARKCURRENT = 0; // Low Dark Current Mode
    DCAM_OPMODE_SATURATION  = 1; // High Saturation Charge Mode

    // LED operating mode
    DCAM_LEDOPMODE_OFF = 0;		// LED Off Mode
    DCAM_LEDOPMODE_ON  = 1;		// LED On Mode

    // Device Information Type
    DCAM_DEVINF_TYPE     = 0; // Device Type
    DCAM_DEVINF_SERIALNO = 1; // Serial Number of Device
    DCAM_DEVINF_VERSION  = 2; // Device Version

    // USB transfer rate type
    DCAM_TRANSRATE_USB11 = 0;	// USB 1.1 standard
    DCAM_TRANSRATE_USB20 = 1;	// USB 2.0 standard

    // External trigger output type
    DCAM_OUTMODE_NOTOUTPUT = 0;		// Not output
    DCAM_OUTMODE_PLS_DT_PW = 1;		// Output pulse (Delay time + Pulse width)
    DCAM_OUTMODE_PLS_ACCUM = 2;		// Output pulse (Accumulation time)

    // External trigger output Polarity
    DCAM_OUTPOL_POSITIVE = 0;		// Positive
    DCAM_OUTPOL_NEGATIVE = 1;		// Negative

    // CCD device type
    DCAM_CCD_TYPE0 = 0; 		// S10420-1106 (2068x70)
    DCAM_CCD_TYPE3 = 3;	  	// S10420-1006 (1044x70)

    // Error Code (Run Status)
    dcCode_Success        = 0;   // Normal termination
    dcCode_Unknown        = 1;   // An unknown error has occurred
    dcCode_NoInit         = 2;   // Library is not initialized
    dcCode_AlreadyInit    = 3;   // Already in-use
    dcCode_NoDriver       = 4;   // No driver was found
    dcCode_NoMemory       = 5;   // Memory is insufficient
    dcCode_NotConnected   = 6;   // The device is not connected
    dcCode_InvalidParam   = 9;   // Invalid parameter
    dcCode_DeviceDefect   = 100; // The device is not functioning
    dcCode_Overrun        = 110; // Overrun has occurred
    dcCode_Timeout        = 111; // Timeout has occurred
    dcCode_AlreadyStarted = 120; // Already started


  { procedimientos y funciones }

  procedure LoadDLL;
  procedure FreeDLL;

  var
   HandleDll : THandle;
   DcamInitialize : DC_Initialize;
   DcamUnInitialize : DC_UnInitialize;
   DcamGetDeviceState : DC_GetDeviceState;
   DcamOpen : DC_Open;
   DcamClose : DC_Close;
   DcamGetImageSize : DC_GetImageSize;
   DcamGetBitPerPixel : DC_GetBitPerPixel;
   DcamSetMeasureDataCount : DC_SetMeasureDataCount;
   DcamGetMeasureDataCount : DC_GetMeasureDataCount;
   DcamGetCaptureBytes : DC_GetCaptureBytes;
   DcamCapture : DC_Capture;
   DcamCaptureReverseX : DC_CaptureReverseX;
   DcamStop : DC_Stop;
   DcamWait : DC_Wait;
   DcamSetGain : DC_SetGain;
   DcamGetGain : DC_GetGain;
   DcamSetOffset : DC_SetOffset;
   DcamGetOffset : DC_GetOffset;
   DcamSetBinning : DC_SetBinning;
   DcamGetBinning : DC_GetBinning;
   DcamSetTriggerMode : DC_SetTriggerMode;
   DcamGetTriggerMode : DC_GetTriggerMode;
   DcamSetTriggerPolarity : DC_SetTriggerPolarity;
   DcamGetTriggerPolarity : DC_GetTriggerPolarity;
   DcamSetExposureTime : DC_SetExposureTime;
   DcamGetExposureTime : DC_GetExposureTime;
   DcamSetCCDType : DC_SetCCDType;
   DcamGetCCDType : DC_GetCCDType;
   DcamSetDriveMode : DC_SetDriveMode;
   DcamGetDriveMode : DC_GetDriveMode;
   DcamSetOperatingMode : DC_SetOperatingMode;
   DcamGetOperatingMode : DC_GetOperatingMode;
   DcamSetLEDOperatingMode : DC_SetLEDOperatingMode;
   DcamGetLEDOperatingMode : DC_GetLEDOperatingMode;
   DcamSetOutPulse : DC_SetOutPulse;
   DcamGetOutPulse : DC_GetOutPulse;
   DcamLoadParameters : DC_LoadParameters;
   DcamStoreParameters : DC_StoreParameters;
   DcamGetVersion : DC_GetVersion;
   DcamGetDriverVersion : DC_GetDriverVersion;
   DcamGetFirmwareVersion : DC_GetFirmwareVersion;
   DcamGetDeviceInformation : DC_GetDeviceInformation;
   DcamGetTransferRateType : DC_GetTransferRateType;
   DcamGetLastError : DC_GetLastError;
   DcamSetStandardTimeUnit : DC_SetStandardTimeUnit;
   DcamGetStandardTimeUnit : DC_GetStandardTimeUnit;
   DcamSetOverClock : DC_SetOverClock;
   DcamGetOverClock : DC_GetOverClock;
   DcamSetMPPMode : DC_SetMPPMode;
   DcamGetMPPMode : DC_GetMPPMode;
   DcamSetLineTime : DC_SetLineTime;
   DcamGetLineTime : DC_GetLineTime;
   DcamSetIntegralCapacity : DC_SetIntegralCapacity;
   DcamGetIntegralCapacity : DC_GetIntegralCapacity;

implementation

  procedure LoadDLL;
  begin
     HandleDll := LoadLibrary('DCamUSB.dll');
     DcamInitialize := GetProcAddress(HandleDll, 'DcamInitialize');
     DcamUnInitialize := GetProcAddress(HandleDll, 'DcamUninitialize');
     DcamGetDeviceState := GetProcAddress(HandleDll, 'DcamGetDeviceState');
     DcamOpen := GetProcAddress(HandleDll, 'DcamOpen');
     DcamClose := GetProcAddress(HandleDll, 'DcamClose');
     DcamGetImageSize := GetProcAddress(HandleDll, 'DcamGetImageSize');
     DcamGetBitPerPixel := GetProcAddress(HandleDll, 'DcamGetBitPerPixel');
     DcamSetMeasureDataCount := GetProcAddress(HandleDll, 'DcamSetMeasureDataCount');
     DcamGetMeasureDataCount := GetProcAddress(HandleDll, 'DcamGetMeasureDataCount');
     DcamGetCaptureBytes := GetProcAddress(HandleDll, 'DcamGetCaptureBytes');
     DcamCapture := GetProcAddress(HandleDll, 'DcamCapture');
     DcamCaptureReverseX := GetProcAddress(HandleDll, 'DcamCaptureReverseX');
     DcamStop := GetProcAddress(HandleDll, 'DcamStop');
     DcamWait := GetProcAddress(HandleDll, 'DcamWait');
     DcamSetGain := GetProcAddress(HandleDll, 'DcamSetGain');
     DcamGetGain := GetProcAddress(HandleDll, 'DcamGetGain');
     DcamSetOffset := GetProcAddress(HandleDll, 'DcamSetOffset');
     DcamGetOffset := GetProcAddress(HandleDll, 'DcamGetOffset');
     DcamSetBinning := GetProcAddress(HandleDll, 'DcamSetBinning');
     DcamGetBinning := GetProcAddress(HandleDll, 'DcamGetBinning');
     DcamSetTriggerMode := GetProcAddress(HandleDll, 'DcamSetTriggerMode');
     DcamGetTriggerMode := GetProcAddress(HandleDll, 'DcamGetTriggerMode');
     DcamSetTriggerPolarity := GetProcAddress(HandleDll, 'DcamSetTriggerPolarity');
     DcamGetTriggerPolarity := GetProcAddress(HandleDll, 'DcamGetTriggerPolarity');
     DcamSetExposureTime := GetProcAddress(HandleDll, 'DcamSetExposureTime');
     DcamGetExposureTime := GetProcAddress(HandleDll, 'DcamGetExposureTime');
     DcamSetCCDType := GetProcAddress(HandleDll, 'DcamSetCCDType');
     DcamGetCCDType := GetProcAddress(HandleDll, 'DcamGetCCDType');
     DcamSetDriveMode := GetProcAddress(HandleDll, 'DcamSetDriveMode');
     DcamGetDriveMode := GetProcAddress(HandleDll, 'DcamGetDriveMode');
     DcamSetOperatingMode := GetProcAddress(HandleDll, 'DcamSetOperatingMode');
     DcamGetOperatingMode := GetProcAddress(HandleDll, 'DcamGetOperatingMode');
     DcamSetLEDOperatingMode := GetProcAddress(HandleDll, 'DcamSetLEDOperatingMode');
     DcamGetLEDOperatingMode := GetProcAddress(HandleDll, 'DcamGetLEDOperatingMode');
     DcamSetOutPulse := GetProcAddress(HandleDll, 'DcamSetOutPulse');
     DcamGetOutPulse := GetProcAddress(HandleDll, 'DcamGetOutPulse');
     DcamLoadParameters := GetProcAddress(HandleDll, 'DcamLoadParameters');
     DcamStoreParameters := GetProcAddress(HandleDll, 'DcamStoreParameters');
     DcamGetVersion := GetProcAddress(HandleDll, 'DcamGetVersion');
     DcamGetDriverVersion := GetProcAddress(HandleDll, 'DcamGetDriverVersion');
     DcamGetFirmwareVersion := GetProcAddress(HandleDll, 'DcamGetFirmwareVersion');
     DcamGetDeviceInformation := GetProcAddress(HandleDll, 'DcamGetDeviceInformation');
     DcamGetTransferRateType := GetProcAddress(HandleDll, 'DcamGetTransferRateType');
     DcamGetLastError := GetProcAddress(HandleDll, 'DcamGetLastError');
     DcamSetStandardTimeUnit := GetProcAddress(HandleDll, 'DcamSetStandardTimeUnit');
     DcamGetStandardTimeUnit := GetProcAddress(HandleDll, 'DcamGetStandardTimeUnit');
     DcamSetOverClock := GetProcAddress(HandleDll, 'DcamSetOverClock');
     DcamGetOverClock := GetProcAddress(HandleDll, 'DcamGetOverClock');
     DcamSetMPPMode := GetProcAddress(HandleDll, 'DcamSetMPPMode');
     DcamGetMPPMode := GetProcAddress(HandleDll, 'DcamGetMPPMode');
     DcamSetLineTime := GetProcAddress(HandleDll, 'DcamSetLineTime');
     DcamGetLineTime := GetProcAddress(HandleDll, 'DcamGetLineTime');
     DcamSetIntegralCapacity := GetProcAddress(HandleDll, 'DcamSetIntegralCapacity');
     DcamGetIntegralCapacity := GetProcAddress(HandleDll, 'DcamGetIntegralCapacity');
  end;

  procedure FreeDLL;
  begin
     FreeLibrary(HandleDll);
  end;

end.
