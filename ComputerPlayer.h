/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "Player.h"
#include "Header.h"
#ifndef _H_GURD_COMPUTERPLAYER
#define _H_GURD_COMPUTERPLAYER

namespace AdvancedProgramingProjectBIU
{
    class ComputerPlayer : public Player
    {
        Board practiceBoard;
        /**********************************
		* C'tor
		* Aim: A normal ctor
		* Input: The way to stream, what to stream
		* Output: A new HumanPlayer
		* How it works?: initializing with Player's
							normal c'tor
		***********************************/
        ComputerPlayer(Type t, Board& b);

        /**********************************
		* Function: Act
		* Aim: To let the computer player pick his moves
		* Input: -
		* Output: Error, if any +makes the move
		* How it works?: goes with minMax
         * strategy, and bring the best results.
		***********************************/

        Error ComputerPlayer::Act();
    };
}

#endif //ADVANCED_PROGRAMMING_COMPUTERPLAYER_H
