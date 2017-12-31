/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_PLAYER
#define _H_GURD_PLAYER

#include "Board.h"
#include "MainMenue.h"
#include "Header.h"


//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{


	/******************************************
	* Class Name: Player
	* Aim: Represent a general player, without knowing
			who'll control him or any thing else about
			him.
	*********************************************/
	class Player
	{

	protected:

		//The board he'll play on
		Board& board;

		//current score
		unsigned int score;

		//color
		Type me;

		//C'tor
		Player(Type t, Board& b) : me(t), board(b), score(0) {}



	public:

		/************************************************************************
		*function name: Act
		*input : NONE
		*output : Error if happend
		*operation : virtual function.
		**************************************************************************/
		virtual Error Act() = 0;


		/************************************************************************
		*function name: UpdateScore
		*input : NONE
		*output :NONE
		*operation : Update the score of the board.
		**************************************************************************/
		void UpdateScore();

		/************************************************************************
		*function name: Finish
		*input : NONE
		*output :NONE
		*operation : finish the game and prints the score.
		**************************************************************************/

		void Finish() {UpdateScore(); flow->os<<(me=='X'?'X':'O')<<"'s score="<<score<<std::endl;}

	};

}


#endif /* _H_GURD_PLAYER */
