#include <iostream>
#include <string>
#include "../../etc/Socket.h"

class Game{
	const std::string gameName;
	int numberPlayersInGame;
	Socket *players[2];
public:
	void JoinGame(Socket* player){}
	Game(std::string name):gameName(name),numberPlayersInGame(0){}
	Game(){}
	~Game();
	std::string GetName(){return gameName;}
	//returns whether it was able to add the player to the game.
	int AddPlayerToGame(Socket* player);
	bool Contains(Socket* player);
	Socket* GetOtherPlayer(Socket* player);
	void SendOtherPlayer(Socket* player,std::string toSend);
	int GetNumberPlayersInGame(){return numberPlayersInGame;}
};
