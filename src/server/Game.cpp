#include "Game.h"

Game::~Game(){
  delete(players[1]);
  delete(players[2]);
}

int Game::AddPlayerToGame(Socket* player){
  if (numberPlayersInGame < 2){
    this->players[numberPlayersInGame] = player;
    numberPlayersInGame++;
    return -1; //indicates Error
  }
  else
    return numberPlayersInGame;//1 is the first and 2 is the second
}

bool Game::Contains(Socket* player){
  for(int i=0;i<2;i++)
    if(players[i]==player)
      return true;
  return false;
}

void Game::SendOtherPlayer(Socket* player,std::string toSend){
  if(player == players[0]){
    players[1]->data = toSend;
    players[1]->Send();
  }
  else if(player == players[1]){
    players[0]->data =toSend;
    players[0]->Send();
  }
}

Socket* Game::GetOtherPlayer(Socket* player){
  if(player == players[0]){
    return players[1];
  }
  else if(player == players[1]){
    return players[0];
  }
}
