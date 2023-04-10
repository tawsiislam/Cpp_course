//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"
// Implement method definitions here

int King::validMove(int to_x, int to_y) {
   shared_ptr<ChessPiece> targetSquare = this-> m_board -> getBoard()(to_x,to_y);

    if(targetSquare != nullptr && targetSquare -> isWhite() == this -> m_is_white){
        return 0;
    }
    
    int dx = abs((this -> m_x) - to_x);
    int dy = abs((this -> m_y) - to_y);
    if((dx+dy!=1) && (dx*dy!=1)){
        return 0;   //Invalid move
    }
    else{
        return (targetSquare == nullptr) ? 1:2;   //If King take one step, check if square is empty or not
    }
}


char King::latin1Representation(){
    return this -> m_is_white ? 'K' : 'k';
}

string King::utfRepresentation(){
    return this -> m_is_white ? "♔" : "♚";
}





