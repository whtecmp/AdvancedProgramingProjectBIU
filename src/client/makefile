#Efraim Vagner	207304262 Avi Kadria 211991401

client.out: main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o Socket.o LocalPlayer.o RemotePlayer.o
	g++ main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o Socket.o LocalPlayer.o RemotePlayer.o -o client.out
main.o: main.cpp Header.h
	g++ -c main.cpp Header.h
Board.o: Board.cpp Board.h
	g++ -c Board.cpp
MainMenue.o: MainMenue.cpp MainMenue.h
	g++ -c MainMenue.cpp
Player.o: Player.cpp Player.h
	g++ -c Player.cpp
HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h
	g++ -c HumanPlayer.cpp
ComputerPlayer.o: ComputerPlayer.cpp ComputerPlayer.h
	g++ -c ComputerPlayer.cpp
RemotePlayer.o: RemotePlayer.cpp RemotePlayer.h
	g++ -c RemotePlayer.cpp
LocalPlayer.o: LocalPlayer.cpp LocalPlayer.h
	g++ -c LocalPlayer.cpp
Socket.o: ../../etc/Socket.cpp ../../etc/Socket.h
	g++ -c ../../etc/Socket.cpp
	
clean:
	rm *.o
	rm client.out	

