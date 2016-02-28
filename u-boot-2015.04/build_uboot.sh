#!/bin/bash

IMAGE=image-linux-31452

mkdir -p ../$IMAGE

make myimx6ek200-6q_defconfig

# For signal core
#make myimx6ek200-6s_defconfig

echo
echo "begin complie"
echo
make -j4

echo
echo "Copy uboot image to image folder"
echo
cp u-boot.imx ../$IMAGE/uboot-myimx6ek200-6q.imx

# For signal core
#cp u-boot.imx ../image-linux-31452/uboot-myimx6ek200-6s.imx
