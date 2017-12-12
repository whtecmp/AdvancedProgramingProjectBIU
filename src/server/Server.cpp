



#include <iostream>
#include <string>
#include "../../etc/Socket.h"


int main()
{
	
	while (true)
	{
		Socket* player1 = new Socket();
		Socket* player2 = new Socket();
		
		player1->Listen();
		player1->data = "1st";
		player1->Send();
		
		player2->Listen();
		player2->data = "2nd";
		player2->Send();
		
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
	}
}
