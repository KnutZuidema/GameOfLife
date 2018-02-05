@echo off

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
