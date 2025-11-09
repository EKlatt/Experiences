echo off
setlocal
cls

rem      ==== Hier editieren ====================================
rem      Hier Deinen Pfad zur zentralen Library, sollte ein 
rem      Unterordner von einem Sketchbook-Ordner sein, eintragen:
rem      Ersetze den Pfad hinter "target=".
set target=C:\Users\Public\arduino-IDE2\Sketchbook\libraries

rem      Trage hier den Pfad zum neuen Sketchbook ein:
rem      Ersetze den Pfad hinter "newSketchbook=".
set newSketchbook=C:\Users\enno_\Desktop\ESP32

rem      Wenn Du den Dialog nicht mehr sehen moechtest, entferne
rem      "rem" vor dem goto ohneDialog
goto ohneDialog
rem      ==== Editieren Ende ====================================

rem      ===  System Link zum zentralen Library Ordner   ===
echo.
echo     ===  Symlink fuer projektbezogene "Sketchbook\libraries" erstellen ===
echo.
echo     Name der Batch-Datei: %~nx0
echo.
echo     Die IDE 2 legt zunaechst in jedem projektbezogenen
echo     Sketchbook einen "libraries-Ordner" an.
echo     Damit werden bisher installierte Libraries nicht mehr gefunden.
echo     Daher muesste man die bisher installierten
echo     Libraries in den neuen Sketchbook Ordner kopieren.
echo.     
echo     Abhilfe: Diese Batch-Datei erzeugt einen Systemlink auf einen
echo     zentralen Libraries-Ordner.
echo.

echo     Syntax: mklink /j "link" "target"
echo     "link" enthaelt den Pfad zum neunen Sketchbook-Ordner.
echo     "target" ist der Pfad zum zentralen Libraries-Ordner.
echo.
pause

cls
echo     Schritt 1, zentralen Libraries-Ordner erstellen:
echo     Die IDE 2 sei hier z.B. in "C:\Users\Public\arduino-IDE2"
echo     gespeichert.
echo. 
echo     Erstelle mit dem Explorer einen zentralen Libraries-Ordner,
echo     der ein Unterordner von einem zentralen "Sketchbook" sein 
echo     koennte z.B.:
echo        "C:\Users\Public\arduino-IDE2\Sketchbook\libraries".
echo.
echo     oder verwende den von der IDE angelegten Pfad in Dokumente.
echo.
echo     Setze die Ausfuehrung fort, wenn Du das getan hast!
echo.
pause

cls
echo     Schritt 2, editiere die Batch-Datei "MakeSymlink_1.cmd".
echo     Trage hinter "target=" einmalig den Pfad zum zentralen 
echo     Libraries-Ordner ein:
echo     Zum Beispiel:
echo       target=C:\Users\Public\arduino-IDE2\Sketchbook\libraries
echo.

echo     Schritt 3, trage jeweils den Pfad zum neuen Sketchbook ein.
echo     Trage hinter "newSketchbook=" den Pfad ein.
echo     Zum Beispiel:
echo       set newSketchbook=C:\Users\myname\Desktop\ESP32
echo       Achtung: Ersetze myname durch Deinen Namen!     
echo.
echo     Breche zum editieren die Batch-Ausfuehrung mit Ctrl+C ab!
echo     Batch-Datei editieren: Rechtsklick und dann "Im Editor bearbeiten".
echo     Anschliessend starte die editierte Batch-Datei erneut!
echo.
pause

cls
echo     Schritt 4:
echo     Die Ausfuehrung der Batch-Datei prueft das Vorhandensein
echo     des neuen Sketchbooks!
echo.
echo     Hier darf kein Ordner mit den Namen "libraries" existieren.
echo     Der Ordner "libraries" wird nun als "symbolic link" angelegt.
echo.

:ohneDialog
set link=%newSketchbook%\libraries
if exist %newSketchbook% (
 cd %newSketchbook%
 if not exist libraries (
   echo      mklink /J "%link%" "%target%"
   echo.
   mklink /J "%link%" "%target%"
   echo. 
 ) else (
     echo ============================================================ 
     echo     Fehler: "libraries besteht als Ordner oder Systemlink!
	 echo ============================================================
	 echo.
   )
)

:ende
echo ============================================================ 
echo     Hinweis: Will man einen Systemlink in einem weiteren
echo     Sketchbook-Ordner anlegen, muss der Eintrag
echo     "newSketchbook=" in dieser Datei geaendert werden.
echo     Diese Batch-Datei kann an einem beliebigen Ort liegen.
echo ============================================================ 
echo.

pause
endlocal
exit /b
