; This is an example of how to call an assembly routine from C with a retun value.
;	Mark A. Yoder, 9-July-2018

	.cdecls "delay-test2.pru0.c"

	.global my_delay_cycles
my_delay_cycles:
delay:
	sub		r14,   r14, 1		; The first argument is passed in r14
	qbne	delay, r14, 0
	
	ldi		r14, TEST		; TEST is defined in delay-test2.c
							; r14 is the return register

	jmp		r3.w2			; r3 contains the return address