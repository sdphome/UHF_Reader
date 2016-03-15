security: security.o
	${CROSS_COMPILE}gcc security.o -o security -lpthread

security.o: security.c security.h
	${CROSS_COMPILE}gcc -c security.c -o security.o

clean:
	rm *.o security
