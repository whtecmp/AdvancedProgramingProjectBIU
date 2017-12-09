/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/

#include "HumanPlayer.h"

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{
static std::ostream& operator<<(std::ostream& os, Type t) { return os << (t==BLACK?'X':(t==NONE?'N':'O')); }

	/**********************************
	* Function: Act
	* Aim: To let a Human player pick his moves
	* Input: -
	* Output: Error, if any
	* How it works?: Takes users input, and
						calls PlaceUnit
	***********************************/
	Error HumanPlayer::Act()
	{
		int x, y;
		flow->os << "Please enter your move row,col: ";
		flow->is >> x;
		flow->is >> y;
		return board.PlaceUnit(x, y, me);
	}
	
	/**********************************
	* C'tor
	* Aim: A normal ctor
	* Input: The way to stream, what to stream
	* Output: A new HumanPlayer
	* How it works?: initializing with Player's
						normal c'tor
	***********************************/
	HumanPlayer::HumanPlayer(Type t, Board& b) : Player(t, b) {}

}
