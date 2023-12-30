#pragma once

#include "Piece.h"
#include "ChessBoard.h"

class Piece;

class Rook : public Piece {
public:
	//Constructor
	Rook(ColorType colorType, PieceType pieceType, sf::Vector2f location);
	//Overriden function
	void findPossibleMoves(ChessBoard& board) override;
	void findIfPinned(ChessBoard& board, int i, int j) override;
};
