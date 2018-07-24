# Instructions for installing BeagleLogic
# https://beaglelogic.readthedocs.io/en/latest/index.html
# From: https://github.com/abhishek-kakkar/BeagleLogic/wiki

# beaglelogic is installed on the 4.9 kernel, but not the 4.14, so
# if you are running 4.14, switch to 4.9
sudo /opt/scripts/tools/update_kernel.sh --lts-4_9
sudo reboot

# Now the kernel driver headers
sudo apt install linux-headers-`uname -r`

modinfo beaglelogic
modprobe beaglelogic

# From: https://beaglelogic.readthedocs.io/en/latest/index.html
