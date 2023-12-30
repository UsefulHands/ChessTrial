#pragma once

#include "Piece.h"
#include "ChessBoard.h"

class Pawn : public Piece {
public:
	Pawn(ColorType colorType, PieceType pieceType, sf::Vector2f location);
	int moveNumber = 0;
	void findPossibleMoves(ChessBoard& board) override;
	void findIfPinned(ChessBoard& board, int i, int j) override;
};