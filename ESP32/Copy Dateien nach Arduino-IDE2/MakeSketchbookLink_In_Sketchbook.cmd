@echo off
rem      === System Link zum zentralen Library Ordner ===
setlocal
echo     ===           Symlink erstellen               ===
echo     Syntax: mklink /J "link" "target"
echo     "link" ist der Pfad zum neunen/aktuellen Skechbook-Ordner
echo.
echo     Problem: Man muesste bei "Erstellung" eines Sketchbooks
echo     die bisher installierten Libraries (also das letzte Projekt)
echo     in den neuen Library-Ordner jeweils kopieren...
echo.

echo     Idee: Man erstellt einen zentralen Library-Ordner
echo     zum Beispiel:
echo     set target="C:\Users\Public\arduino-IDE2\Sketchbook\libraries"
echo.

echo     Trage hier zunaechst einmalig 
echo     den Pfad zum zentralen Library-Ordner ein:
echo     Trage hinter "target=" zum Beispiel
echo     den Pfad ein:
echo     C:\Users\Public\arduino-IDE2\Sketchbook\libraries
echo.
echo     Das Ergebnis ist:
echo     "target=C:\Users\Public\arduino-IDE2\Sketchbook\libraries"
echo     Breche die Batch-Ausfuehrung zum editieren mit Ctrl+C ab,
echo     und editiere die Batch-Datei.
echo.
pause

cls
REM       ==================================================================
REM        Hier deinen Pfad zur zentralen Library eintragen:
set target=C:\Users\Public\arduino-IDE2\Sketchbook\libraries
REM       ==================================================================

echo      Die Batch-Datei muss im neuen Sketchbook-Ordner liegen.
echo      Hier darf kein Ordner mit den Namen "libraries" vorhanden sein.
echo	  Wir erstellen anstelle des Ordners "libraries" einen Symlink.
echo.

echo      Der Ordner "libraries" wird nun als "symbolic link", 
echo      hier "link" genannt angelegt.

REM Ich hole mir den Sketchbook-Pfad vom aktuellen Speicherort der Batch-Datei
set newSketchbook=%~dp0

if exist %newSketchbook% (
  echo      set link="%newSketchbook%libraries"
  echo.
  set link=%newSketchbook%libraries
)  

if not exist %target% (
  echo      Erstelle %target%
  echo.
  md %target%
)

echo      mklink /J "C:\Users\enno_\Desktop\LED-Projekt\_Pastellfarben\libraries" "C:\Users\Public\arduino-IDE2\Sketchbook\libraries
echo.
mklink /J "%link%" "%target%"
echo.

:ende
pause
endlocal
exit /b
