//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"
// Implement method definitions here

int Bishop::validMove(int to_x, int to_y) {    
    shared_ptr<ChessPiece> targetSquare = this-> m_board -> getBoard()(to_x,to_y);  //The square we want to move to
    if(targetSquare != nullptr && targetSquare -> isWhite() == this -> m_is_white){ //Return 0 if the piece at targetSquare is same color
        return 0;
    }
    
    int dx = abs((this -> m_x) - to_x);
    int dy = abs((this -> m_y) - to_y);
    if(dx==dy){
        for(int i= 1; i < dx; i++){
            if(this -> m_x > to_x && this -> m_y > to_y && (this->m_board->getBoard()(this->m_x-i,this->m_y-i)!=nullptr)){ //Check if any piece block southwest direction
                return 0;
            }
            else if(this -> m_x > to_x && this -> m_y < to_y && (this->m_board->getBoard()(this->m_x-i,this->m_y+i)!=nullptr)){ //Any piece blocking northwest direction
                return 0;
            }
            else if(this -> m_x < to_x && this -> m_y < to_y && (this->m_board->getBoard()(this->m_x+i,this->m_y+i)!=nullptr)){ //Any piece blocking northeast direction
                return 0;
            }
            else if(this -> m_x < to_x && this -> m_y > to_y && (this->m_board->getBoard()(this->m_x+i,this->m_y-i)!=nullptr)){ //Any piece blocking southeast direction
                return 0;
            }
        }
        return(targetSquare != nullptr) ? 2 : 1;    //No blocking piece, check if square is occupied or not
    }
    else{
        return 0;
    }
}


char Bishop::latin1Representation(){
    return this -> m_is_white ? 'B' : 'b';
}

string Bishop::utfRepresentation(){
    // correct way doesnt work for me char32_t ch4{L'\u2654'};
    return this -> m_is_white ? "♗" : "♝";;
}
