



#include <iostream>
#include <string>


int main()
{
	Socket* player1 = new Socket(SERVER);
	Socket* player2 = new Socket(SERVER);
	
	player1->Connect();
	player1->data = "1st";
	player1->Send();
	
	player2->connect();
	player2->data = "2nd";
	player2->Send();
	
	player1->Send();
	player2->Send();


	while (move != "End")
	{
		player1->Recive();
		player2->data = player1->data;
		player2->Send();
	
		player2->Recive();
		player1->data = player2->data;
		player1->Send();
	
	}
}
