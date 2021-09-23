VERSION 5.00
Begin VB.Form fMain 
   BorderStyle     =   3  'ŒÅ’èÀÞ²±Û¸Þ
   Caption         =   "Sample"
   ClientHeight    =   1725
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   2190
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1725
   ScaleWidth      =   2190
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton cmdCapture 
      Caption         =   "Capture"
      Height          =   1335
      Left            =   240
      TabIndex        =   0
      Top             =   180
      Width           =   1755
   End
End
Attribute VB_Name = "fMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCapture_Click()

    Dim DataBuff() As Integer
    Dim lRetStatus As Long
    Dim lWidth     As Long
    Dim lHeight    As Long
    Dim lImageSize As Long
    Dim lLineCount As Long
    Dim lBitSize   As Long
   
    lRetStatus = DCAM_WAITSTATUS_UNCOMPLETED
    lWidth = 0
    lHeight = 0
    lImageSize = 0
    
    lLineCount = 50                                         ' Line Count( 50 line )

    Call DcamInitialize                                     ' Initialize DLL
    Call DcamOpen                                           ' Open the device
    Call DcamStop                                           ' Stop acquisition

    Call DcamSetGain(1)                                     ' Set the gain 1
    Call DcamSetOffset(40)                                  ' Set the offset 10
    Call DcamSetBinning(DCAM_BINNING_FULL)                  ' Set the Full line binning
    Call DcamSetTriggerPolarity(DCAM_TRIGPOL_NEGATIVE)      ' Set the trigger polarity negative
    Call DcamSetTriggerMode(DCAM_TRIGMODE_INT2)             ' Set the trigger mode "Internal Mode "

    Call DcamSetMeasureDataCount(lLineCount)                ' Set the line count 5


    Call DcamGetBitPerPixel(lBitSize)                       ' Get the bit size

    Call DcamGetImageSize(lWidth, lHeight)                  ' Get the image size
    lImageSize = lWidth * lHeight

    On Error GoTo Data_Error
    ReDim DataBuff((lImageSize * lLineCount) - 1)
    On Error GoTo 0

    ' Acquire the image data
    Call DcamCapture(DataBuff(0), (lImageSize * lLineCount) * 2)

    Do
        ' Wait to complete the image acquisition
        Call DcamWait(lRetStatus, 0)

        If lRetStatus = DCAM_WAITSTATUS_COMPLETED Then
            Exit Do
        End If
    Loop

    If lRetStatus = DCAM_WAITSTATUS_COMPLETED Then
        ' Save data
        Call SaveData("Sample.txt", DataBuff, lWidth, lHeight, lLineCount)
    Else
        Call MsgBox("Error Capture.", vbCritical)
    End If

Data_Error:
    Call DcamStop                                           ' Stop acquisition
    Call DcamClose                                          ' Close the device
    Call DcamUninitialize                                   ' Uninitialize DLL
    
End Sub

' Save data
Sub SaveData(FileName As String, ByRef DataBuff() As Integer, lWidth As Long, lHeight As Long, lFrame As Long)
    Dim CountW As Long
    Dim CountH As Long
    Dim CountF As Long
    Dim ImageSize As Long
    Dim StrData As String


    ImageSize = lWidth * lHeight
    Open FileName For Output As #1
    
    For CountF = 0 To lFrame - 1
        For CountH = 0 To lHeight - 1
            For CountW = 0 To lWidth - 1
                StrData = Str(DataBuff(ImageSize * CountF + CountH * lWidth + CountW)) + ","
                Print #1, StrData;
            Next
            
            Print #1, ""
        Next
    Next
    
    Close #1

End Sub

