/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_MAINMENUE
#define _H_GURD_MAINMENUE

#include "Header.h"

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

	/************************************************
	* Class Name: MainMenue
	* Class Aim: Handle the general flow of the game.
	************************************************/
	class MainMenue
	{
	private:


		/******************************************
		* Function: Start
		* Aim: Replace the main function
		* Input: -
		* Output: If there was an error or not
		* How it works? Initialises players, then enters
						an infinet loop and starts the game.
		*********************************************/
		Error Start();

	public:
	
		//stream method
		std::ostream& os;

		//input method
		std::istream& is;


		/******************************************
		* C'tor
		* Aim: Initialise tokens, and start the program
		* Input: to_start ?
		* Output: -
		* How it works? Initialises streaming and input 
						methods. Then checks if an error 
						was encountered, because of the singletone.
		*********************************************/
		MainMenue(bool start = true);

	};

	//A public pointer to the mainmenue class single instance
	extern MainMenue const* flow;

}

#endif /* _H_GURD_MAINMENUE */
