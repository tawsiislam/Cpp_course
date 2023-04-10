//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"

Queen::Queen(int x, int y, bool is_white, ChessBoard* board) : ChessPiece(x, y, is_white, board) , Bishop(x, y, is_white, board), Rook(x, y, is_white, board) {}
int Queen::validMove(int to_x, int to_y) {
    
    int rookMoveValid = Rook::validMove(to_x, to_y);    //Check move when Queen is like Rook
    int bishopMoveValid = Bishop::validMove(to_x, to_y);    //Check move when Queen is like Bishop

    return ((bishopMoveValid >= rookMoveValid) ? bishopMoveValid : rookMoveValid);  //Returns the moves vector that has the most.
}


char Queen::latin1Representation(){
    return this -> m_is_white ? 'Q' : 'q';
}

string Queen::utfRepresentation(){
    return this -> m_is_white ? "♕" : "♛";
}
