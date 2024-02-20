@echo off

setlocal enabledelayedexpansion

set mode=release
set outDir=bin
set outname=main.exe
set sourceDir=src
set dependendyDir=dependencies

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
set files=
for /R "%sourceDir%" %%F in (*.cpp) do (
    set "files=!files! "%%F""
)

set options=

if "%mode%"=="debug" (
    set options=-fdiagnostics-color=always -g -Og
)

g++ ^
    %options% ^
    !files! ^
    -o %outDir%\%mode%\%outname% ^
    -I%dependendyDir%/include ^
    -L%dependendyDir%/lib ^
    -lopengl32 ^
    -lglew-2-1-0/glew32 ^
    -llib-mingw-w64/glfw3 ^
    -mwindows

endlocal


@REM If you use MinGW, you can use -mwindows flag.
@REM this will mark the program as a gui application and no console will be attached. redirect console output or attach a console manually
@REM default system linked libs visual studio for windows
@REM kernel32.lib
@REM user32.lib
@REM gdi32.lib
@REM winspool.lib
@REM comdlg32.lib
@REM advapi32.lib
@REM shell32.lib
@REM ole32.lib
@REM oleaut32.lib
@REM uuid.lib
@REM odbc32.lib
@REM odbccp32.lib