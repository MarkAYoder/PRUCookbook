#if AI == 1
#warning "Found AI"
#define GPIO1 0x4AE10000
#define GPIO2 0x48055000
#define GPIO3 0x48057000
#define GPIO4 0x48059000
#define GPIO5 0x4805B000
#define GPIO6 0x4805D000
#define GPIO7 0x48051000
#define GPIO8 0x48053000
// GPIO3
#define USR0 (1<<17)
#define USR2 (1<<15)
#define USR3 (1<<14)
#define USR4 (1<< 7)
// GPIO5
#define USR1 (1<< 5)
// GPIO6
#define P9_25   (0x1<<17)
// GPIO8
#define P8_17   (0x1<18)
// R30 bits - Output on pru1_1
#define P9_14	(0x1<<14)
#define P9_16	(0x1<<15)
#define P8_15	(0x1<<16)
#define P8_26	(0x1<<17)
#define P8_16	(0x1<<18)
// R31 bits - Input on pru1_1
#define P8_18	(0x1<<5)
#define P8_19	(0x1<<6)
#define P8_13	(0x1<<7)

#else

#warning "Found else"
#define GPIO0 0x44E09000
#define GPIO1 0x4804C000
#define GPIO2 0x481AC000
#define GPIO3 0x481AE000

// GPIO 1
#define USR0 (1<<21)
#define USR1 (1<<22)
#define USR2 (1<<23)
#define USR3 (1<<24)

#endif

#define GPIO_CLEARDATAOUT	0x190/4	// /4 to convert from byte address to word address
#define GPIO_SETDATAOUT 	0x194/4
#define GPIO_DATAOUT		0x138/4   // For reading the GPIO registers
