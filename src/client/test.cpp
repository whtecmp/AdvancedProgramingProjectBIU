
#include "Board.h"
#include <gtest/gtest.h>
#include "Header.h"
#include "MainMenue.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using namespace std;
using namespace AdvancedProgramingProjectBIU;




TEST(Board, test)
{
	Board b;
	EXPECT_EQ(b.GetSquare(3, 1), NONE)
	EXPECT_EQ(b.GetSquare(4, 4), WHITE)
	EXPECT_EQ(b.GetSquare(3, 4), BLACK)
	b.PlaceUnit(2, 2, WHITE)
	EXPECT_EQ(b.GetSquare(2, 2), NONE)
	b.PlaceUnit(3, 2, BLACK)
	EXPECT_EQ(b.GetSquare(3, 2), BLACK)
	
	Board b(14);
	EXPECT_EQ(b.GetSquare(3, 1), NONE)
	EXPECT_EQ(b.GetSquare(7, 7), WHITE)
	EXPECT_EQ(b.GetSquare(6, 7), BLACK)
	b.PlaceUnit(5, 5, WHITE)
	EXPECT_EQ(b.GetSquare(5, 5), NONE)
	b.PlaceUnit(6, 5, BLACK)
	EXPECT_EQ(b.GetSquare(6, 5), BLACK)
	
	
}

TEST(MainMenue, test)
{
	Error e = SUCCESS;
	try MainMenue(false);
	catch e;
	EXPECT_EQ(e, SUCCESS)
	try MainMenue(false);
	catch e;
	EXPECT_EQ(e, MORE_THEN_ONE_SINGLETONE)
}

TEST(Player, test)
{
	Player* humanPlayer = new HumanPlayer();
	Player* computerPlayer = new ComputerPlayer();
}



int main(int argc, char **argv)
{
	
	::testing::InitGoogleTest(&argc,argv);
	
	return RUN_ALL_TESTS();
	
}

