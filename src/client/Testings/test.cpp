
#include "../Board.h"
#include <gtest/gtest.h>
#include "../Header.h"
#include "../MainMenue.h"
#include "../Player.h"
#include "../ComputerPlayer.h"
#include "../HumanPlayer.h"
#include <iostream>

using namespace std;
using namespace AdvancedProgramingProjectBIU;




TEST(Board, test)
{
	Board b;
	EXPECT_EQ(b.GetSquare(3, 1), NONE);
	EXPECT_EQ(b.GetSquare(4, 4), WHITE);
	EXPECT_EQ(b.GetSquare(3, 4), BLACK);
	b.PlaceUnit(2, 2, WHITE);
	EXPECT_EQ(b.GetSquare(1, 1), NONE);
	b.PlaceUnit(4, 3, BLACK);
	EXPECT_EQ(b.GetSquare(3, 2), BLACK);
	
	Board c(14);
	EXPECT_EQ(c.GetSquare(3, 1), NONE);
	EXPECT_EQ(c.GetSquare(7, 7), WHITE);
	EXPECT_EQ(c.GetSquare(6, 7), BLACK);
	c.PlaceUnit(5, 5, WHITE);
	EXPECT_EQ(c.GetSquare(4, 4), NONE);
	c.PlaceUnit(7, 6, BLACK);
	EXPECT_EQ(c.GetSquare(6, 5), BLACK);
	
	
}

TEST(MainMenue, test)
{
	Error e = SUCCESS;
	try {MainMenue(false);}
	catch (Error f){e=f;}
	EXPECT_EQ(e, SUCCESS);
	try {MainMenue(false);}
	catch (Error f){e=f;}
	EXPECT_EQ(e, MORE_THEN_ONE_SINGLETONE);
}

TEST(Player, test)
{
	Board b;
	Player* humanPlayer = new HumanPlayer(WHITE, b);
	Player* computerPlayer = new ComputerPlayer(WHITE, b);
	delete computerPlayer;
	delete humanPlayer;
}



int main(int argc, char **argv)
{
	
	::testing::InitGoogleTest(&argc,argv);
	
	return RUN_ALL_TESTS();
	
}

