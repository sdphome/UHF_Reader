############################################################################
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

CC				= ${CROSS_COMPILE}gcc
CFLAGS			= -Wall

EXE				= uhf

SM2_INCLU		= utils/sm2
LTK_INCLU		= utils/llrp
UHF_HDRS		= include

UHF_OBJS = \
	uhf.o	\
	upper.o	\
	radio.o	\
	security.o

$(EXE): $(UHF_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L $(LTK_INCLU) -L $(SM2_INCLU) -lpthread -lsm2 -lltkc

uhf.o: uhf.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS) -I $(LTK_INCLU)

upper.o: upper.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(LTK_INCLU) -I $(UHF_HDRS)

radio.o: radio.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS)

security.o: security.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(SM2_INCLU) -I $(UHF_HDRS)


clean:
	find -name '*.o' -exec rm -rf {} \;
	rm $(EXE) -rf
