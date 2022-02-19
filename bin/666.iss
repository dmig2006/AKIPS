; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "KPA"
#define MyAppVersion "1"
#define MyAppPublisher "kalkon"
#define MyAppURL "http://www.example.com/"
#define MyAppExeName "kpa_new.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
ChangesEnvironment=yes
ChangesAssociations=yes
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
OutputDir=C:\Project\kpa_new_test\bin
OutputBaseFilename=KPAsetup
Compression=lzma
SolidCompression=yes
[Code]
#include "installPath.iss"
procedure CurStepChanged(CurStep: TSetupStep);
  begin
    if CurStep = ssPostInstall then
    begin
      SetEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('Path'));
      SetEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('QT_QPA_PLATFORM_PLUGIN_PATH'));
    end;
  end;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\Project\kpa_new_test\bin\kpa_new.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\libgcc_s_dw2-1.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\libGLESv2.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\qminimal.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\qoffscreen.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5Cored.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5Guid.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5OpenGL.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5QuickWidgets.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5SerialPortd.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5WinExtras.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\qwindows.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\libstdc++-6.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\libwinpthread-1.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5Core.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5Gui.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5SerialPort.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\dll\Qt5Widgets.dll"; DestDir: "{app}\dll"; Flags: ignoreversion
Source: "C:\Project\kpa_new_test\bin\kpa_new .bat"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
  begin
    if CurUninstallStep = usUninstall then
    begin
      DeleteEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('Path'));
      //DeleteEnvironmentPath(ExpandConstant('{app}\dll'), ExpandConstant('QT_QPA_PLATFORM_PLUGIN_PATH'));
      RegDeleteValue(HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'QT_QPA_PLATFORM_PLUGIN_PATH');
    end;                                                                                    
  end;
[UninstallDelete]
Type: files; Name: "{userdesktop}\Shortcut KPA.lnk"
Type: files; Name: "{commondesktop}\Shortcut KPA.lnk"
[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment\QT_QPA_PLATFORM_PLUGIN_PATH"; Flags: uninsdeletekey