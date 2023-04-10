//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

//would have been cleaner to have CheessPiece as an abstract class 

int ChessPiece::validMove(int to_x, int to_y) {
    // Implementation goes here
    //will never be runned
    return 0;
}

string ChessPiece::getUtfRepresentation(){
    return utfRepresentation();
}

char ChessPiece::getLatin1Representation(){
    return latin1Representation();
}

bool ChessPiece::isWhite(){
    return m_is_white;
}

void ChessPiece::setIsWhite(bool newColor){
    m_is_white = newColor;
}

string ChessPiece::utfRepresentation() {
    // Implementation goes here
    //will never be runned
    return "h";
}

char ChessPiece::latin1Representation() {
    // Implementation goes here
    //will never be runned
    return 'h';
}

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board) : m_x(x), m_y(y), m_is_white(is_white), m_board(board)
/*:  Initialize members here */ {
}


bool ChessPiece::capturingMove(int to_x, int to_y) {
    return(this->validMove(to_x,to_y) == 2) ? true : false;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    return(this->validMove(to_x,to_y) == 1) ? true : false;
}

vector<ChessMove> ChessPiece::capturingMoves() {
    vector<ChessMove> vecCapturingMoves;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){ //Check any capturing move in all squares
            if((this -> capturingMove(x, y))){
                ChessMove pieceMove{this -> m_x, this -> m_y, x, y, this};
                vecCapturingMoves.push_back(pieceMove);
            }
        }
    }
    return vecCapturingMoves;
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    vector<ChessMove> vecNonCapturingMoves;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){ //Check any non-capturing move in all squares
            if((this -> nonCapturingMove(x, y))){
                ChessMove pieceMove{this -> m_x, this -> m_y, x, y, this};
                vecNonCapturingMoves.push_back(pieceMove);}
        }
    }
    return vecNonCapturingMoves;
}