//
// DD1388 - Lab 4: Losing Chess
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
    // Override virtual methods from ChessPiece here
    protected:
        virtual int validMove(int to_x, int to_y) override;
        string utfRepresentation() override;
        char latin1Representation() override;
        
    public:
        using ChessPiece::ChessPiece;
};


#endif //PAWN_H
