100 REM "EBW 1602A LCD 2x16"
200 REM "hardware-arduino.h 74 #define ARDUINOLCDI2C"
220 REM "hardware-arduino.h 1203 dsp_rows=2"
230 REM "hardware-arduino.h 1204 dsp_columns=16"
300 REM "Arduino DFRobot_AS3935-master LCD-library"
320 REM "https://github.com/slviajero/tinybasic/tree/main/Basic1/TinyVT52"
330 REM "https://github.com/slviajero/tinybasic/blob/main/MANUAL.md"
340 REM "Terminal emulation and VT52 capability on display systems"
400 REM "Clear screen"
450 PUT &2,27,"E"
500 REM "Make cursor visible"
550 PUT &2,27,"e"
600 REM "Seperator ';' no CRLF"
620 PRINT &2,"Line 1";
630 PRINT &2,"EBW"
640 PRINT &2,"Line 2"
650 DELAY (2000)
660 REM "Cursor home"
680 PUT &2,27,"H"
690 REM "Clear to end of line"
700 PUT &2,27,"K"
710 DELAY (2000)
720 PRINT &2,"Enno"
730 DELAY (2000)
800 PUT &2,27,"K"
820 DELAY (2000)
850 PRINT &2,"Cursor up"
900 PUT &2,27,"A"
920 REM "Clear to end of line"
930 PUT &2,27,"K"
950 PRINT &2,"Uhr"
960 PUT &2,27,"H"
970 PRINT &2,"...."
980 PRINT &2,"::::";
1000 PUT &2,27,"A"
1110 PRINT &2,"okay"
1200 REM "Alternatives"
1220 REM "Clear screen"
1240 PUT &2,12
1250 REM "variables @X, @Y contain the cursor position"
1250 @X=0: @Y=0: PUT &2,"X"
1260 @X=5: @Y=0: PUT &2,"Z"
1270 @X=5: @Y=1: PUT &2,"A"
1280 @X=5: @Y=0: PRINT &2,1.234
