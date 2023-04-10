//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <istream>
#include <memory>
#include "ChessMove.h"
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h

using namespace std;

class ChessPiece;

class ChessBoard {
    // add additional members or functions of your choice
private:
    // Alternative 1 (the matrix owns the chess pieces):
    Matrix<shared_ptr<ChessPiece>> m_state{8}; // Matrix from lab 2
    vector<ChessPiece *> m_white_pieces;
    vector<ChessPiece *> m_black_pieces;
    
public:
    Matrix<shared_ptr<ChessPiece>> & getBoard(){ return m_state; };
    vector<ChessPiece *> & getWhitePieces(){ return m_white_pieces; };
    vector<ChessPiece *> & getBlackPieces(){ return m_black_pieces; };
    
    void createBoard(ChessBoard & cb, char piece, int x, int y);
    void movePiece(ChessMove chessMove);
    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);

    //Ai related methods
    bool randomThinkerAI(bool is_white);
    bool smartAI(bool is_white);
    ChessMove ForceCaptureOpponent(vector<ChessMove> chessMoves, bool is_white);
    void replacePawn(ChessMove chessMove, int newPiece, int x, int y, bool is_white);
    //void pawnPromotionRandom(ChessMove chessMove, bool is_white);
    void pawnPromotion(ChessMove chessMove, bool is_white, bool randomChoice); //Add bool random 
    void checkForceCapture(ChessMove chessMove, int x, int y, bool is_white);
};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);

#endif //CHESSBOARD_H
