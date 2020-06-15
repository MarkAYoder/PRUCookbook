export TARGET=uart1.pru0
echo TARGET=$TARGET

machine=$(awk '{print $NF}' /proc/device-tree/model)
echo -n $machine
if [ $machine = "Black" ]; then
    echo " Found"
    # Configure tx
    config-pin P9_24 pru_uart
    # Configure rx
    config-pin P9_26 pru_uart
elif [ $machine = "AI" ]; then
    echo " Found"
    echo "See AI chapter for configuring via device tree"
elif [ $machine = "Blue" ]; then
    echo " Found"
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    # Configure tx
    config-pin P1_06 pru_uart
    config-pin P2_09 pru_uart
    # Configure rx
    config-pin P1_12 pru_uart
    config-pin P2_11 pru_uart
else
    echo " Not Found"
    pins=""
fi
