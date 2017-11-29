#Efraim Vagner	207304262 Avi Kadria 211991401

a.out: main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o
	g++ main.o Board.o MainMenue.o Player.o HumanPlayer.o ComputerPlayer.o
main.o: Reversi_Project/main.cpp Reversi_Project/Header.h
	g++ -c Reversi_Project/main.cpp Reversi_Project/Header.h
Board.o: Reversi_Project/Board.cpp Reversi_Project/Board.h
	g++ -c Reversi_Project/Board.cpp
MainMenue.o: Reversi_Project/MainMenue.cpp Reversi_Project/MainMenue.h
	g++ -c Reversi_Project/MainMenue.cpp
Player.o: Reversi_Project/Player.cpp Reversi_Project/Player.h
	g++ -c Reversi_Project/Player.cpp
HumanPlayer.o: Reversi_Project/HumanPlayer.cpp Reversi_Project/HumanPlayer.h
	g++ -c Reversi_Project/HumanPlayer.cpp
ComputerPlayer.o: Reversi_Project/ComputerPlayer.cpp Reversi_Project/ComputerPlayer.h
	g++ -c Reversi_Project/ComputerPlayer.cpp
clean:
	rm HumanPlayer.o
	rm ComputerPlayer.o
	rm Player.o
	rm MainMenue.o
	rm Board.o
	rm main.o
	rm a.out	

