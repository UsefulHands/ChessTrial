#pragma once

#include "Piece.h"
#include "ChessBoard.h"

class Bishop : public Piece {
public:
	Bishop(ColorType colorType, PieceType pieceType, sf::Vector2f location);

	void findPossibleMoves(ChessBoard& board) override;
	void findIfPinned(ChessBoard& board, int i, int j) override;
};
