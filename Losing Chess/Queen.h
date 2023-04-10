//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook {
    // Override virtual methods from ChessPiece here
    protected:
        virtual int validMove(int to_x, int to_y) override;
        string utfRepresentation() override;
        char latin1Representation() override;
        
    public:
    Queen(int x, int y, bool is_white, ChessBoard* board);
};


#endif //QUEEN_H
