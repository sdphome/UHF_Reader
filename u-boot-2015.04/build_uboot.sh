#!/bin/bash

mkdir -p ../image-linux-31452

make myimx6ek200-6q_defconfig

# For signal core
#make myimx6ek200-6s_defconfig

echo
echo "begin complie"
echo
make -j16

echo
echo "Copy uboot image to image folder"
echo
cp u-boot.imx ../$IMAGE/uboot-myimx6ek200-6q.imx

# For signal core
#cp u-boot.imx ../image-linux-31452/uboot-myimx6ek200-6s.imx
