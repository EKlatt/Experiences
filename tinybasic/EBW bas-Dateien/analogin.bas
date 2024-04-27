100 REM "AnalogInput from Arduino examples"
120 REM "S is the analog sensor input, L the LED pin"
130 S=35
140 L=14
150 V=0
200 REM "setup() put your setup code here, to run once:"
210 PINM L, 1
220 PUT &2,12
230 REM "loop() put your main code here, to run repeatedly:"
240 PRINT "Type 'q' to exit!"
310 FOR I
320 GET Q : IF Q="q" THEN BREAK
330 V=AREAD(S)
340 V=MAP(V,0,4095,0,500) 
350	@X=0:@Y=0:PUT &2,27,"K":PRINT &2,V;
360 DWRITE L, 1
370 DELAY V
380 DWRITE L, 0
390 NEXT I
400 END
