unit uMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, uHamamatsu_LOAD;

type
  TfMain = class(TForm)
    btnConnect: TButton;
    btnDisconnect: TButton;
    lblState: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnConnectClick(Sender: TObject);
    procedure btnDisconnectClick(Sender: TObject);
  private
    m_DevOpenFlag: Boolean;

    procedure WMDeviceChange(var Msg: TMessage); message WM_DEVICECHANGE;

    function ConnectionDevice: Boolean;
    function DisconnectionDevice: Boolean;
    function CheckDevice: Boolean;
  public
    { Public declarations }
  end;

var
  fMain: TfMain;

implementation

{$R *.dfm}

// Create form
procedure TfMain.FormCreate(Sender: TObject);
begin
  LoadDLL;
  m_DevOpenFlag := False;
  CheckDevice();
end;

// Close form
procedure TfMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if m_DevOpenFlag = True then
    DisconnectionDevice();  // Disconnection the device

  m_DevOpenFlag := False;
  FreeDLL;
end;

// Button Click (Connection)
procedure TfMain.btnConnectClick(Sender: TObject);
var
  Code: Boolean;
begin

  // Connection the device
  Code := ConnectionDevice();

  if Code = True then
    m_DevOpenFlag := True;

  CheckDevice();

end;

// Button Click (Disconnection)
procedure TfMain.btnDisconnectClick(Sender: TObject);
var
  Code: Boolean;
begin

  // Disconnection the device
  Code := DisconnectionDevice();

  if Code = True then
    m_DevOpenFlag := False;

  CheckDevice();

end;

// Get the system message
procedure TfMain.WMDeviceChange(var Msg: TMessage);
var
  Code: Boolean;
  DevState: Integer;
begin

  // Get the device state
  Code := DcamGetDeviceState(DevState);

  if Code = True then
  begin
    // Remove the Device
    if (DevState = DCAM_DEVSTATE_NODEVICE) and
       (m_DevOpenFlag = True) then
    begin
      DisconnectionDevice();        // Disconnection the device
    end

    else
    // Reconnection the Device
    if (DevState = DCAM_DEVSTATE_DEVICE) and
       (m_DevOpenFlag = True) then
    begin
      Code := ConnectionDevice();   // Connection the device
      if Code = True then m_DevOpenFlag := True;
    end

  end;

  CheckDevice();

end;


// Connection the device
function TfMain.ConnectionDevice: Boolean;
var
  Code: Boolean;
begin
  btnConnect.Enabled := False;
  btnDisconnect.Enabled := False;

  Code := DcamInitialize();  // Initialize DLL

  if Code = True then
    Code := DcamOpen();      // Open the device

  btnConnect.Enabled := True;
  btnDisconnect.Enabled := True;
  Result := Code;
end;

// Disconnection the device
function TfMain.DisconnectionDevice: Boolean;
var
  Code: Boolean;
begin

  Code := DcamClose();    // Close the device

  if Code = True then
    DcamUninitialize();   // Uninitialize DLL

  Result := Code;
end;

// Check the device State
function TfMain.CheckDevice: Boolean;
var
  Code: Boolean;
  DevState: Integer;
begin

  // Get the device state
  Code := DcamGetDeviceState(DevState);

  if Code = True then
  begin

    // Set String of the device state
    case DevState of
      DCAM_DEVSTATE_NON:
        lblState.Caption := 'Non-connection'#13#10'No device found';

      DCAM_DEVSTATE_DEVICE:
        lblState.Caption := 'Non-connection'#13#10'Device found';

      DCAM_DEVSTATE_NODEVICE:
        lblState.Caption := 'Connection'#13#10'No device found';

      DCAM_DEVSTATE_CONNECT:
        lblState.Caption := 'Connection'#13#10'Device found';

      DCAM_DEVSTATE_BOOT:
        lblState.Caption :=
          'Connection'#13#10'Device found'#13#10'(during the boot process)';

    end;
  end

  else  // Error
    lblState.Caption := 'Check Device Error';

  Result := Code;
end;

end.
