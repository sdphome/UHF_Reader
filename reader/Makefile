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

CC				= ${CROSS_COMPILE}gcc
CFLAGS			= -Wall -g
#-rdynamic -funwind-tables
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
	$(CC) $(CFLAGS) $^ -o $@ -L $(LTK_INCLU) -L $(SM2_INCLU) -lpthread -lsm2 -lltkc -lsqlite3 -ldl -lxml2

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
