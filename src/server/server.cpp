



#include <iostream>
#include <string>


int main()
{
	Socket* player1 = Wait();
	SendConfirmation(player1);
	
	Socket* player2 = Wait();
	SendConfirmation(player2);


	while (move != 'End')
	{
		std::string move1 = ReciveMove(player1);
		SendMove(player2, move1);
	
		std::string move2 = ReciveMove(player2);
		SendMove(player1, move2);
	
	}
}
