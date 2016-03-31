#!/bin/bash

PLATFORM=$1

IMAGE=image-linux-31452

mkdir -p ../$IMAGE

if [ "$PLATFORM" = "s" ]; then
	make jzt-uhf-6s_defconfig
elif [ "$PLATFORM" = "q" ]; then
	make jzt-uhf-6q_defconfig
fi


echo
echo "begin complie"
echo
make -j16

echo
echo "Copy uboot image to image folder"
echo

if [ "$PLATFORM" = "s" ]; then
	cp u-boot.imx ../$IMAGE/uboot-jzt-uhf-6s.imx
elif [ "$PLATFORM" = "q" ]; then
	cp u-boot.imx ../$IMAGE/uboot-jzt-uhf-6q.imx
fi
