/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/



Error ComputerPlayer::Act(){
    Board practiceBoard = Board(board);
    int best_score = -100;
    int x_move, y_move;
    for(int i = 0; i < size;i++){
        for(j=0;j<size;j++){
            if(practiceBoard.CanPlaceHere(i,j,me)){
                practiceBoard.PlaceUnit(i,j,me);
                for(int k = 0; k < size;k++){
                    for(int l = 0; l < size;l++){
                        if(practiceBoard.CanPlaceHere(i,j,!me)){
                            practiceBoard.PlaceUnit(i,j,me);
                            practiceBoard.
                        }
                    }
                }
            }
        }

    }
}
