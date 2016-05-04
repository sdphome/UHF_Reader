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

PLATFORM=$1

IMAGE=image-linux-31452

mkdir -p ../$IMAGE

if [ "$PLATFORM" = "s" ]; then
	make jzt-uhf-6s_defconfig
elif [ "$PLATFORM" = "q" ]; then
	make jzt-uhf-6q_defconfig
fi


echo
echo "begin complie uboot"
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
