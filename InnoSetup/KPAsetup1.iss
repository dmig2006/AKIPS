; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

;�������� ���������
#define MyAppName "9M311-1M"
;������ ���������
#define MyAppVersion "1.0"
;������������ ������������ �� ����� ������������ ������� �� ���� ������� ������
#define MyAppPublisher "�� ""������� ""����������"""
;���� ������������
#define MyAppURL "https://kalashnikov.com"
;�������� ��� ����� ���������
#define MyAppExeName "kpa_new.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{45B0C352-9212-4DE4-B94A-EABF68DD661B}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
;����� ���� ����� ������� ������������
OutputDir=.\install
OutputBaseFilename=9M311-1M_Setup
Compression=lzma
SolidCompression=yes
ChangesEnvironment=yes
;������ ������������, ��� ������������� ��������
SetupIconFile=C:\Project\kpa_new_test\bin\��link.ico
;������ ��������������, ���� ���� ��������
UninstallDisplayIcon=C:\Project\kpa_new_test\bin\��link.ico

;����� �� ����������� ������ �� ������, ����� ������������� ���� � dll ������ � ���������� �����
[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "QT_QPA_PLATFORM_PLUGIN_PATH"; ValueData: ".\bin"; AfterInstall: RefreshEnvironment;
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "PATH"; ValueData: ".\bin;{olddata}"; AfterInstall: RefreshEnvironment;

[Code]
#include "installPath.iss"
procedure CurStepChanged(CurStep: TSetupStep);
  begin
    if CurStep = ssPostInstall then
    begin
      //SetEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('Path'));
      //SetEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('QT_QPA_PLATFORM_PLUGIN_PATH'));
    end;
  end;

  procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
  begin
    if CurUninstallStep = usUninstall then
    begin
      DeleteEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('Path'));
      //DeleteEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('QT_QPA_PLATFORM_PLUGIN_PATH'));
      RegDeleteValue(HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'QT_QPA_PLATFORM_PLUGIN_PATH');
    end;                                                                                    
  end;


  const
  SMTO_ABORTIFHUNG = 2;
  WM_WININICHANGE = $001A;
  WM_SETTINGCHANGE = WM_WININICHANGE;

type
  WPARAM = UINT_PTR;
  LPARAM = INT_PTR;
  LRESULT = INT_PTR;

function SendTextMessageTimeout(hWnd: HWND; Msg: UINT;
  wParam: WPARAM; lParam: PAnsiChar; fuFlags: UINT;
  uTimeout: UINT; out lpdwResult: DWORD): LRESULT;
  external 'SendMessageTimeoutA@user32.dll stdcall';  

procedure RefreshEnvironment;
var
  S: AnsiString;
  MsgResult: DWORD;
begin
  S := 'Environment';
  SendTextMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0,
    PAnsiChar(S), SMTO_ABORTIFHUNG, 5000, MsgResult);
end;




//����� ���������� ����� ����������� ������� ����� �������
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
;������� �� �������� ������ �������� ������� � ������
[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1
;� ����� [Files] ���������� ���� � ������ ������� ���������� �������� � ������������
;� ���� ��������� ������ ������������ ���������� ���� ��������� ���������
[Files]
Source: "..\bin\kpa_new.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\dll1\libgcc_s_dw2-1.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\libGLESv2.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\qminimal.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\qoffscreen.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5Cored.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5Guid.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5OpenGL.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5QuickWidgets.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5SerialPortd.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5WinExtras.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\qwindows.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\libstdc++-6.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\libwinpthread-1.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5Core.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5Gui.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\dll1\Qt5SerialPort.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\\\bin\dll1\Qt5Widgets.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\bin\��link.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\translate\QtLanguage_ru.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\translate\QtLanguage_en.qm"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\help.docx"; DestDir: "{app}"; Flags: ignoreversion
;Source: "C:\Project\kpa_new_test\bin\kpa_new .bat"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files


;������, ��� ������������� ��������
[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\��link.ico" 
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\��link.ico"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
;Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: runasoriginaluser


;��� ������������� ��������� ����� � �������� �����
[UninstallDelete]
Type: files; Name: "{userdesktop}\Shortcut KPA.lnk"
Type: files; Name: "{commondesktop}\Shortcut KPA.lnk"
