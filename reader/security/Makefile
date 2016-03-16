security: security.o
	${CROSS_COMPILE}g++ security.o -o security -lpthread -L ../utils -lsm2

security.o: security.c security.h
	${CROSS_COMPILE}g++ -c security.c -o security.o

clean:
	rm *.o security
