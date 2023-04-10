//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

int Pawn::validMove(int to_x, int to_y) {
    shared_ptr<ChessPiece> targetSquare = this-> m_board -> getBoard()(to_x,to_y);

    if(targetSquare != nullptr && targetSquare -> isWhite() == this -> m_is_white){
        return 0;
    }
    
    int signWhite = (m_is_white) ? -1:1;    //Used to switch between the condition for white and black
    int secondLastRow = (m_is_white) ? 6:1;   //Used for the condition if pawn promotion is possible

    if(targetSquare!=nullptr){
        if(((this -> m_x)+(signWhite*1) == to_x && ((this -> m_y)+1 == to_y || (this -> m_y)-1 == to_y))){  //Check if diagonal movement possible and valid
                return 2;
            }
    }
    else{
        if(((this -> m_x)+(signWhite*1) == to_x && (this -> m_y) == to_y) || ((this -> m_x) == secondLastRow && (this -> m_x)+(signWhite*2) == to_x && (this -> m_y) == to_y && (this -> m_board -> getBoard()((this -> m_x)+(signWhite*1), this -> m_y) == nullptr))){
                return 1;   //Normal movement or in the case pawn promotion is possible
            }
    }
    return 0;   //No valid movements
}


char Pawn::latin1Representation(){
    return this -> m_is_white ? 'P' : 'p';
}

string Pawn::utfRepresentation(){
    return this -> m_is_white ? "♙" : "♟";;
}
