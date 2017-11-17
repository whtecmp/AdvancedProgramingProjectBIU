#Efraim Vagner	207304262

a.out: main.o Board.o MainMenue.o Player.o HumanPlayer.o
	g++ main.o Board.o MainMenue.o Player.o HumanPlayer.o
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
