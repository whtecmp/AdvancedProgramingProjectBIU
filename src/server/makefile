server.out: Socket.o Server.o Game.o
	g++ -std=c++11 -pthread Server.o Socket.o Game.o -o server.out
Server.o: Server.cpp
	g++ -c -std=c++11 -pthread Server.cpp
Socket.o: ../../etc/Socket.cpp ../../etc/Socket.h
	g++ -c ../../etc/Socket.cpp
Game.o:	Game.h Game.cpp
	g++ -c Game.cpp
clean:
	rm *.o
	rm server.out
