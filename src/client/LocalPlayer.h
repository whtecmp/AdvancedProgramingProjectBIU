/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_LOCALPLAYER
#define _H_GURD_LOCALPLAYER

#include "Board.h"
#include "Header.h"
#include "Player.h"
#include "../../etc/Socket.h"

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

	/******************************************
	* Class Name: Player
	* Aim: Represent a general player, without knowing
			who'll control him or any thing else about
			him.
	*********************************************/
	class LocalPlayer : public Player
	{
	private:
		
		Socket* info;


	public:

		//Function that plays turns
		virtual Error Act() = 0;

		LocalPlayer(Type t, Board& b, Socket* s);

	};

}


#endif /* _H_GURD_LOCALPLAYER */
