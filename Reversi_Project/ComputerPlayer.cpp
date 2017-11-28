/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#define INFINITY 9999999

#include "ComputerPlayer.h"
#include "Header.h"
namespace AdvancedProgramingProjectBIU {
    Error ComputerPlayer::Act() {
        Board practiceBoard;
        Type enemy = (me==WHITE ? BLACK:WHITE);
        int max_score = -INFINITY;
        int min_score = INFINITY;
        int x_move, y_move;
        for (int i = 0; i < board.GetSize(); i++) {
            for (int j = 0; j < board.GetSize(); j++) {
                if (practiceBoard.CanPlaceHere(i, j, me)) {
                    min_score = INFINITY;
                    for (int k = 0; k < board.GetSize(); k++) {
                        for (int l = 0; l < board.GetSize(); l++) {
                            practiceBoard = Board(board);
                            practiceBoard.PlaceUnit(i, j, me);
                            if (practiceBoard.CanPlaceHere(k, l, enemy)) {
                                practiceBoard.PlaceUnit(k, l, enemy);
                                if (min_score > practiceBoard.GetScore(me))
                                    min_score = practiceBoard.GetScore(me);
                            }
                        }
                    }
                    if (max_score < min_score) {
                        max_score = min_score;
                        x_move = i;
                        y_move = j;
                    }
                }
            }
        }
        return board.PlaceUnit(x_move, y_move, me);
    }

    ComputerPlayer::ComputerPlayer(Type t, Board &b) : Player(t, b) {}
}