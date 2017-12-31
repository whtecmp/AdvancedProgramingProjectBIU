/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_BOARD
#define _H_GURD_BOARD

#include <iostream>
#include "Header.h"


//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

	/************************************************
	* Class Name: Board
	* Class Aim: To manage the board of a reversy game
	************************************************/
	class Board
	{
	private:


		int size;

		Type** theBoard;

	public:


        Type GetSquare(unsigned i,unsigned j){return theBoard[i][j];}
		//standard getter
		int GetSize() {return size;}

		//standard getter
		int GetScore(Type me);

		/******************************************
		* Function: PlaceUnit
		* Aim: Place in position a token
		* Input: position and player
		* Output: If there was an error or not
		* How it works? Goes over all possible directions
						to see if the move captures someone
						if so, put the token and flip
						else, returns error.
		*********************************************/
		Error PlaceUnit(int x, int y, Type who);


		/******************************************
		* Function: CanPlaceHere
		* Aim: To see if it is legal to place here
		* Input: position and player
		* Output: Legal or not
		* How it works? uses same algorithem as the one
						that places/flips the tokens, except
						it won't place/flip them.
		*********************************************/
		bool CanPlaceHere(int x, int y, Type who);

		/**********************************
		* Operator: <<
		* Aim: A stream method
		* Input: The way to stream, what to stream
		* Output: The way to stream
		* How it works?: Goes over the matrix,
			theBoard and streams one by one
		***********************************/
		friend std::ostream& operator<<(std::ostream& os, const Board& b);


		/******************************************
		* C'tor: Default C'tor
		* Aim: Can only change size
		* Input: The size, deafaultly 8
		* How it works? Creates a matrix of this size
			and gives it its default values
		*********************************************/
		Board(unsigned int size = 8);

        /******************************************
		* C'tor: Default C'tor
		* Aim: Can only change size
		* Input: The size, deafaultly 8 and a board to copy
		* How it works? Creates a matrix of this size
			and copy the points from the oldBoard;
		*********************************************/
		Board(Board &oldBoard);
		/*******************************
		* D'tor
		* How it works? Realese theBoard
		********************************/
		~Board();
	};


	/**********************************
	* Operator: <<
	* Aim: A stream method
	* Input: The way to stream, what to stream
	* Output: The way to stream
	* How it works?: Goes over the matrix,
		theBoard and streams one by one
	***********************************/
	std::ostream& operator<<(std::ostream& os, const Board& b);
}


#endif /* _H_GURD_BOARD */
