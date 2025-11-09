@echo off
setlocal

rem === Pfad zu deiner portablen IDE anpassen, falls nötig ===
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
	echo    --- Es existiert eine Konfiguration! ---
	echo    --- Loesche die Konfiguration        ---
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

