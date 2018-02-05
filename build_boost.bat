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

pushd .\lib\boost
if not exist .\bin (
    if not exist .\b2.exe (
        bootstrap.bat gcc
    )
    b2 toolset=gcc variant=release link=shared threading=multi runtime-link=shared address-model=32 --layout=system ^
    --with-program_options --prefix=./bin install
    b2 toolset=gcc variant=release link=shared threading=multi runtime-link=shared address-model=32 --layout=system ^
    --with-program_options --prefix=./bin install
    REM doesn't build libraries the first time, don't know why.
)
popd
mklink libboost_program_options.dll .\lib\boost\bin\lib\libboost_program_options.dll
