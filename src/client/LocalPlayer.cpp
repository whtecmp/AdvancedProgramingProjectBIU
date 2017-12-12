/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "LocalPlayer.h"
#include <string>
namespace AdvancedProgramingProjectBIU 
{
    static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }


	Error LocalPlayer::Act()
	{
		int x, y;
		flow->os << "Please enter your move row,col: ";
		flow->is >> x;
		flow->is >> y;
		Error e = board.PlaceUnit(x, y, me);
		if (e != SUCCESS)
			return e;
		info->data = std::to_string(x) + "," + std::to_string(y);
		info->Send();
		flow->os << "Waiting for othe player's move...";
		info->Send();
		return e;
		
	}
    
	LocalPlayer::LocalPlayer(Type t, Board& b, Socket* s) : Player(t, b) 
	{
		info = s;
	}
}
