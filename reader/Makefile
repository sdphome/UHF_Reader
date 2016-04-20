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

CC				= ${CROSS_COMPILE}gcc
CFLAGS			= -Wall
MKDIR			= mkdir
RM				= rm
OUT				= out
EXE				= uhf
OBJS			= objs

SM2_INCLU		= utils/sm2
LTK_INCLU		= utils/llrp
SQL_INCLU		= utils/sqlite3
UHF_HDRS		= include

UHF_OBJS = \
	$(OBJS)/uhf.o	\
	$(OBJS)/sql.o	\
	$(OBJS)/file.o	\
	$(OBJS)/upper.o	\
	$(OBJS)/radio.o	\
	$(OBJS)/security.o

all: $(OUT) $(EXE)

$(OUT):
	$(MKDIR) -p $(OBJS)

$(EXE): $(UHF_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L $(LTK_INCLU) -L $(SM2_INCLU) -lpthread -lsm2 -lltkc -lsqlite3 -ldl

$(OBJS)/uhf.o: uhf.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS) -I $(LTK_INCLU)

$(OBJS)/upper.o: upper.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(LTK_INCLU) -I $(UHF_HDRS)

$(OBJS)/radio.o: radio.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS)

$(OBJS)/security.o: security.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(SM2_INCLU) -I $(UHF_HDRS)

$(OBJS)/file.o: file.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS)

$(OBJS)/sql.o: sql.c
	$(CC) -c $(CFLAGS) $^ -o $@ -I $(UHF_HDRS) -I $(SQL_INCLU)

clean:
	find -name '*.o' -exec rm -rf {} \;
	$(RM) $(EXE) -rf
	$(RM) $(OBJS) -rf

.PHONY: clean
