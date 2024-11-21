;file:		calc.asm
; author:	<Sean Gor>
; date:		12/11/23
; description:
; This program calculates the sum, average, min and max of 5 dwords. It also computes the amount of dwords less than the average.
;----------------------------------------------------------------------------
		option	    casemap:none		;case sensitive
;----------------------------------------------------------------------------
		.data							;variables definitions

X0		dword	    5					;memory location X0 has the value 0Alh
X1		dword       1					;memory location X1 has the value 11001001b
X2		dword       100					;memory location X2 has the value 100
X3		dword		90					;memory location X3 has the value 90
X4		dword		-10					;memory location X4 has the value -10
sum		dword		0					;memory location sum has the value 0
avg		dword		0					;memory location avg has the value 0
max	    dword       5					;memory location max has the value of the first element
min		dword		5					;memory location min has the value 0
cnt		dword		0			        ;memory location cnt has the value 0

;----------------------------------------------------------------------------
		.code							;executable instructions (procedures/functions)

calc	proc	
		mov			eax, X0				;putting the value of X0 in register eax
	    mov			ebx, X1         	;putting the value of X1 in register ebx
		mov			ecx, X2				;putting the value of X2 in register ecx
	    mov			edx, X3				;putting the value of X3 in register edx
		mov			ebp, X4				;putting the value of X4 in register eex
	    add			eax, ebx			;adding the value of register ebx to value of register  eax
	    add			eax, ecx			;adding the value of register ecx to register eax
	    add			eax, edx			;adding the value of register edx to register eax
	    add			eax, ebp			;putting the value of register eax into the value sum    
		mov			sum, eax		    ;sum = eax
		cdq							    ;extending sign bit of eax into edx
		mov			ebx, 5				;ebx = 5 (divisor)
		IMUL		ebx					;dividing by 5 to obtain average for all numbers
		mov			avg, eax			;moving register eax to memory location avg	
		or			eax, ebx
		mov		    ebx, X0	  			;ebx contains min value
		mov		    eax, X1			    ;eax contains value of X1
		cmp		    eax, ebx			;comparing X1 with X0
		jl		    updateMin	        ;updates min if X0 < X1								
		jmp		    checkMin1           ;continues to next section

updateMin:
		mov	        ebx, eax            ;updates min to value of eax

checkMin1:
		mov		    eax, X2				;eax = X2
		cmp		    eax, ebx			;comparing X2 to current min
		jg		    updateMin2          ;jumps to updatemin2 section if X2 < min
		jmp		    checkMin2           ;continues to next section

updateMin2:
		mov			ebx, eax            ;updates ebx (min) to the value of eax

checkMin2:		
		mov		    eax, X3				;eax = X3
		cmp		    eax, ebx            ;comparing X3 to current min
		jg		    updateMin3			;jump to updateMin3 if X3 < min
		jmp		    checkMin3			;continues to next section

updateMin3:
		mov			ebx, eax			;updates ebx (min) to the value of eax

checkMin3:
		mov		    eax, X4			    ;eax = X4
		cmp		    eax, ebx		    ;comparing X4 to current min
		jg		    updateMin4			;jump to updateMin4 if X4 < min
		jmp		    next				;continues to next section

updateMin4:
		mov			ebx, eax			;updates ebx (min) to the value of eax
next: 
		mov			min, ebx			;saving value of ebx in min 
		mov		    ebx, max			;moving the initial max into ebx
		mov			eax, X1			    ;eax = X1
		cmp			eax, ebx			;comparing X1 to current max
		jg			updateMax			;jumps to updateMax if X1 > max
		jmp			next2				;continues to next section

updateMax:
		mov		    ebx, eax		    ;updates ebx (max) to the value of eax
next2:	
		mov		    eax, X2			    ;eax = X2
		cmp		    eax, ebx			;comparing X2 to current max
		jg		    updateMax1			;jumps to updateMax1 if X2 > max
		jmp		    next3				;continues to next section

updateMax1:
		mov		    ebx, eax			;updates ebx (max) to the value of eax
next3:	
		mov		    eax, X3			    ;eax = X3
		cmp		    eax, ebx			;comparing X3 to current max
		jg		    updateMax2			;jumps to updateMax2 if X3 > max
		jmp		    next4				;continues to next section

updateMax2:
		mov		    ebx, eax			;updates ebx (max) to the value of eax
next4:
		mov		    eax, X4				;eax = X4
		cmp		    eax, ebx			;comparing X4 to current max
		jg		    updateMax3			;jumpes to updateMax3 if X4 > max
		jmp		    next5				;continues to next section

updateMax3:
		mov		    ebx, eax			;updates ebx (max) to the value of eax
next5:
		mov			max, ebx			;max = ebx
		mov			eax, X0				;eax = X0
		cmp			eax, avg			;comparing X0 to the average value
		jl		    incCnt				;jumps to incCnt if X0 < avg
		jmp			next6				;continues to next section

incCnt:
		inc			cnt					;cnt = cnt + 1
next6:
		mov			eax, X1				;eax = X1
		cmp			eax, avg			;comparing X1 to the average value
		jl			incCnt1				;jumps to incCnt if X1 < avg
		jmp			next7				;continues to next section

incCnt1:
		inc			cnt					;cnt = cnt + 1
next7:	
		mov		    eax, X2				;eax = X2
		cmp			eax, avg			;comparing X2 to the average value
		jl			incCnt2				;jumpes to incCnt if X2 < avg
		jmp		    next8				;continues to next section

incCnt2:
		inc			cnt					;cnt = cnt + 1
next8:
		mov			eax, X3				;eax = X3
		cmp			eax, avg			;comparing X3 to the average value
		jl		    incCnt3				;jumes to incCnt if X3 < avg
		jmp		    next9				;continues to next section

incCnt3:	
		inc			cnt					;cnt = cnt + 1

next9:
		mov			eax, X4				;eax = X4
		cmp			eax, avg			;comparing X4 to the average value
		jl			incCnt4				;jumps to incCnt if X4 < avg
		jmp		    done				;continues to next section

incCnt4:
		inc			cnt					;cnt = cnt + 1
done:
		nop								;no opcode/operand
		ret								;return
calc    endp							;end function

getSum  proc
		mov		    eax, sum			;eax has value of sum
		ret								;return
getSum  endp							;end function

getAvg	proc							
		mov		    eax, avg			;eax has the value of avg
		ret								;return
getAvg	endp							;end function

getMin	proc
		mov		    eax, min			;eax has the value of min
		ret								;return
getMin	endp							;end function

getMax	proc
		mov		    eax, max			;eax has the value of max
		ret								;return
getMax	endp							;end function

getCnt	proc
		mov		    eax, cnt			;eax has the value of cnt
		ret								;return
getCnt	endp							;end function
		end								;required by Mr. Gates!
;----------------------------------------------------------------------------
