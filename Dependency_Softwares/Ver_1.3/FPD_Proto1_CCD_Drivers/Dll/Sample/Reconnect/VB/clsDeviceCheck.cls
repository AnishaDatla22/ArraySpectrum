VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsDeviceCheck"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' original window proc address
Private m_WinProcOld As Long

' subclassed hWnd
Private m_hWnd As Long

' our events
Event DeviceChanged()
  
' system message processe
Friend Function WindowProc(ByVal hWindow&, ByVal uMsg&, ByVal wParam&, ByVal lParam&) As Long
  ' this function is called from the mdlDevMonitor BAS module.  all messages are for
  ' the subclasses hWnd are passed here to be processed before passing them on to VB

    Select Case uMsg
        ' catch the device changed message
        Case WM_DEVICECHANGE
            RaiseEvent DeviceChanged
    End Select
    
    ' pass the messages on to VB
    WindowProc = CallWindowProc(m_WinProcOld, hWindow, uMsg, wParam, lParam)

End Function


' this routine subclasses the window
Public Sub SubClass(ByVal hWnd&)
  
  ' first check with the OS to make sure the hWnd is a valid window
  If IsWindow(hWnd) Then
    ' we store a pointer to this instance of the class in an extra property
    ' we add to the window using the SetProp API function.  if the property exists,
    ' this window is already subclassed and we don't want to overwrite the property
    If GetProp(hWnd, "nvDevMonitor") Then Exit Sub
    
    ' store a pointer to this instance of the class object in an added property
    If SetProp(hWnd, ByVal "nvDevMonitor", ObjPtr(Me)) Then
      ' if the SetProp call succeeded, subclass the window...
      
        m_WinProcOld = SetWindowLong(hWnd, GWL_WNDPROC, AddressOf mdlDevMonitor.WindProc)
  
      ' store the subclassed hWnd so we will have it when it is time to un-subclass
      m_hWnd = hWnd
    End If
  End If
  
End Sub

' this routine un-subclasses the window
Private Sub UnSubClass()
  
  ' make sure the window still exists....
  If IsWindow(m_hWnd) Then
    ' if we have an address for the old windowproc, return the proc to the original state...
    If m_WinProcOld Then
      ' un-subclass the window
      SetWindowLong m_hWnd, GWL_WNDPROC, m_WinProcOld
      
      ' remove the added property
      RemoveProp m_hWnd, "nvDevMonitor"
      
      ' set the variables to zero to avoid any mishaps
      m_WinProcOld = 0
      m_hWnd = 0
    End If
    
  End If
  
End Sub

' we un-subclass the window when we are terminated
Private Sub Class_Terminate()
  UnSubClass
End Sub
