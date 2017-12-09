/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "MainMenue.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
using namespace std;
//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }
static std::ostream& operator<<(std::ostream& os, Type t) { return os << (t==BLACK?'X':(t==NONE?'N':'O')); }

	//A public pointer to the mainmenue class single instance
	MainMenue const * flow = NULL;

	/******************************************
	* C'tor
	* Aim: Initialise tokens, and start the program
	* Input: -
	* Output: -
	* How it works? Initialises streaming and input 
					methods. Then checks if an error 
					was encountered, because of the singletone.
	*********************************************/
	MainMenue::MainMenue(bool start) : os(std::cout), is(std::cin)
	{
		if (flow != NULL)
		{
			throw MORE_THEN_ONE_SINGLETONE;
		}
		flow = this;
		
		if (start)
			Start();
	}


	Error MainMenue::Start()
	{
		os << "Welcome to Reversi!\n\n Choose an opponent:\n1. a human local player\n2. an AI player\n3. a remote player\n";
		int i;
		is >> i;
		return Play(i);
	}

	/******************************************
	* Function: Start
	* Aim: Replace the main function
	* Input: -
	* Output: If there was an error or not
	* How it works? Initialises players, then enters
					an infinet loop and starts the game.
	*********************************************/
	Error MainMenue::Play(int typeOfGame)
	{
		Socket* remotePlay = NULL;
		
		Board b;
		Player* p[2];
		switch (typeOfGame)
		{
		case 1:
			p[0] = new HumanPlayer(BLACK, b);
			p[1] = new HumanPlayer(WHITE, b);
			break;
		case 2:
			p[0] = new HumanPlayer(BLACK, b);
			p[1] = new ComputerPlayer(WHITE, b);
			break;
		case 3:
			remotePlay = new Socket(CLIENT);
			remotePlay->data = "active";
			remotePlay->Send();
			remotePlay->Recive();
			
			os << "connected to server" << std::endl;
			os << "waiting for other player to join..." << std::endl;
			
			remotePlay->Wait();
			
			if (remotePlay->data == "1st")
			{
				p[0] = new LocalPlayer(BLACK, b, remotePlay);
				p[1] = new RemotePlayer(WHITE, b, remotePlay);
			}
			else
			{
				p[0] = new RemotePlayer(BLACK, b, remotePlay);
				p[1] = new LocalPlayer(WHITE, b, remotePlay);
			}
			
			break;
		default:
			return NO_SUCH_GAME;
			break;
		}
		
		Type playerToPlayIs = BLACK;
		
		bool quit = false;
		while (!quit)
		{
			os << b;
			os << playerToPlayIs << ':' << "It's your move." << std::endl;
			bool** mat;
			mat = new bool*[b.GetSize()];
			for (int i = 0; i <  b.GetSize(); i++)
				mat[i] = new bool[b.GetSize()];
			for (int i = 0; i <  b.GetSize(); i++)
			{
				for (int j = 0; j <  b.GetSize(); j++)
					mat[i][j] = false;
			}
			
			bool posMoves = false;
			for (int i = 0; i < b.GetSize(); i++)
			{
				for (int j = 0; j < b.GetSize(); j++)
				{
					if (b.CanPlaceHere(i+1, j+1, playerToPlayIs))
						{mat[i][j] = true; posMoves = true;}
				}
			}
			
			
			if (posMoves)
			{
				bool isFirst = true;
				os << "Your possible moves: ";
				for (int i = 0; i < b.GetSize(); i++)
				{
					for (int j = 0; j < b.GetSize(); j++)
					{
						if (mat[i][j])
						{
							if (isFirst)
								isFirst = false;
							else
								os << ',';
							os << '(' << i+1 << ',' << j+1 << ')';
						}
								
					}
				}
				
				os << std::endl << std::endl;

				Error e = p[playerToPlayIs]->Act();

				if (e != NO_ERROR)
				{
					os << "Invalid move! Please try again." << std::endl;
					playerToPlayIs = !playerToPlayIs;
				}
			}
			else
			{
				os << "No possible moves. Play passes to the other player. Press any key to continue.";
				
				char temp;
				is >> temp;
				if (remotePlay != NULL)
				{
					remotePlay->data = "NoMove";
					remotePlay->Send();
				}
			}
			playerToPlayIs = !playerToPlayIs;
		}
	}
}
