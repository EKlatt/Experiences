100 REM "Melody from Arduino examples"
110 REM "Read Notes N0(), tones T(), and durations D()"
120 READ N
130 DIM N0(N) : FOR I=1 TO N : READ N0(I) : NEXT
140 READ N
150 DIM T(N) : FOR I=1 TO N : READ T(I) : NEXT
160 DIM D(N) : FOR I=1 TO N : READ D(I) : NEXT
170 REM "setup() put your setup code here, to run once:"
180 FOR I=1 TO N
190 D=1000/D(I)
200 IF T(I)=0 THEN T=0 ELSE T=N0(T(I))
210 PLAY 2, T, D
220 DELAY D*13/10
230 NEXT
240 PLAY 2, 0
250 END
300 REM "loop() put your main code here, to run repeatedly:"
310 REM "Pitches of 89 notes"
410 DATA 89
420 DATA 31, 33, 35, 37, 39, 41, 44, 46
430 DATA 49, 52, 55, 58, 62, 65, 69, 73
440 DATA 78, 82, 87, 93, 98, 104, 110, 117
450 DATA 123, 131, 139, 147, 156, 165, 175, 185
460 DATA 196, 208, 220, 233, 247, 262, 277, 294
470 DATA 311, 330, 349, 370, 392, 415, 440, 466 
480 DATA 494, 523, 554, 587, 622, 659, 698, 740 
490 DATA 784, 831, 880, 932, 988, 1047, 1109, 1175 
500 DATA 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865
510 DATA 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960
520 DATA 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699 
530 DATA 4978
540 REM "The melody of N notes and durations"
550 DATA 8
560 DATA 37, 32, 32, 34, 32, 0, 36, 37
570 DATA 4, 8, 8, 4, 4, 4, 4, 4