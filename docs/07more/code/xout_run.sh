# Be sure to start PRU 0 before PRU 1.  PRU 0 will wait for PRU 1 to signal it.
make TARGET=xout.pru0
make TARGET=xin.pru1
