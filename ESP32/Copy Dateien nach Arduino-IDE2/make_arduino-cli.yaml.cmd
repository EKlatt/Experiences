@echo off
setlocal

rem === Pfad zu deiner portablen IDE, hier der Ordner der Batch-Datei         ===
rem === Die Batch-Datei "make_arduino-cli.yaml.cmd" muss im IDE-Ordner liegen ===
set PORTABLE_DIR=%~dp0

rem === Pfad zum portablen "...\AppData\Local\Appdata15" Verzeichnis ===
set ARDUINO15=%~dp0Arduino15

rem === Pfad zum portablen "...\AppData\Local\Sketchbook" Verzeichnis ===
set SKETCHBOOK=%~dp0Sketchbook

rem === CLI-Konfigurationsdatei definieren ===
set CLI_CONFIG=arduino-cli.yaml 

rem === Versteckte Arduino-Nutzer-Konfiguration definieren ===
set ARDUINO_USER_DIR=%USERPROFILE%\.arduinoIDE

echo ===========================================================
echo    Arduino IDE 2 Portable Starter
echo ===========================================================
echo    Portable-Verzeichnis: %PORTABLE_DIR%
echo    Portable-Arduino15:   %ARDUINO15%
echo    Sketchbook:           %SKETCHBOOK%
echo    Benutzerverzeichnis:  %ARDUINO_USER_DIR%
echo.

echo ===========================================================
echo    Erzeuge %ARDUINO_USER_DIR%
echo    Erzeuge %CLI_CONFIG% in %ARDUINO_USER_DIR%
echo.
echo ===========================================================


rem === Falls Ordner existiert: Abbruch ===
if exist "%ARDUINO_USER_DIR%" (
    echo    --- Die %ARDUINO_USER_DIR% existiert!
	echo    --- Die IDE 2 hat eine Konfiguration! ---
	echo    --- Bennene die Konfiguration um      ---
	echo    --- oder loesche sie!                 ---
)

if not exist "%ARDUINO_USER_DIR%" (
	echo    Erzeuge "%ARDUINO_USER_DIR%"
	md "%ARDUINO_USER_DIR%" 
	echo.
	echo ===========================================================
)

if not exist "%ARDUINO_USER_DIR%\%CLI_CONFIG%" (
	echo    Erzeuge %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo ===========================================================	
	echo board_manager:                          > %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo  additional_urls: []                   >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo directories:                           >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo  builtin:                              >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo   libraries: %PORTABLE_DIR%libraries   >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo  data: %ARDUINO15%                     >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo  user: %SKETCHBOOK%                    >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
	echo locale: de                             >> %ARDUINO_USER_DIR%\%CLI_CONFIG%
)


:ende
echo === Ende ===
pause

endlocal
exit /b

