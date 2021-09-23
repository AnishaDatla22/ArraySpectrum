Attribute VB_Name = "mdlAPI_Declares"
Option Explicit

Public Type DEV_BROADCAST_HDR
  dbch_size As Long
  dbch_devicetype As Long
  dbch_reserved As Long
End Type

Public Type DEV_BROADCAST_VOLUME
  dbcv_size As Long
  dbcv_devicetype As Long
  dbcv_reserved As Long
  dbcv_unitmask As Long
  dbcv_flags As Long
End Type

Public Const DBTF_MEDIA  As Long = &H1&
Public Const DBT_DEVTYP_VOLUME  As Long = &H2&
Public Const WM_DEVICECHANGE  As Long = &H219&
Public Const DBT_DEVICEARRIVAL  As Long = &H8000&
Public Const DBT_DEVICEREMOVECOMPLETE  As Long = &H8004&


Public Const GWL_WNDPROC As Long = (-4&)

Public Declare Function IsWindow Lib "user32" (ByVal hWnd&) As Long

Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (lpDest As Any, lpSource As Any, ByVal cBytes&)

Public Declare Function SetProp Lib "user32" Alias "SetPropA" (ByVal hWnd As Long, ByVal lpString As String, ByVal hData As Long) As Long
Public Declare Function GetProp Lib "user32" Alias "GetPropA" (ByVal hWnd As Long, ByVal lpString As String) As Long
Public Declare Function RemoveProp Lib "user32" Alias "RemovePropA" (ByVal hWnd&, ByVal lpString$) As Long

Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hWnd&, _
                                                            ByVal nIndex&, ByVal dwNewLong&) As Long

Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc&, _
                                             ByVal hWnd&, ByVal Msg&, ByVal wParam&, ByVal lParam&) As Long



