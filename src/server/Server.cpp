/*
Names: Avi Kadria and Efraim Vagner
*/

#include <iostream>
#include <string>
#include "../../etc/Socket.h"
#include "string.h"
#include <thread>
#include <pthread.h>

#define D true
class Game{
	const std::string gameName;
	int numberPlayersInGame;
	Socket *players[2];
public:
	void JoinGame(Socket* player){}
	Game(std::string name):gameName(name),numberPlayersInGame(0){}
	Game(){}
	~Game(){
		delete(players[1]);
		delete(players[2]);
	}
	std::string GetName(){return gameName;}
	//returns whether it was able to add the player to the game.
	bool AddPlayerToGame(Socket* player){
		if (numberPlayersInGame < 2){
			players[numberPlayersInGame] = player;
			numberPlayersInGame++;
		}
		else
			return false;
	}
	bool Contains(Socket* player){
		for(int i=0;i<2;i++)
			if(players[i]==player)
				return true;
		return false;
	}
	void SendOtherPlayer(Socket* player,std::string toSend){
		if(player == players[0]){
			players[1]->data = toSend;
			players[1]->Send();
		}
		else if(player == players[1]){
			players[0]->data =toSend;
			players[0]->Send();
		}
	}
	int GetNumberPlayersInGame(){return numberPlayersInGame;}
};

Game** ListGames = new Game*[100]; //default value, can open more.
int ListGamesSize = 100;
int CurrentOpenGames = 0; //counts the number of open games.


void OpenGame(std::string gameName,Socket* player){
	if(D){
		std::cout<<gameName<<std::endl;
	}

	for(int i=0;i<CurrentOpenGames;i++){
		if(gameName==ListGames[i]->GetName()){
			player->data = "-1";
			player->Send();
			return;
		}
	}
	if(CurrentOpenGames < ListGamesSize)
	{
		CurrentOpenGames++;
		ListGames[CurrentOpenGames] = new Game(gameName);
	}
	return;
}

void PrintGames(Socket* player){
	std::string output = "";
	for(int i=0;i<CurrentOpenGames;i++){
		if(ListGames[i]->GetNumberPlayersInGame() < 2){
			if(D) std::cout<<"name: " << ListGames[i]->GetName() << std::endl;
			output += ListGames[i]->GetName(); + "\n";
		}
	}
	player->data = output;
	player->Send();
}

void CloseGame(std::string gameName){
	for (int i=0;i<CurrentOpenGames;i++){
		if(gameName==ListGames[i]->GetName()){
			delete(ListGames[i]);
		}
	}
	return;
}

void JoinGame(std::string gameName,Socket* player){
	for(int i=0;i<CurrentOpenGames;i++){
		if(gameName==ListGames[i]->GetName()){
			ListGames[i]->AddPlayerToGame(player);
		}
	}
}

void Play(std::string move/*<x> <y>*/,Socket* player){
	move[1] = ',';
	for(int i=0;i<CurrentOpenGames;i++){
			if(ListGames[i]->Contains(player)){
				ListGames[i]->SendOtherPlayer(player,move);
			}
	}
}

void* HandlePlayer(void* voidpToPlayer){
	Socket * player = (Socket *) voidpToPlayer;
	while(player->data != "End")
	{
		player->Listen();
		player->Recive();

		if(player->data.substr(0,strlen("start ")) == "start "){
			OpenGame(player->data.substr(strlen("start ")),player);
		}
		else if(player->data == "list_games"){
			PrintGames(player);
		}
		else if(player->data.substr(0,strlen("start ")) == "join "){
			JoinGame(player->data.substr(strlen("join ")),player);
		}
		else if(player->data.substr(0,strlen("play ")) == "play ")
		{
			//input format: play <x> <y>
			Play(player->data.substr(strlen("play ")),player);
		}
		else if(player->data.substr(0,strlen("close ")) == "close ")
		{
			CloseGame(player->data.substr(strlen("close ")));
		}
	}
	delete(player);
}

int main(){
	pthread_t threads[100];
  int index=0;
	while(true){
			Socket* newPlayer = new Socket();
			newPlayer->Listen();
			pthread_create(&threads[index], NULL, HandlePlayer,(void *)newPlayer);
			//listThreads[index] = new std::thread(HandlePlayer,newPlayer);
			index++;
	}
	//Efi's stuff.
	while (true){
		Socket* player1 = new Socket();
		Socket* player2 = new Socket();

		player1->Listen();
		player1->data = "1st";
		player1->Send();

		player2->Listen();
		player2->data = "2nd";
		player2->Send();

		//??
		player1->Send();
		player2->Send();


		while (player1->data != "End")
		{
			player1->Recive();
			player2->data = player1->data;
			player2->Send();

			player2->Recive();
			player1->data = player2->data;
			player1->Send();

		}
		delete(player1);
		delete(player2);
	}
}
