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

usage()
{
	echo "usage:"
	echo "$0" " q  Or"
	echo "$0" " s"
}

if [ "$1" = "q" ]; then
	echo "q"
elif [ "$1" = "s" ]; then
	echo "s"
else
	usage
	exit 1
fi

source arm-linux-gnueabihf-492-env
export IMAGE=image-linux-31452
UBOOT=u-boot-2015.04
KERNEL=linux-3.14.52
ROOTFS=rootfs
ROOTFS_2=rtfs_file
ROOT_DIR=$PWD
READER=reader

PLATFORM=$1

mkdir -p $IMAGE

cd $ROOT_DIR/$READER
make

cp uhf $ROOT_DIR/rfs/$ROOTFS/uhf/

cd $ROOT_DIR/$UBOOT
. build_uboot.sh $PLATFORM

cd $ROOT_DIR/$KERNEL
. build_kernel.sh $PLATFORM

echo
echo "====== Creating i.MX6 fs ======"
cd $ROOT_DIR/rfs/$ROOTFS
if [ $? -ne 0 ]
then
    echo "no rootfs found! exit"
    exit 1
else
    echo "tar rootfs.tar.bz2..."
    tar -jcf $ROOT_DIR/$IMAGE/rootfs.tar.bz2 *
    if [ $? -ne 0 ]
    then
        echo "====== tar rootfs.tar.bz2 err[$?] ======"
        exit 1
    else
        echo "OK"
    fi
fi

cd $ROOT_DIR/rfs/$ROOTFS_2
if [ $? -ne 0 ]
then
    echo "no rtfs_file found! exit"
    exit 1
else
    echo "tar rtfs_file.tar.bz2..."
    tar -jcf $ROOT_DIR/$IMAGE/rtfs_file.tar.bz2 *
    if [ $? -ne 0 ]
    then
        echo "====== tar rtfs_file.tar.bz2 err[$?] ======"
        exit 1
    else
        echo "OK"
    fi
fi

cd $ROOT_DIR

echo
echo "Complete"
echo
