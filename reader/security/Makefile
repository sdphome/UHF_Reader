security: security.o
	${CROSS_COMPILE}gcc security.o -o security -lpthread -L ../utils/sm2 -lsm2

security.o: security.c
	${CROSS_COMPILE}gcc -c security.c -o security.o -I ../utils/sm2

clean:
	rm *.o security
