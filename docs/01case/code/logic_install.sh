# Instructions for installing BeagleLogic
# https://beaglelogic.readthedocs.io/en/latest/index.html
# From: https://github.com/abhishek-kakkar/BeagleLogic/wiki

# beaglelogic is installed on the 4.9 kernel, but not the 4.14, so
# if you are running 4.14, switch to 4.9
sudo /opt/scripts/tools/update_kernel.sh --lts-4_9
sudo reboot

git clone https://github.com/abhishek-kakkar/BeagleLogic
cd BeagleLogic
sudo ./install.sh
sudo reboot

# Now the kernel driver headers
sudo apt install linux-headers-`uname -r`

modinfo beaglelogic
modprobe beaglelogic

# From: https://beaglelogic.readthedocs.io/en/latest

# Here's what works from abhishek
git clone https://github.com/abhishek-kakkar/BeagleLogic
cd BeagleLogic
# 1. Get the dts file from this gist (https://gist.github.com/abhishek-kakkar/0761ef7b10822cff4b3efd194837f49c)

# 2. cd to 'BeagleLogic/kernel' directory. Put the dts file there. (edited)
# 3. Run 'make overlay'
# 4. Run 'sudo cp -v beaglelogic-00A0.dtbo /lib/firmware/' (edited)
# 5. Run 'sudo update-initramfs -u -k ``uname -r``' (edited)
# (single backticks only, apparently Slack treats single backtick as code) (edited)
# 6. Reboot
# 7. Browse to bone:4000
