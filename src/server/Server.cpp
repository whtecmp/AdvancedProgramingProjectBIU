/*
Names: Avi Kadria and Efraim Vagner
*/

#include <iostream>
#include <string>
#include "../../etc/Socket.h"
#include "string.h"
#include <thread>
#include <pthread.h>
#include "Game.h"

#define D true

Game** ListGames = new Game*[100]; //default value, can open more.
int ListGamesSize = 100;//Saves the size of the list of games.
													//(could be reallocated)
int CurrentOpenGames = 0; //counts the number of open games.

/*************************************
function name: OpenGame
input: name of a game.
output: nothing
function operation:check if there exists a game with this name, if there is
	return -1 (error) otherwise create a new game with this name.
**************************************/
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

/*************************************
function name: PrintGames
input: Socket of player
output: nothing
function operation:Send to a player string representing all the games that has
	been created..
**************************************/
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


/*************************************
function name: CloseGame
input: name of game.
output: nothing
function operation:Remove the game from the game list.
**************************************/
void CloseGame(std::string gameName){
	for (int i=0;i<CurrentOpenGames;i++){
		if(gameName==ListGames[i]->GetName()){
			delete(ListGames[i]);
		}
	}
	return;
}

/*************************************
function name: JoinGame
input: pointer to Socket of a player and the bane of the game.
output: nothing
function operation:check if there exists a game with this name and f there is
	more room in it(less than two players in it). if there is room connects the
	player to this game.
**************************************/
void JoinGame(std::string gameName,Socket* player){
	for(int i=0;i<CurrentOpenGames;i++){
		if(gameName==ListGames[i]->GetName()){
			ListGames[i]->AddPlayerToGame(player);
		}
	}
}

/*************************************
function name: Play
input: pointer to Socket of a player and a string of the move it does.
output: nothing
function operation:check on which game the player is in. when it is found send
	the second player the move this player has done.
**************************************/
void Play(std::string move/*<x> <y>*/,Socket* player){
	move[1] = ',';
	for(int i=0;i<CurrentOpenGames;i++){
			if(ListGames[i]->Contains(player)){
				ListGames[i]->SendOtherPlayer(player,move);
			}
	}
}

/*************************************
function name: HandlePlayer
input: pointer to Socket of a player
output: nothing
function operation: runs an inifinite while loop, in it waiting to receive
	input from client, goes according to the input and calls the wanted functions.
**************************************/
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
/*************************************
function name: main
input: nothing
output: nothing
function operation: runs an inifinite while loop, in it waiting to receive
	clients, when clients is received open a new thread which will take care of it.
**************************************/
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
