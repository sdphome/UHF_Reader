upper: upper.o
	${CROSS_COMPILE}gcc upper.o -o upper -lpthread -L ../utils/llrp -lltkc

upper.o: upper.c
	${CROSS_COMPILE}gcc -c upper.c -o upper.o -I ../utils/llrp

clean:
	rm *.o upper
