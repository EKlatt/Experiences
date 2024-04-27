100 REM "Button from Arduino examples"
110 REM "setup() put your setup code here, to run once:"
120 B=13
130 L=14
140 S=0
150 PINM L, 1
160 PINM B, 0 
200 REM "loop() put your main code here, to run repeatedly:"
210 PRINT "Type 'Q' to exit!"
220 FOR I
230 GET Q : IF Q="q" OR Q="Q" THEN END
240 S=DREAD(B)
250 IF S=1 THEN DWRITE L, 1 ELSE DWRITE L, 0
260 NEXT
