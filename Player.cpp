/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#include "Player.h"
namespace AdvancedProgramingProjectBIU {
    static Type operator!(Type t) { return t == BLACK? WHITE : (t==NONE?NONE:BLACK); }

    void Player::UpdateScore() {
        this->score = 0;
        Type const myType = this->me;
        for (int i = 0; i < board.GetSize(); i++) {
            for (int j = 0; j < board.GetSize(); j++) {
                if (this->board.GetSquare(i, j) == this->me)
                    this->score++;
                if (this->board.GetSquare(i, j) == !this->me)
                    this->score--;
            }
        }
    }
}