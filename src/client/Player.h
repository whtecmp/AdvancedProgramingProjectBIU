/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_PLAYER
#define _H_GURD_PLAYER

#include "Board.h"
#include "Header.h"

static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }
static std::ostream& operator<<(std::ostream& os, Type t) { return os << (t==BLACK?'X':(t==NONE?'N':'O')); }
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

		//Function that plays turns
		virtual Error Act() = 0;

		void UpdateScore();
		
		void Finish() {UpdateScore(); flow->os<<me<<"'s score="<<score<<std::endl;}
	
	};

}


#endif /* _H_GURD_PLAYER */
