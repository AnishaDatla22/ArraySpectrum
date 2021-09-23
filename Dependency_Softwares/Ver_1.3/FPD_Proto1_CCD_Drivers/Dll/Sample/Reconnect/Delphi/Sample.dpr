program Sample;

uses
  Forms,
  uHamamatsu_LOAD in 'uHamamatsu_LOAD.pas',
  uMain in 'uMain.pas' {fMain};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfMain, fMain);
  Application.Run;
end.
