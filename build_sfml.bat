@echo off

:: see: https://sites.google.com/site/eneerge/scripts/batchgotadmin
:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params = %*:"=""
    echo UAC.ShellExecute "cmd.exe", "/c %~s0 %params%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"
:--------------------------------------

pushd .\SFML
if not exist .\lib\libsfml-graphics.dll (
    cmake -G"MinGW Makefiles" .
    mingw32-make sfml-graphics
)
popd
mklink sfml-graphics-2.dll .\lib\SFML\lib\sfml-graphics-2.dll
mklink sfml-window-2.dll .\lib\SFML\lib\sfml-window-2.dll
mklink sfml-system-2.dll .\lib\SFML\lib\sfml-system-2.dll
