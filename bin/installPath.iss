///////////////////////////////////////////////////////////////////////////////////////////////////
// Сохранить сей манускрипт как "env-tools.iss" (без кавычек)
//
//  По мотивам сообщения тов. omals и zhe_zho от 02-12-2008 09:21
//  http://forum.ru-board.com/topic.cgi/tools.cgi?action=notifyon&forum=5&topic=27438&start=1685
//
//  Для применения нового значения %PATH% после завершения инсталяции
//  необходимо добавить в секцию:
//
//  [Setup]
//  ChangesEnvironment=yes
//
//  В скрипт подключается так:
//
//  [_Code]                           "_Code" - Из-за ограничений тегов форума. Имеется ввиду секция Code
//  #include "env-tools.iss"
//
//  Процедуры описаны в env-tools.iss:
//
//  SetEnvironmentPath('<ваш_путь>');    // Добавляет <ваш_путь> к системному %PATH% 
//  DeleteEnvironmentPath('<ваш_путь>'); // Удаляет <ваш_путь> из системного %PATH%
//
//  Вызывать по смыслу в нужном месте инсталляции или деинсталяции 
//  Например:
//  {После инсталляции:}
//  procedure CurStepChanged(CurStep: TSetupStep);
//  begin
//    if CurStep = ssPostInstall then
//    begin
//      SetEnvironmentPath(ExpandConstant('{app}\dll'));
//    end;
//  end;
// 
//  {Перед деинсталляцией:}
//  procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
//  begin
//    if CurUninstallStep = usUninstall then
//    begin
//      DeleteEnvironmentPath(ExpandConstant('{app}\bin'));
//    end;
//  end;
//        
///////////////////////////////////////////////////////////////////////////////////////////////////

procedure SetEnvironmentPath(NewPath: String; EnvName: String);
var
  PathStr: String;
begin
  {Получаем значение текущего системного %PATH%}
  if RegQueryStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, PathStr) then
begin
  	{Ищем NewPath в текущем системном %PATH%}
  	if Pos(NewPath, PathStr) <= 0 then // Если в текущем %PATH% не найдено NewPath;
  	begin
    		PathStr := PathStr + ';' + NewPath;
    		RegWriteStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, PathStr);
  	end;
end
 else 
  begin
    //RegWriteStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, NewPath);
    RegWriteStringValue(HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, NewPath);
    //RegQueryStringValue(HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, NewPath)
 end;
end;

procedure DeleteEnvironmentPath(OldPath: String; EnvName: String);
var
  PathStr: String;
  StartPos, Len: Integer;
begin
  {Получаем значение текущего системного %PATH%}
  RegQueryStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, PathStr);

  {Ищем OldPath c ";" в текущем системном %PATH%}
  StartPos := Pos(OldPath + ';', PathStr); //индекс начала вхождения OldPath c ";"
  if StartPos > 0 then // Если в текущем %PATH% найден OldPath;
  begin
    Len := Length(OldPath + ';');   //длина строки OldPath c ";"
    Delete(PathStr, StartPos, Len); // удаляем из текущего системного %PATH% (PathStr) строку OldPath c ";"
    {Записываем изменения в реестр}
    RegWriteStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, PathStr);
    Exit;
  end;

  {Ищем OldPath без ";" в текущем системном %PATH%}
  StartPos := Pos(OldPath, PathStr);
  if StartPos > 0 then // Если в текущем %PATH% найден OldPath без ";"
  begin
    Len := Length(OldPath); //индекс начала вхождения OldPath без ";"
    Delete(PathStr, StartPos, Len); // удаляем из текущего системного %PATH% (PathStr) строку OldPath без ";"
    {Записываем изменения в реестр}
    RegWriteStringValue(HKLM,'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', EnvName, PathStr);
  end;
  RegDeleteKeyIncludingSubkeys(HKLM, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment\QT_QPA_PLATFORM_PLUGIN_PATH')
end;
