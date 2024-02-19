@echo off

setlocal enabledelayedexpansion

set mode=release
set outDir=bin
set outname=main.exe
set sourceDir=src
set dependendiesDir=dependencies

rem Check if an argument is provided
if "%~1"=="" (
    set mode=debug
    rem set build=%~1
)

echo Build %mode% candidate...

rem create out folders
mkdir %outDir%\release 2>nul
mkdir %outDir%\debug 2>nul
del /q %outDir%\release\%outname% 2>nul
del /q %outDir%\debug\%outname% 2>nul

rem find all cpp recusive in sorce dir
set "files="
for /R "%sourceDir%" %%F in (*.cpp) do (
    set "files=!files! "%%F""
)


if "%mode%"=="release" (
    g++ !files! -o bin\%mode%\%outname%
    g++ ^
        -I%dependendiesDir%/include !files! ^
        -o bin\%mode%\%outname% ^
        -L%dependendiesDir%/lib ^
        -llib-mingw-w64/glfw3
) else (
    g++ ^
        -fdiagnostics-color=always ^
        -g -Og ^
        -I%dependendiesDir%/include !files! ^
        -o %outDir%\%mode%\%outname% ^
        -L%dependendiesDir%/lib ^
        -llib-mingw-w64/glfw3
    )
endlocal