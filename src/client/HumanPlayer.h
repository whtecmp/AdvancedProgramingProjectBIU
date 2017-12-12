/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_HUMANPLAYER
#define _H_GURD_HUMANPLAYER

#include "Player.h"
#include "MainMenue.h"

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

	/************************************************
	* Class Name: HumanPlayer
	* Inherits: Player
	* Class Aim: Represent a human player
	************************************************/
	class HumanPlayer : public Player
	{

	private:

	public:
	
	
	
		/**********************************
		* C'tor
		* Aim: A normal ctor
		* Input: The way to stream, what to stream
		* Output: A new HumanPlayer
		* How it works?: initializing with Player's
							normal c'tor
		***********************************/
		HumanPlayer(Type t, Board& b);

		/**********************************
		* Function: Act
		* Aim: To let a Human player pick his moves
		* Input: -
		* Output: Error, if any
		* How it works?: Takes users input, and
							calls PlaceUnit
		***********************************/
		virtual Error Act();

	};

}


#endif /* _H_GURD_HUMANPLAYER */
