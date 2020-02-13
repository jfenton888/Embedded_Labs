CLFAGS = -O
CC = g++

WiimoteAccel: main.o WiimoteAccel.o
	$(CC) $(CFLAGS) -o WiimoteAccel main.o WiimoteAccel.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


WiimoteAccel.o: WiimoteAccel.cpp
	$(CC) $(CFLAGS) -c WiimoteAccel.cpp

clean:
	rm -f core *.o WiimoteAccel
