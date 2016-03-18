security: security.o
	${CROSS_COMPILE}g++ security.o -o security -lpthread -L ../utils/sm2 -lsm2

security.o: security.c security.h
	${CROSS_COMPILE}g++ -c security.c -o security.o -I ../utils/sm2

clean:
	rm *.o security
