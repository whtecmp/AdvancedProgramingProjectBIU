/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_HEADER
#define _H_GURD_HEADER

#include <iostream>

//namespace to keep things organized
namespace AdvancedProgramingProjectBIU
{

	//#define DEBUG
	
	#ifdef DEBUGca
	#define D(A) A
	#define IFD(A) {if (!debug){A}}
	#else
	#define D(A) 
	#define IFD(A) 
	#endif /* DEBUG */

	#define SUCCESS NO_ERROR

	enum Error 
	{
		NO_ERROR = 0,
		MORE_THEN_ONE_SINGLETONE,
		POSITION_IS_TAKEN,
		CAPTURES_NO_ONE,
	};

	enum Type {BLACK, WHITE, NONE};
	
	
//	Type operator!(Type t);
//	std::ostream& operator<<(std::ostream& os, Type t);
}

#endif /* _H_GURD_HEADER */