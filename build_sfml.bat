@echo off

pushd .\SFML
if not exist .\lib\libsfml-graphics.dll (
    cmake -G"MinGW Makefiles" .
    mingw32-make sfml-graphics
)
popd
