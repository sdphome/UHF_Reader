radio: radio.o
	${CROSS_COMPILE}gcc radio.o -o radio -lpthread

radio.o: radio.c radio.h
	${CROSS_COMPILE}gcc -c radio.c -o radio.o

clean:
	rm *.o radio
