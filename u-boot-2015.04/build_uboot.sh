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
