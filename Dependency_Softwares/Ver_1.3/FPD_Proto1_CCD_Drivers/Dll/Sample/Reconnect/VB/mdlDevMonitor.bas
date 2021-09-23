Attribute VB_Name = "mdlDevMonitor"
Option Explicit

Public Function WindProc(ByVal hWnd&, ByVal uMsg&, ByVal wParam&, ByVal lParam&) As Long

    WindProc = cDevMonitorFromhWnd(hWnd).WindowProc(hWnd, uMsg, wParam, lParam)
    
End Function


' resolve a dumb pointer into a referenced object....
Private Function cDevMonitorFromhWnd(ByVal hWnd As Long) As clsDeviceCheck
    Dim DevMonitorEx As clsDeviceCheck, pObj As Long
      
    ' retrieve the pointer from the property we set in the subclass routine
    pObj = GetProp(hWnd, ByVal "nvDevMonitor")
    
    ' copy the pointer into the local variable
    CopyMemory DevMonitorEx, pObj, 4&
    
    ' set a reference to the object
    Set cDevMonitorFromhWnd = DevMonitorEx
    
    ' clear the object variable
    CopyMemory DevMonitorEx, 0&, 4&
  
End Function


