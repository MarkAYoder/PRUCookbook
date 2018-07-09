# This is a example of ARM to PRU communication from Lab 5 of
# http://processors.wiki.ti.com/index.php/PRU_Training:_Hands-on_Labs#LAB_5:_RPMsg_Communication_between_ARM_and_PRU

sudo apt install linux-headers-`uname -r`

wget https://github.com/beagleboard/linux/raw/4.9/drivers/rpmsg/rpmsg_pru.c
