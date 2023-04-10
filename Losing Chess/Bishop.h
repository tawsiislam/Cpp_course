//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece {
    // Override virtual methods from ChessPiece here
    protected:
        virtual int validMove(int to_x, int to_y) override;
        string utfRepresentation() override;
        char latin1Representation() override;
        
    public:
        using ChessPiece::ChessPiece;
};

#endif //BISHOP_H
