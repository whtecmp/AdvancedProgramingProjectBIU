/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "RemotePlayer.h"
#include <string>
namespace AdvancedProgramingProjectBIU 
{
    static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }

	Error RemotePlayer::Act()
	{
		info->Recive();
		std::string move = info->data;
		if (move != "End" && move != "NoMove")
		{
		
			std::string xstr;
			std::string ystr;
			
			int i;
			for (i = 0; move[i] != ','; i++)
			{
				xstr[i] = move[i];
			}
			xstr[i] = '\0';
			i++;
			int j;
			for (j = 0; move[i+j] != '\0';j++)
			{
				ystr[j] = move[i+j];
			}
			ystr[j] = '\0';
			
			int x = std::stoi(xstr);
			int y = std::stoi(ystr);
			
			Error e = board.PlaceUnit(x, y, me);
			flow->os << me << "played:" << '(' << x << ',' << y << ')' << std::endl;
			
			return e;
		
		}
		else
		{
			return SUCCESS;
		}
	}


	RemotePlayer::RemotePlayer(Type t, Board& b, Socket* s) : Player(t, b) 
	{
		info = s;
	}
}
