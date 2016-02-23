#!/bin/bash

source arm-linux-gnueabihf-492-env
export IMAGE=image-linux-31452
UBOOT=u-boot-2015.04
KERNEL=linux-3.14.52
ROOTFS=rootfs
ROOT_DIR=$PWD

mkdir -p $IMAGE

cd $ROOT_DIR/$UBOOT
. build_uboot.sh

cd $ROOT_DIR/$KERNEL
. build_kernel.sh

echo
echo "====== Creating i.MX6 fs ======"
cd $ROOT_DIR/$ROOTFS
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

cd $ROOT_DIR

echo
echo "Complete"
echo
