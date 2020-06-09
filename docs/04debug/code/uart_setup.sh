export TARGET=uart1.pru0
echo TARGET=$TARGET

# Configure tx
config-pin P9_24 pru_uart
# Configure rx
config-pin P9_26 pru_uart
