program Sample;

uses
  Forms,
  uMain in '.\uMain.pas' {Form1},
  uHamamatsu_LOAD in '.\uHamamatsu_LOAD.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.       
