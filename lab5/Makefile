CLFAGS = -O
CC = g++

ServoPosition: ServoPosition.o GPIO.o
	$(CC) $(CFLAGS) -o ServoPosition ServoPosition.o GPIO.o

ServoPosition.o: ServoPosition.cpp
	$(CC) $(CFLAGS) -c ServoPosition.cpp


GPIO.o: GPIO.cpp
	$(CC) $(CFLAGS) -c GPIO.cpp

clean:
	rm -f core *.o ServoPosition
