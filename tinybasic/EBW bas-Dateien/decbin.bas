100 REM "EBW dezimal nach binaer"
110 REM "Initialize arrays for binary numbers & GPIOs"
200 DIM N(8)
220 DIM L(8)
230 READ L0
240 FOR I=1 To L0 : READ L(I) : NEXT I
250 REM FOR I=1 TO L0 : PRINT L(I) : NEXT I
260 FOR I=1 TO L0 : PINM L(I), 1 : NEXT I
290 REM "Endless loop with 'FOR J'"
300 PRINT "Type 'q' to quit or 'decimal number'"
310 FOR J
320 	FOR I=1 TO L0 : N(I)=0 : NEXT I
330 	INPUT "Eingabe: ", T$
340 	IF T$="q" THEN 700
350		D=VAL(T$)
360		IF SGN(D)=(-1) THEN 700
370		IF D>255 THEN 700
380 	PRINT "Dezimal=", D
390 	P=1
400		REM "Endless loop with 'FOR I'"
410 	FOR I
420 		R=D % 2
430 		REM PRINT "R: ",r
440 		IF R=1 THEN N(P)=1
450 		D=INT(D/2)
460 		REM PRINT "D: ",D
470 		P=P+1
480 		IF D=0 THEN BREAK
490 	NEXT I
500		PUT "B","i","n","a","r","y","="
510 	PUT (N(8)+48),(N(7)+48),(N(6)+48),(N(5)+48)
520 	PUT (N(4)+48),(N(3)+48),(N(2)+48),(N(1)+48), 13, 10
530 	FOR I=1 TO L0
540 		DWRITE L(I), N(I)
550 	NEXT I
600 NEXT J
700 FOR I=1 TO L0 : DWRITE L(I), 0 : NEXT
710 PRINT "'quit' or 'false number' 'run' again"
720 END
800 DATA 8
820 DATA      32,33,25,26,27,17,16,4
830 REM       "1/ 2/ 4/ 8/16/32/64/128"
