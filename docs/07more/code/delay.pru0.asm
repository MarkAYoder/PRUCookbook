; This is an example of how to call an assembly routine from C.
;	Mark A. Yoder, 9-July-2018
	.global my_delay_cycles
my_delay_cycles:
delay:
	sub		r14,   r14, 1		; The first argument is passed in r14
	qbne	delay, r14, 0

	jmp		r3.w2			; r3 contains the return address