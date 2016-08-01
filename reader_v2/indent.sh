#!/bin/sh
#    Author: Shao Depeng (sdphome@live.cn)
#    Date:   Sun Apr 10 17:26:44 CST 2016
#    Version:  1.0.0
# Description:  This shell script used to format all the source code in current folder
#               and convert source code file format from windows to linux

find -iname \*.c -exec dos2unix {} \;
find -iname \*.h -exec dos2unix {} \;
find -iname "makefile" -exec dos2unix {} \;
find -iname "Makefile" -exec dos2unix {} \;


INDET_FORMAT="-npro -kr -i4 -ts4 -cli2 -ss -bbb -bap -sob -l100 -ncs"

find -iname \*.c -exec indent $INDET_FORMAT {} \;
find -iname \*.h -exec indent $INDET_FORMAT {} \;
find -iname \*.h~ | xargs rm -rf {} \;
find -iname \*.c~ | xargs rm -rf {} \;
