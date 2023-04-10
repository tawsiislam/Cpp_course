//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <time.h>

using namespace std;

void ChessBoard::movePiece(ChessMove chess_move) {

    if(m_state(chess_move.to_x, chess_move.to_y) != nullptr){   //If target square is not empty, a piece will be captured
        bool isWhite = (m_state(chess_move.to_x, chess_move.to_y)->m_is_white); //Check the color that will be captured
        if(isWhite){
            for(int i = 0; i < m_white_pieces.size(); i++){
                if(m_white_pieces[i] == m_state(chess_move.to_x, chess_move.to_y).get()){
                    m_white_pieces.erase(m_white_pieces.begin() + i);   //Remove the white piece when matching pieces found
                }
            }
        }else{
            for(int i = 0; i < m_black_pieces.size(); i++){
                if(m_black_pieces[i] == m_state(chess_move.to_x, chess_move.to_y).get()){
                    m_black_pieces.erase(m_black_pieces.begin() + i);   //Remove the black piece when matching pieces found
                }
            }
        }
    }

    //update board
    this -> m_state(chess_move.to_x, chess_move.to_y) = this -> m_state(chess_move.from_x, chess_move.from_y); //copy value
    this -> m_state(chess_move.to_x, chess_move.to_y) -> m_x = chess_move.to_x;
    this -> m_state(chess_move.to_x, chess_move.to_y) -> m_y = chess_move.to_y;
    this -> m_state(chess_move.to_x, chess_move.to_y) -> m_is_white = this -> m_state(chess_move.from_x, chess_move.from_y) -> m_is_white;  //Change which color is on the square
    this -> m_state(chess_move.from_x, chess_move.from_y) = nullptr; //clear the sqaure
}


vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    // Implementation goes here
    vector<ChessMove> vecCapturingMoves;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            shared_ptr<ChessPiece> colorPiece = this->getBoard()(x,y);
            if (colorPiece != nullptr && colorPiece->isWhite() == is_white) {   //Non-empty square gives a pieces and check if the color matches with who's turn it is
                auto allMoves = colorPiece -> capturingMoves();
                for(int b = 0; b < allMoves.size(); b++){
                    vecCapturingMoves.push_back(allMoves[b]);   //Append to vector with all capturing moves for this particular piece
                }
            }
        }
    }
    return vecCapturingMoves;
}


vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    // Implementation goes here
    vector<ChessMove> vecNonCapturingMoves;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            shared_ptr<ChessPiece> colorPiece = this->getBoard()(x,y);
            if (colorPiece != nullptr && colorPiece->isWhite() == is_white) {   //Non-empty square gives a pieces and check if the color matches with who's turn it is
                auto allNonMoves = colorPiece -> nonCapturingMoves();
                for(int b = 0; b < allNonMoves.size(); b++){
                    vecNonCapturingMoves.push_back(allNonMoves[b]); //Append to vector with all non-capturing moves for this particular piece
                }
            }
        }
    }
    return vecNonCapturingMoves;
}


void ChessBoard::createBoard(ChessBoard & cb, char piece, int x, int y){    //Create the board with all pieces after inputted board
    switch(piece){
        case 'R':
            cb.getBoard()(x,y) = make_shared<Rook>(x, y, true, &cb);
            break;
        case 'r':
            cb.getBoard()(x,y) = make_shared<Rook>(x, y, false, &cb);
            break;
        case 'N':
            cb.getBoard()(x,y) = make_shared<Knight>(x, y, true, &cb);
            break;
        case 'n':
            cb.getBoard()(x,y) = make_shared<Knight>(x, y, false, &cb);
            break;
        case 'B':
            cb.getBoard()(x,y) = make_shared<Bishop>(x, y, true, &cb);
            break;
        case 'b':
            cb.getBoard()(x,y) = make_shared<Bishop>(x, y, false, &cb);
            break;
        case 'Q':
            cb.getBoard()(x,y) = make_shared<Queen>(x, y, true, &cb);
            break;
        case 'q':
            cb.getBoard()(x,y) = make_shared<Queen>(x, y, false, &cb);
            break;
        case 'K':
            cb.getBoard()(x,y) = make_shared<King>(x, y, true, &cb);
            break;
        case 'k':
            cb.getBoard()(x,y) = make_shared<King>(x, y, false, &cb);
            break;
        case 'P':
            cb.getBoard()(x,y) = make_shared<Pawn>(x, y, true, &cb);
            break;
        case 'p':
            cb.getBoard()(x,y) = make_shared<Pawn>(x, y, false, &cb);
            break;
        default:
            throw invalid_argument("Recived unidentified character in inputted board!");
    }
    if(isupper(piece)){
        cb.getWhitePieces().push_back(cb.getBoard()(x, y).get());   //Add the piece to correct vector for depending on its color
    }else{
        cb.getBlackPieces().push_back(cb.getBoard()(x, y).get());   //Add the piece to correct vector for depending on its color
    }
}

