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
