#!/bin/bash

echo
echo "Make zImage"
echo
make myimx6_defconfig
make zImage -j16
cp arch/arm/boot/zImage ../image-linux-31452/zImagemyimx6

echo
echo "Make dtb"
echo
make myimx6ek200-6q.dtb
#make myimx6ek200-6s.dtb

cp arch/arm/boot/dts/myimx6ek*.dtb ../image-linux-31452/

echo
echo "Make modules"
echo
make modules -j16
make modules_install INSTALL_MOD_PATH=./modules
cd modules
tar -cjf ../modules.tar.bz2 *
cd ../
cp ./modules.tar.bz2 ../image-linux-31452/

echo
echo "Done"
echo
