#!/bin/bash

IMAGE=image-linux-31452

echo
echo "Make zImage"
echo
make jzt_uhf_defconfig
make zImage -j16
cp arch/arm/boot/zImage ../$IMAGE/zImage-jzt-uhf

echo
echo "Make dtb"
echo
make jzt-uhf-6q.dtb
#make myimx6ek200-6s.dtb

cp arch/arm/boot/dts/jzt-uhf-6q.dtb ../$IMAGE/

echo
echo "Make modules"
echo
make modules -j16
make modules_install INSTALL_MOD_PATH=./modules
cd modules
tar -cjf ../modules.tar.bz2 *
cd ../
cp ./modules.tar.bz2 ../$IMAGE/

echo
echo "Done"
echo
