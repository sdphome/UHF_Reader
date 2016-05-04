############################################################################
#
#   Author: Shao Depeng <dp.shao@gmail.com>
#   Copyright 2016 Golden Sky Technology CO.,LTD
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
############################################################################

#!/bin/bash

IMAGE=image-linux-31452
PLATFORM=$1

echo
echo "Make zImage"
echo
make jzt_uhf_defconfig
make zImage -j16
cp arch/arm/boot/zImage ../$IMAGE/zImage-jzt-uhf

echo
echo "Make dtb"
echo
if [ "$PLATFORM" = "s" ]; then
	make jzt-uhf-6s.dtb
	cp arch/arm/boot/dts/jzt-uhf-6s.dtb ../$IMAGE/
elif [ "$PLATFORM" = "q" ]; then
	make jzt-uhf-6q.dtb
	cp arch/arm/boot/dts/jzt-uhf-6q.dtb ../$IMAGE/
fi

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
