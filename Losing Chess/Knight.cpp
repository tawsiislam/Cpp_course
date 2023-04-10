//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"

// Implement method definitions here

int Knight::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> targetSquare = this-> m_board -> getBoard()(to_x,to_y);

    if(targetSquare != nullptr && targetSquare -> isWhite() == this -> m_is_white){
        return 0;
    }
    
    int dx = ((this -> m_x) - to_x) * ((this -> m_x) - to_x);
    int dy = ((this -> m_y) - to_y) * ((this -> m_y) - to_y);
    if(dx+dy!=5){
        return 0;   //Invalid move
    }
    else{
        return (targetSquare == nullptr) ? 1:2;   //If Knight has valid move, check if square is empty or not
    }
}


char Knight::latin1Representation(){
    return this -> m_is_white ? 'N' : 'n';
}

string Knight::utfRepresentation(){
    return this -> m_is_white ? "♘" : "♞";;
}
