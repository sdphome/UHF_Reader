############################################################################
#
#   Author: Shao Depeng <dp.shao@gmail.com>
#   Copyright 2016 Golden Sky Technology CO.,LTD
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
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
cp uhf $ROOT_DIR/rfs/$ROOTFS/home/root/

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
