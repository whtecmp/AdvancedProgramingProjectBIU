server.out: Socket.o
	g++ server.cpp -o server.out
Socket.o: ../../etc/Socket.cpp ../../etc/Socket.h
	g++ -c ../../etc/Socket.cpp
clean:
	rm *.o
	rm server.out
