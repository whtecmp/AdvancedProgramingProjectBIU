/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_REMOTEPLAYER
#define _H_GURD_REMOTEPLAYER

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
	class RemotePlayer : public Player
	{
	private:

		Socket* info;

	public:

		/************************************************************************
		*function name: UpdateScore
		*input : NONE
		*output :NONE
		*operation : asks for the game move and send it to the server
		**************************************************************************/
		virtual Error Act();

		/************************************************************************
		*function name:constructor
		*input : the type, board refrence and a socket.
		*output : Remote player
		*operation :Set the values according to input
		**************************************************************************/
		RemotePlayer(Type t, Board& b, Socket* s);

	};

}


#endif /* _H_GURD_REMOTEPLAYER */
