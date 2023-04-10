//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

int Rook::validMove(int to_x, int to_y) {  
    shared_ptr<ChessPiece> targetSquare = this-> m_board -> getBoard()(to_x,to_y);

    if(targetSquare != nullptr && targetSquare -> isWhite() == this -> m_is_white){
        return 0;
    }
    
    int dx = abs((this -> m_x) - to_x);
    int dy = abs((this -> m_y) - to_y);
    //check if the desired square is in the horizontal or veritcal position of the rook
    if(dx==0){  //Movement only in y-direction, check any blocking pieces
        int start = (this->m_y < to_y) ? this->m_y : to_y;
        int end = (this->m_y > to_y) ? this->m_y : to_y;
        for(int y = 1+start; y < end; y++){
            if(this -> m_board -> getBoard()(to_x, y) != nullptr){
                return 0;
            }
        }        
    }
    else if (dy==0){    //Movement only in x-direction, check any blocking pieces
        int start = (this->m_x < to_x) ? this->m_x : to_x;
        int end = (this->m_x > to_x) ? this->m_x : to_x;
        for(int x = 1+start; x < end; x++){
            if(this -> m_board -> getBoard()(x, to_y) != nullptr){
                return 0;
            }
        }
    }
    
    if(dx==0||dy==0){   //If no blocking pieces
        if(targetSquare != nullptr){
            return 2;
        }
        return 1;
    }
    return 0;
}


char Rook::latin1Representation(){
    return this -> m_is_white ? 'R' : 'r';
}

string Rook::utfRepresentation(){
    return this -> m_is_white ? "♖" : "♜";;
}