void ChessBoard::checkForceCapture(ChessMove chessMove, int x, int y, bool is_white){
    
    //make the pawn a knight
    this -> getBoard()(x,y) = make_shared<Knight>(x, y, is_white, this);
    if((this -> getBoard()(x,y) -> capturingMoves()).empty()){
        return; //return the knight if it cannot capture a piece from its position (x,y)
    }
    
    //Test with a Rook
    this -> getBoard()(x,y) = make_shared<Rook>(x, y, is_white, this);
    if((this -> getBoard()(x,y) -> capturingMoves()).empty()){
        return; //return the Rook if it cannot capture a piece from its position (x,y)
    }
    
    //Test with a Queen
    this -> getBoard()(x,y) = make_shared<Queen>(x, y, is_white, this);
    if((this -> getBoard()(x,y) -> capturingMoves()).empty()){
        return; //return the Queen if it cannot capture a piece from its position (x,y)
    }
    
    //Test with a Bishop
    this -> getBoard()(x,y) = make_shared<Bishop>(x, y, is_white, this);
    if((this -> getBoard()(x,y) -> capturingMoves()).empty()){
        return; //return the Bishop if it cannot capture a piece from its position (x,y)
    }
    
    //If all pieces has capturing moves, return a random piece that can promote the pawn
    int randomInt = rand() % 3 + 0;
    replacePawn(chessMove, randomInt, x, y, is_white);
    return;
}

void ChessBoard::replacePawn(ChessMove chessMove, int newPiece, int x, int y, bool is_white){
    switch(newPiece){
        case 0:
            this -> getBoard()(x,y) = make_shared<Queen>(x, y, is_white, this);
            break;
        case 1:
            this -> getBoard()(x,y) = make_shared<Bishop>(x, y, is_white, this);
            break;
        case 2:
            this -> getBoard()(x,y) = make_shared<Knight>(x, y, is_white, this);
            break;
        case 3:
            this -> getBoard()(x,y) = make_shared<Rook>(x, y, is_white, this);
            break;
    }
}

void ChessBoard::pawnPromotion(ChessMove chessMove, bool is_white, bool randomPromotion){
    char pieceColor = chessMove.piece -> getLatin1Representation();
    vector<ChessPiece*>& colorPieces = (is_white) ? this -> m_white_pieces : this -> m_black_pieces;
    char pawnColor;
    int colorLastRow;
    if(is_white){
        colorPieces = this -> m_white_pieces;
        pawnColor = 'P';
        colorLastRow = 0;
    }
    else{
        colorPieces = this -> m_black_pieces;
        pawnColor = 'p';
        colorLastRow = 7;
    }

    if(pieceColor == pawnColor && chessMove.to_x == colorLastRow){  //If pawn promotion is allowed
        int newPiece;
        if(randomPromotion == false){   //For the case with smart AI
            checkForceCapture(chessMove, chessMove.to_x, chessMove.to_y, is_white);
        }
        else{   // For the case with Random thinking AI
            srand(time(NULL));
            int newPiece = rand() % 3;
            replacePawn(chessMove, newPiece ,chessMove.to_x, chessMove.to_y, is_white);
        }
        
        
        for(int i = 0; i < colorPieces.size(); i++){
            if(chessMove.piece == colorPieces[i]){
                colorPieces[i] = this -> getBoard()(chessMove.to_x, chessMove.to_y).get(); //Replace the pawn with new piece in the vector with all playing pieces
            }
        }
    }
}

