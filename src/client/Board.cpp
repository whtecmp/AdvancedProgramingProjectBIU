/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "Board.h"
#include "MainMenue.h"

#define NUM_OF_DIRECTIONS 8

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{
static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }
static std::ostream& operator<<(std::ostream& os, Type t) { return os << (t==BLACK?'X':(t==NONE?'N':'O')); }

	#define PRINT_LINE_OF_LINES os << "--"; \
	for (int i = 0; i < b.size; i++) \
		{os << "----";} \
	os << std::endl;

	/**********************************
	* Operator: <<
	* Aim: A stream method
	* Input: The way to stream, what to stream
	* Output: The way to stream
	* How it works?: Goes over the matrix,
		theBoard and streams one by one
	***********************************/
	std::ostream& operator<<(std::ostream& os, const Board& b)
	{
		os << ' ' << '|';
		for (int i = 0; i < b.size; i++)
			os << ' ' << i + 1 << ' '<< '|';
		os << std::endl;
		PRINT_LINE_OF_LINES
		for (int i = 0; i < b.size; i++)
		{
			os << i + 1 << '|';
			for (int j = 0; j < b.size; j++)
			{
				char c = ((b.theBoard[i][j] == NONE) ? ' ' : (b.theBoard[i][j] == WHITE ? 'O' : 'X'));
				os << ' ' << c << ' ' << '|';
			}
			os << std::endl;
			PRINT_LINE_OF_LINES
		}
		return os;
	}



	/******************************************
	* Macro: CHECK_LEGALITY
	* Aim: Check if the direction dir captures enemies
	* Input: The direction, the right arithmetics macros
	* How it works? Looks at the board and determines
					if it is leagal or not to capture
					in this direction
	*********************************************/
	#define CHECK_LEGALITY(DIR, OPX, OPY) if(done[DIR] == UNDETRMINED) \
	{ \
		if(x OPX(i) < 0 || x OPX(i) >= size || y OPY(i) < 0 || y OPY(i) >= size) \
			{done[DIR] = ILEAGLE;} \
		else if(theBoard[x OPX(i)][y OPY(i)] == NONE ) \
			{done[DIR] = ILEAGLE;} \
		else if(theBoard[x OPX(i)][y OPY(i)] == who) \
			{if(capIn[DIR]){done[DIR] = CAPTURED;} else {done[DIR]=ILEAGLE;}} \
		else if(theBoard[x OPX(i)][y OPY(i)] == !who) \
			{capIn[DIR]=true;} \
	}



	/******************************************
	* Macro: CAPTURE
	* Aim: The algorithem that captures enemies
	* Input: The direction, the right arithmetics macros
	* How it works? Captures the enemy units
	*********************************************/
	#define CAPTURE(DIR, OPX, OPY) \
	{ \
		if (done[DIR]==CAPTURED) \
		{ \
			if(theBoard[x OPX(i)][y OPY(i)] == NONE) \
				{done[DIR]=UNDETRMINED;} \
			else \
				{theBoard[x OPX(i)][y OPY(i)] = who;} \
		} \
	}


	//small Macros for arithmetics
	#define ADD(X) + X
	#define SUB(X) - X
	#define IGN(X)


	/******************************************
	* Macro: ACTIVATE_ALL_DIRECTIONS
	* Aim: To be able to use 1 algorithem for every direction
			without copying code
	* Input: another macro
	* How it works? For every direction, calls the macro
					with appropriate directions.
	*********************************************/
	#define ACTIVATE_ALL_DIRECTIONS(A) \
	{ \
		A(LEFT, SUB, IGN) \
		A(RIGHT, ADD, IGN) \
		A(UP, IGN, SUB) \
		A(DOWN, IGN, ADD) \
		 \
		A(LEFTUP, SUB, SUB) \
		A(LEFTDOWN, SUB, ADD) \
		A(RIGHTDOWN, ADD, ADD) \
		A(RIGHTUP, ADD, SUB) \
	}

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
	Error Board::PlaceUnit(int x, int y, Type who)
	{
        x = x - 1; y = y - 1;
		if (theBoard[x][y] != NONE)
			return POSITION_IS_TAKEN;
		bool loop = true;
		enum {LEFT=0,RIGHT=1,UP=2,DOWN=3,LEFTUP=4,LEFTDOWN=5,RIGHTDOWN=6,RIGHTUP=7};
		enum status {ILEAGLE, CAPTURED, UNDETRMINED};
		status done[NUM_OF_DIRECTIONS];
		bool capIn[NUM_OF_DIRECTIONS];

		for (int i = 0; i < NUM_OF_DIRECTIONS; i++)
			done[i] = UNDETRMINED;
        for (int i = 0; i < NUM_OF_DIRECTIONS; i++)
			capIn[i] = false;
        for (int i = 1; i < size; i++)
		{
            ACTIVATE_ALL_DIRECTIONS(CHECK_LEGALITY)
		}

        bool prob = true;
		for (int s = LEFT; s<=RIGHTUP;s++)
		{
			if (done[s] == CAPTURED)
				prob = false;
		}

        if(prob)
			return CAPTURES_NO_ONE;

		for (int i = 1; i < size; i++)
		{
			ACTIVATE_ALL_DIRECTIONS(CAPTURE)
		}
		theBoard[x][y] = who;

        return NO_ERROR;
	}

	/******************************************
	* Function: CanPlaceHere
	* Aim: To see if it is legal to place here
	* Input: position and player
	* Output: Legal or not
	* How it works? uses same algorithem as the one
					that places/flips the tokens, except
					it won't place/flip them.
	*********************************************/
	bool Board::CanPlaceHere(int x, int y, Type who)
	{
		x = x - 1; y = y - 1;
		if (theBoard[x][y] != NONE)
			return false;

        bool loop = true;
		enum {LEFT=0,RIGHT=1,UP=2,DOWN=3,LEFTUP=4,LEFTDOWN=5,RIGHTDOWN=6,RIGHTUP=7};
		enum status {ILEAGLE, CAPTURED, UNDETRMINED};
		status done[NUM_OF_DIRECTIONS];
		bool capIn[NUM_OF_DIRECTIONS];

        for (int i = 0; i < NUM_OF_DIRECTIONS; i++)
			done[i] = UNDETRMINED;

        for (int i = 0; i < NUM_OF_DIRECTIONS; i++)
			capIn[i] = false;

		for (int i = 1; i < size; i++)
		{
			ACTIVATE_ALL_DIRECTIONS(CHECK_LEGALITY)
		}


        bool legal = false;
		for (int s = LEFT; s<=RIGHTUP;s++)
		{
			if (done[s] == CAPTURED)
				legal = true;
		}

        return legal;
	}


	/******************************************
	* C'tor: Default C'tor
	* Aim: Can only change size
	* Input: The size, deafaultly GetSize()
	* Output: The board
	* How it works? Creates a matrix of this size
		and gives it its default values
	*********************************************/
	Board::Board(unsigned int size)
	{
		this->size = size;
		theBoard = new Type*[size + 2];
		for (int i = 0; i <= size + 1; i++)
		{
			theBoard[i] = new Type[size + 2];
			for (int j = 0; j <= size + 1; j++)
				theBoard[i][j] = NONE;
		}
		theBoard[size/2 - 1][size/2 - 1] = theBoard[size/2][size/2] = WHITE;
		theBoard[size/2 - 1][size/2] = theBoard[size/2][size/2 - 1] = BLACK;
	}
	Board::Board(Board &oldBoard)
	{
        this->size = oldBoard.GetSize();
        theBoard = new Type*[size + 2];
        for(int i=0; i < size;i++){
            theBoard[i] = new Type[size + 2];
            for(int j=0;j < size;j++) {
                theBoard[i][j] = oldBoard.GetSquare(i, j);
            }
        }
	}

    int Board::GetScore(Type me){
        int score = 0;
        for (int i = 0; i < GetSize(); i++) {
            for (int j = 0; j < GetSize(); j++) {
                if (this->GetSquare(i, j) == me)
                    score++;
                if (this->GetSquare(i, j) == !me)
                    score--;
            }
        }
        return score;
    }
	/********************************
	* D'tor
	* How it works? Realese theBoard
	*********************************/
	Board::~Board()
	{
		for (int i = 0; i <= size + 1; i++)
		{
			delete theBoard[i];
		}
		delete theBoard;
	}

}
