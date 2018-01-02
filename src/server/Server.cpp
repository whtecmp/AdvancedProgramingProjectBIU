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

#define D false

Game** ListGames = new Game*[100]; //default value, can open more.
int ListGamesSize = 100;//Saves the size of the list of games.
													//(could be reallocated)
int CurrentOpenGames = 0; //counts the number of open games.

/*************************************
ListGames[i]->SendOtherPlayer(player,move);
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
	//sends the player that the operation succeeded
	player->data = "1";
	player->Send();
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
			if(D) std::cout << "name: " << ListGames[i]->GetName() << std::endl;
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
void CloseGame(std::string gameName, Socket* player){
	bool isDeleted = false;
	for (int i=0;i<CurrentOpenGames;i++){
		if(gameName == ListGames[i]->GetName()){
			delete(ListGames[i]);
			isDeleted = true;
		}
	}

	if(isDeleted){
		//sends the player that the operation succeeded
		player->data = "1";
	}
	else{
		player->data = "-1";
	}
	player->Send();
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
	bool isJoined;
	int numPlayer = -1;
	for(int i=0;i<CurrentOpenGames;i++){
		if(gameName == ListGames[i]->GetName()){
			numPlayer = ListGames[i]->AddPlayerToGame(player);
			isJoined = true;
		}
	}
	player->data = std::to_string(numPlayer);//-1 is error,1 or 2 is num player.
	player->Send();
}

/*************************************
function name: Play
input: pointer to Socket of a player and a string of the move it does.
output: nothing
function operation:check on which game the player is in. when it is found send
	the second player the move this player has done.
**************************************/
void Play(std::string move/*<x> <y>*/,Socket* player){
	bool isInGame = false;
	std::string otherplayerMove;
	Socket* otherPlayer = NULL;
	//to agree with last exercise format:
	move[1] = ',';
	for(int i=0;i<CurrentOpenGames;i++){
			if(ListGames[i]->Contains(player)){
				isInGame = true;
				otherPlayer = ListGames[i]->GetOtherPlayer(player);
				otherPlayer->Recive();//the other player makes his move according
				 												//to format
				otherplayerMove = otherPlayer->data.substr(strlen("play "));
				otherplayerMove[1] = ',';
				player->data = otherplayerMove;
				player->Send();
				return;

				// player1->Recive();
				// player2->data = player1->data;
				// player2->Send();
        //
				// player2->Recive();
				// player1->data = player2->data;
				// player1->Send();
			}
	}
	if(!isInGame){
		player->data = "-1";
		player->Send();
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
	bool toContinue = true;
	Socket * player = (Socket *) voidpToPlayer;
	player->Listen();
	while(toContinue)
	{
		player->Recive();

		if(player->data.substr(0,strlen("start ")) == "start "){
			OpenGame(player->data.substr(strlen("start ")),player);
		}
		else if(player->data == "list_games"){
			PrintGames(player);
		}
		else if(player->data.substr(0,strlen("join ")) == "join "){
			JoinGame(player->data.substr(strlen("join ")),player);
		}
		else if(player->data.substr(0,strlen("play ")) == "play ")
		{
			//input format: play <x> <y>
			Play(player->data.substr(strlen("play ")),player);
		}
		else if(player->data.substr(0,strlen("close ")) == "close ")
		{
			CloseGame(player->data.substr(strlen("close ")),player);
		}
		else if(player->data == "End"){
			toContinue = false;
			player->Send(); //just to make the client exit aswell (to let him know I
												//saw he disconnected).
		}
		else{
			//non-valid operator:
			player->data = "-1";
			player->Send();
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
	//Ex4:
	// while (true){
	// 	Socket* player1 = new Socket();
	// 	Socket* player2 = new Socket();
  //
	// 	player1->Listen();
	// 	player1->data = "1st";
	// 	player1->Send();
  //
	// 	player2->Listen();
	// 	player2->data = "2nd";
	// 	player2->Send();
  //
	// 	//??
	// 	player1->Send();
	// 	player2->Send();
  //
  //
	// 	while (player1->data != "End")
	// 	{
	// 		player1->Recive();
	// 		player2->data = player1->data;
	// 		player2->Send();
  //
	// 		player2->Recive();
	// 		player1->data = player2->data;
	// 		player1->Send();
  //
	// 	}
	// 	delete(player1);
	// 	delete(player2);
	// }
}
