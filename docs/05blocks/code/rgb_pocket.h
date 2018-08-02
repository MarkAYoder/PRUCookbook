// Pocket
// These are from https://github.com/FalconChristmas/fpp/blob/master/src/pru/PocketScrollerV1.hp
// _gpio tells which gpio port and _pin tells which bit in the port
// The first 1 in r11 is for the J1 connector
// See the githuub file for the other connectors

#define r11_gpio 1
#define r11_pin 20
#define g11_gpio 1
#define g11_pin 28
#define b11_gpio 1
#define b11_pin 25

#define r12_gpio 1
#define r12_pin 26
#define g12_gpio 1
#define g12_pin 27
#define b12_gpio 1
#define b12_pin 18

#define pru_latch  0	// These are the bit positions in R30
#define pru_oe     7
#define pru_clock  1

#define pru_sel0   2	// These are called LA, LB, LC and LD in the python code
#define pru_sel1   3	// Also bit positions
#define pru_sel2   4
#define pru_sel3   5
