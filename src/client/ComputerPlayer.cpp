/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#define INFINITY 9999999
using namespace std;

#include "ComputerPlayer.h"
#include "Header.h"
namespace AdvancedProgramingProjectBIU {
    Error ComputerPlayer::Act() {
        Board *practiceBoard;
        Board *practiceBoard2;

        Type enemy = (me==WHITE ? BLACK:WHITE);
        int max_score = -INFINITY;
        int min_score = INFINITY;
        int x_move, y_move;
        for (int i = 1; i < board.GetSize(); i++) {
            for (int j = 1; j < board.GetSize(); j++) {
                if (board.CanPlaceHere(i, j, me)) {
                    practiceBoard = new Board(board);
                    practiceBoard->PlaceUnit(i,j,me);
                    min_score = INFINITY;
                    for (int k = 1; k < practiceBoard->GetSize(); k++) {
                        for (int l = 1; l < practiceBoard->GetSize(); l++) {
                            practiceBoard2 = new Board(*practiceBoard);
                            practiceBoard2->PlaceUnit(i, j, me);

                            if (practiceBoard2->CanPlaceHere(k, l, enemy)) {
                                practiceBoard2->PlaceUnit(k, l, enemy);
                                if (min_score > practiceBoard2->GetScore(me)) {
                                    min_score = practiceBoard2->GetScore(me);
                                }
                            }
                            delete practiceBoard2;

                        }
                    }
                    if (max_score < min_score) {
                        max_score = min_score;
                        x_move = i;
                        y_move = j;
                    }
                    delete practiceBoard;
                }
            }
        }
        return board.PlaceUnit(x_move, y_move, me);
    }

    ComputerPlayer::ComputerPlayer(Type t, Board &b) : Player(t, b) {}
}