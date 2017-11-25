#Efraim Vagner	207304262

a.out: main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o
	g++ main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o
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
clean:
	rm HumanPlayer.o
	rm Player.o
	rm MainMenue.o
	rm Board.o
	rm main.o
	rm a.out	
