/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include <iostream>
#include "MainMenue.h"

//namespace to keep things organized
using namespace AdvancedProgramingProjectBIU;

static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }
static std::ostream& operator<<(std::ostream& os, Type t) { return os << (t==BLACK?'X':(t==NONE?'N':'O')); }




/******************************************
* Function Name: main
* Aim: The startup of the program, initializing
	and starting the game. Then at the end
	cleaning up.
* Input: None
* Output: An unimportant int (0)
* How it works? Calls the appropriate MainMenue
	class.
*********************************************/
int main()
{
	new MainMenue();
	delete flow;
	return 0;
}
