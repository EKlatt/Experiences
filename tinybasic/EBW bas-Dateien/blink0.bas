100 REM "Blink from Arduino examples"
110 REM "setup() put your setup code here, to run once:"
120 L=14
130 PINM L ,1
200 REM "loop() put your main code here, to run repeatedly:"
210 PRINT "Type 'q' to exit!"
220 FOR I
230 GET Q : IF Q="q" THEN END
240 DWRITE L, 1
250 DELAY 1000
260 DWRITE L, 0
270 DELAY 1000
300 NEXT
