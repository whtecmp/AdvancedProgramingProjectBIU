server.out: Socket.o Server.o
	g++ Server.o Socket.o -o server.out
Server.o: Server.cpp
	g++ -c Server.cpp
Socket.o: ../../etc/Socket.cpp ../../etc/Socket.h
	g++ -c ../../etc/Socket.cpp
clean:
	rm *.o
	rm server.out
