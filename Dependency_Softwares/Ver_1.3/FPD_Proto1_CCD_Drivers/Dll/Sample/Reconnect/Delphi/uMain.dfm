object fMain: TfMain
  Left = 229
  Top = 280
  Width = 232
  Height = 147
  Caption = 'Sample'
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object lblState: TLabel
    Left = 8
    Top = 56
    Width = 201
    Height = 41
    AutoSize = False
    Caption = 'lblState'
  end
  object btnConnect: TButton
    Left = 8
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Connect'
    TabOrder = 0
    OnClick = btnConnectClick
  end
  object btnDisconnect: TButton
    Left = 112
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Disconnect'
    TabOrder = 1
    OnClick = btnDisconnectClick
  end
end
