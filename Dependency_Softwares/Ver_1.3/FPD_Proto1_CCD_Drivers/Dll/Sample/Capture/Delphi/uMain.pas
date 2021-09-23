unit uMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, uHamamatsu_LOAD, Math;

type
  TForm1 = class(TForm)
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
    procedure DataSave(FName: String; Buffer: PWord; Width: Integer; Height: Integer; Frame: Integer);
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
 Buffer: PWord;
 BuffLen: Integer;
 Code: Boolean;
 Width: Integer;
 Height:Integer;
 LineCount:Integer;
 BitSize:Integer;
 Continue: Integer;
 WaitStat: Longword;
 MemHandle: HGlobal;
 OldCursor: TCursor;
begin
   OldCursor := Screen.Cursor;
   Screen.Cursor := crHourglass;

   Buffer := nil;
   Continue := 1;
   BuffLen := 0;

   LineCount := 50;                                             // Line Count( 50 line )

   Code := DcamInitialize();                                    // Initialize DLL
   Code := DcamOpen();                                          // Open the device
   Code := DcamStop();                                          // Stop acquisition

   Code := DcamSetGain(1);                                      // Set the gain 1
   Code := DcamSetOffset(40);                                   // Set the offset 10
   Code := DcamSetBinning(DCAM_BINNING_FULL);                   // Set the Full line binning
   Code := DcamSetTriggerPolarity(DCAM_TRIGPOL_NEGATIVE);       // Set the trigger polarity negative
   Code := DcamSetTriggerMode(DCAM_TRIGMODE_INT2);              // Set the trigger mode "Internal Mode"

   Code := DcamSetMeasureDataCount( LineCount );					      // Set the line count 50

   Code := DcamGetBitPerPixel( BitSize );					              // Get the bit size
   Code := DcamGetImageSize(Width, Height);                     // Get the image size
   BuffLen := Width * Height;

   MemHandle := GlobalAlloc(GMEM_DDESHARE or GMEM_MOVEABLE, (BuffLen * LineCount) * 2);
   Buffer := PWord(GlobalLock(MemHandle));

   Code := DcamCapture(PChar(Buffer), (BuffLen * LineCount) * 2);

   while Continue = 1 do
   begin
      DcamWait(WaitStat, 0);
      if WaitStat = 0 Then
      Continue := 0;
   end;

   // Save data
   DataSave('Sample.txt', Buffer, Width, Height, LineCount);

   GlobalUnlock(MemHandle);
   GlobalFree(MemHandle);
   DcamStop();
   DcamClose();
   DcamUninitialize();

   Screen.Cursor := OldCursor;
end;

// Save data
procedure TForm1.DataSave(FName: String; Buffer: PWord; Width: Integer; Height: Integer; Frame: Integer);
var
 tf: TextFile;
 CountW, CountH, CountF, ImageSize, Index: Integer;
 DataStr: String;
 PData: PWord;
begin
   AssignFile( tf, FName );
   Rewrite( tf );

   ImageSize := Width * Height;
   PData := Buffer;
   for CountF := 0 To Frame-1 do
   begin
      Index := (ImageSize * CountF) * 2;
      for CountH := 0 To Height-1 do
      begin
         DataStr := '';
         for CountW := 0 To Width-1 do
         begin
            DataStr := DataStr + Format( '%d', [PWord(PData)^] ) + ',';
            inc(PData);
         end;
         Writeln( tf, DataStr);
      end;
   end;

   CloseFile( tf );
end;

// FormCreate
procedure TForm1.FormCreate(Sender: TObject);
begin
   LoadDLL;
end;

// FormClose
procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   FreeDLL;
end;

end.
