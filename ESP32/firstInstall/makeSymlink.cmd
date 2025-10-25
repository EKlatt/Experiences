@echo off
setlocal

rem === Pfad zu deiner portablen IDE anpassen, falls nötig === 
set PORTABLE_DIR=%~dp0

rem === Versteckte Arduino-Verzeichnisse definieren === 
set ARDUINO_USER_DIR=%USERPROFILE%\.arduinoIDE
set ARDUINO_LOCAL_DIR=%LOCALAPPDATA%\Arduino15

echo ============================================================
echo   Arduino IDE 2 Symlinks erzeugen bei kopierter Installation
echo ============================================================
echo Portable-Verzeichnis: %PORTABLE_DIR% 
echo Benutzerverzeichnis:  %ARDUINO_USER_DIR% 
echo AppData-Verzeichnis:  %ARDUINO_LOCAL_DIR% 
echo.
echo Wenn nicht Strg+c

pause

rem --- Symlinks (Junctions) anlegen ---
if not exist "%ARDUINO_USER_DIR%" (
    echo Erstelle Link: %ARDUINO_USER_DIR% nach %PORTABLE_DIR%.arduinoIDE
    mklink /J "%ARDUINO_USER_DIR%" "%PORTABLE_DIR%.arduinoIDE"
)
echo .
if not exist "%ARDUINO_LOCAL_DIR%" (
    echo Erstelle Link: %ARDUINO_LOCAL_DIR% nach %PORTABLE_DIR%Arduino15
    mklink /J "%ARDUINO_LOCAL_DIR%" "%PORTABLE_DIR%Arduino15"
)

pause
endlocal
exit /b

