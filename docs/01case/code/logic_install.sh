# Instructions for installing BeagleLogic
# From: https://github.com/abhishek-kakkar/BeagleLogic/wiki
wget https://github.com/abhishek-kakkar/BeagleLogic/archive/release-v1.1.tar.gz
tar xaf release-v1.1.tar.gz

# First PRU
cd BeagleLogic-release-v1.1/cd BeagleLogic-release-v1.1/
make

sudo cp beaglelogic-pru0 /lib/firmware/am335x-pru0-fw
sudo cp beaglelogic-pru1 /lib/firmware/am335x-pru1-fw

# Now the kernel driver
sudo apt install linux-headers-`uname -r`

# If the linux-headers fails to install, try updating your kernel, and then installing
/opt/scripts/tools/update_kernel.sh

