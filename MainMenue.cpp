/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "MainMenue.h"
#include "Board.h"
#include "HumanPlayer.h"


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
	MainMenue::MainMenue() : os(std::cout), is(std::cin)
	{
		if (flow != NULL)
		{
			throw MORE_THEN_ONE_SINGLETONE;
		}
		flow = this;
		
		Start();
	}


	/******************************************
	* Function: Start
	* Aim: Replace the main function
	* Input: -
	* Output: If there was an error or not
	* How it works? Initialises players, then enters
					an infinet loop and starts the game.
	*********************************************/
	Error MainMenue::Start()
	{
		Board b;
		Player* p[2];
		p[0] = new HumanPlayer(BLACK, b);
		p[1] = new HumanPlayer(WHITE, b);
		
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
			}
			playerToPlayIs = !playerToPlayIs;
		}
	}
}
