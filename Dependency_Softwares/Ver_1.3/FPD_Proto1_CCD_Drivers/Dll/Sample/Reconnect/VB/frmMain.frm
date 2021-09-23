VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   3  'ŒÅ’èÀÞ²±Û¸Þ
   Caption         =   "Sample"
   ClientHeight    =   2385
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2385
   ScaleWidth      =   3750
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton cmdDisconnect 
      Caption         =   "Disconnect"
      Height          =   525
      Left            =   2040
      TabIndex        =   1
      Top             =   210
      Width           =   1245
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   525
      Left            =   420
      TabIndex        =   0
      Top             =   210
      Width           =   1245
   End
   Begin VB.Label lblState 
      Height          =   1185
      Left            =   300
      TabIndex        =   2
      Top             =   960
      Width           =   3195
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_DevOpenFlag As Boolean

' the subclass procedure is in the clsDeviceCheck class module
Private WithEvents m_oWatchDevChg As clsDeviceCheck
Attribute m_oWatchDevChg.VB_VarHelpID = -1

Private Sub cmdConnect_Click()
    ' Connection the device
    If ConnectionDevice() Then m_DevOpenFlag = True
    
    Call CheckDevice

End Sub

Private Sub cmdDisconnect_Click()
    ' Disconnection the device
    If DisconnectionDevice() Then m_DevOpenFlag = False
    
    Call CheckDevice

End Sub

Private Sub Form_Load()

    ' create an instance of the clsDeviceCheck object and call it's
    ' SubClass method to initiate the subclass for this form
    Set m_oWatchDevChg = New clsDeviceCheck
    m_oWatchDevChg.SubClass hWnd

    m_DevOpenFlag = False
    Call CheckDevice
End Sub

Private Sub Form_Unload(Cancel As Integer)

    If m_DevOpenFlag = True Then
        Call DisconnectionDevice    ' Disconnection the device
    End If
    
    m_DevOpenFlag = False

    ' destroy the object so we don't crash since the
    ' subclass is terminated in the Class_Terminate event
    Set m_oWatchDevChg = Nothing

End Sub

' Get the system message
Private Sub m_oWatchDevChg_DeviceChanged()
    Dim DevState

  ' Get the device state
    If DcamGetDeviceState(DevState) Then
        ' Remove the Device
        If (DevState = DCAM_DEVSTATE_NODEVICE) And (m_DevOpenFlag = True) Then
          Call DisconnectionDevice          ' Disconnection the device
        
        ' Reconnection the Device
        ElseIf (DevState = DCAM_DEVSTATE_DEVICE) And (m_DevOpenFlag = True) Then
            ' Connection the device
            If ConnectionDevice() Then m_DevOpenFlag = True
        End If
    End If

    Call CheckDevice

End Sub

' Connection the device
Private Function ConnectionDevice() As Boolean
    ConnectionDevice = False
    
    cmdConnect.Enabled = False
    cmdDisconnect.Enabled = False
    
    'Initialize DLL
    If DcamInitialize() Then
        ConnectionDevice = DcamOpen()      ' Open the device
    End If
    
    cmdConnect.Enabled = True
    cmdDisconnect.Enabled = True

End Function

' Disconnection the device
Private Function DisconnectionDevice() As Boolean
    DisconnectionDevice = False

    ' Close the device
    If DcamClose() Then
        DisconnectionDevice = DcamUninitialize()    ' Uninitialize DLL
    End If
    
End Function

' Check the device State
Private Function CheckDevice() As Boolean
    Dim DevState

    CheckDevice = False

    ' Get the device state
    If DcamGetDeviceState(DevState) Then
    
        ' Set String of the device state
        Select Case DevState
        Case DCAM_DEVSTATE_NON:
            lblState.Caption = "Non-connection" + Chr(13) + "No device found"
        
        Case DCAM_DEVSTATE_DEVICE:
            lblState.Caption = "Non-connection" + Chr(13) + "Device found"
        
        Case DCAM_DEVSTATE_NODEVICE:
            lblState.Caption = "Connection" + Chr(13) + "No device found"
        
        Case DCAM_DEVSTATE_CONNECT:
            lblState.Caption = "Connection" + Chr(13) + "Device found"
        
        Case DCAM_DEVSTATE_BOOT:
            lblState.Caption = "Connection" + Chr(13) + "Device found" + Chr(13) + "(during the boot process)"
        End Select
    
        CheckDevice = True
    Else  ' Error
        lblState.Caption = "Check Device Error"
    End If

End Function
