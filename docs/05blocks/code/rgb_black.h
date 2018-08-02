//Black - Not tested
// These are from https://github.com/FalconChristmas/fpp/blob/master/src/pru/PocketScrollerV1.hp
// _gpio tells which gpio port and _pin tells which bit in the port
// The first 1 in r11 is for the J1 connector
// See the githuub file for the other connectors

#define r11_gpio 2
#define r11_pin 9
#define g11_gpio 2
#define g11_pin 11
#define b11_gpio 2
#define b11_pin 10

#define r12_gpio 2
#define r12_pin 12
#define g12_gpio 2
#define g12_pin 22
#define b12_gpio 2
#define b12_pin 23

#define pru_latch 1	// These are the bit positions in R30
#define pru_oe    0
#define pru_clock 2

// Control pins are all in GPIO2
// The pocket has these on R0, the code needs to be changed for this work work
#define gpio_sel0 13 /* must be sequential with sel1 and sel2 */
#define gpio_sel1 14
#define gpio_sel2 15
#define gpio_sel3 16
#define gpio_sel4 17
