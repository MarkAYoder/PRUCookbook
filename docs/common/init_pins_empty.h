// Defins an empty table to write_init_pins wont' complain

#pragma DATA_SECTION(init_pins, ".init_pins")
#pragma RETAIN(init_pins)
const char init_pins[] =
	"\0\0";