ChessMove ChessBoard::ForceCaptureOpponent(vector<ChessMove> chessMoves, bool is_white){    
    auto &opponentPieces = (is_white) ? this -> m_black_pieces : this -> m_white_pieces;
    for(int i = 0; i < chessMoves.size(); i++){
        for(int j = 0; j < opponentPieces.size(); j++){
            int target_x = chessMoves[i].to_x;
            int target_y = chessMoves[i].to_y;
            auto targetSquare = this -> getBoard()(target_x,target_y);
            
            if(targetSquare == nullptr){
                if(opponentPieces[j] -> nonCapturingMove(target_x,target_y)){
                    return chessMoves[i];   //Return the move if that move is non-capturing for the opponent
                }
            }
            else{
                targetSquare -> setIsWhite(!(targetSquare ->isWhite()));    //Change the opponent's piece's color temporary to your color
                if(opponentPieces[j]->capturingMove(target_x, target_y)){
                    targetSquare -> setIsWhite(!(targetSquare ->isWhite())); //change back to original
                    return chessMoves[i];   //Return the move if you can be captured at target square
                }
                targetSquare -> setIsWhite(!(targetSquare ->isWhite()));    //Change back to original if the if-condition was not fulfilled

            }
        }
    }
    ChessMove emptyVec;
    emptyVec.piece = nullptr;
    return emptyVec;
}

bool ChessBoard::randomThinkerAI(bool is_white){
    vector<ChessMove> allCapturingMoves = capturingMoves(is_white);
    vector<ChessMove> allNonCapturingMoves = nonCapturingMoves(is_white);
    vector<ChessMove>& chosenMoves = allCapturingMoves;
    if(allCapturingMoves.empty() && allNonCapturingMoves.empty()){
        return true;     //if the player cannot move any piece, they have won
    }
    else{
        chosenMoves = (allCapturingMoves.empty()) ? allNonCapturingMoves : allCapturingMoves;
    }

    srand(time(NULL));
    int randMove = rand() % chosenMoves.size();
    movePiece(chosenMoves[randMove]);
    srand(time(NULL));
    int randProm = rand() % chosenMoves.size();
    pawnPromotion(chosenMoves[randProm], is_white,true);
    return false;
}

bool ChessBoard::smartAI(bool is_white){
    vector<ChessMove> allCapturingMoves = capturingMoves(is_white);
    vector<ChessMove> allNonCapturingMoves = nonCapturingMoves(is_white);
    
    vector<ChessMove>& chosenMoves = allCapturingMoves;
    if(allCapturingMoves.empty() && allNonCapturingMoves.empty()){
        return true;     //if the player cannot move any piece, they have won
    }
    else{
        chosenMoves = (allCapturingMoves.empty()) ? allNonCapturingMoves : allCapturingMoves;
    }

    auto possibleForceCaptureMove = ForceCaptureOpponent(chosenMoves,is_white);
    if(possibleForceCaptureMove.piece != nullptr){  //If we can force capture
        movePiece(possibleForceCaptureMove);
        pawnPromotion(possibleForceCaptureMove, is_white,false);
    }
    else{   //Otherwise play like randomThinkerAI
        srand(time(NULL));
        int randMove = rand() % chosenMoves.size();
        movePiece(chosenMoves[randMove]);
        srand(time(NULL));
        int randProm = rand() % chosenMoves.size();
        pawnPromotion(chosenMoves[randProm], is_white,true);
    }
    return false;
}

ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    // Implementation goes here
    string line;
    for(int row = 0; row < 8; row++){
        getline (is,line);
        for(int i = 0; i < 8; i++){
            if(line[i] != '.'){
                cb.createBoard(cb, line[i], row, i);
            }
        }
    }
    return cb;
}


ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    // Implementation goes here
    cout << "--------\n";
    auto board = cb.getBoard();
    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            if(board(row, column) != nullptr){
                cout << board(row, column) -> getLatin1Representation();
            }else{
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << "--------\n";
    
    return cb;
}

