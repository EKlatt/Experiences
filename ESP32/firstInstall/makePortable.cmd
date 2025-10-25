@echo off
setlocal

rem === Pfad zu deiner portablen IDE anpassen, falls nötig === 
set PORTABLE_DIR=%~dp0

rem === Versteckte Arduino-Verzeichnisse definieren === 
set ARDUINO_USER_DIR=%USERPROFILE%\.arduinoIDE
set ARDUINO_LOCAL_DIR=%LOCALAPPDATA%\Arduino15

echo ============================================
echo   Arduino IDE 2 Portable Starter
echo ============================================
echo Portable-Verzeichnis: %PORTABLE_DIR% 
echo Benutzerverzeichnis:  %ARDUINO_USER_DIR% 
echo AppData-Verzeichnis:  %ARDUINO_LOCAL_DIR% 
echo.

rem --- Sicherstellen, dass die Zielordner existieren --- 
rem --- move erzeugt Ordner
rem if not exist "%PORTABLE_DIR%\Arduino15" mkdir "%PORTABLE_DIR%\Arduino15"


rem --- Falls Originalordner existieren, verschieben wir sie einmalig --- 
if exist "%ARDUINO_USER_DIR%" (
    echo Verschiebe %ARDUINO_USER_DIR% nach %PORTABLE_DIR%.arduinoIDE ...
    move "%ARDUINO_USER_DIR%" "%PORTABLE_DIR%.arduinoIDE"
)

if exist "%ARDUINO_LOCAL_DIR%" (
    echo Verschiebe %ARDUINO_LOCAL_DIR% nach %PORTABLE_DIR% ...
    move "%ARDUINO_LOCAL_DIR%" "%PORTABLE_DIR%"
)

rem --- Symlinks (Junctions) anlegen ---
if not exist "%ARDUINO_USER_DIR%" (
    echo Erstelle Link: %ARDUINO_USER_DIR% nach %PORTABLE_DIR%.arduinoIDE
    mklink /J "%ARDUINO_USER_DIR%" "%PORTABLE_DIR%.arduinoIDE"
)

if not exist "%ARDUINO_LOCAL_DIR%" (
    echo Erstelle Link: %ARDUINO_LOCAL_DIR% nach %PORTABLE_DIR%Arduino15
    mklink /J "%ARDUINO_LOCAL_DIR%" "%PORTABLE_DIR%Arduino15"
)

echo.

pause
endlocal
exit /b

