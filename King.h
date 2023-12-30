#pragma once

#include "Piece.h"
#include "ChessBoard.h"
  
class ChessBoard;

class King : public Piece {
public:

	King(ColorType colorType, PieceType pieceType, sf::Vector2f location);

	bool isThreatFromU = false;
	bool isThreatFromD = false;
	bool isThreatFromLU = false;
	bool isThreatFromLD = false;
	bool isThreatFromRU = false;
	bool isThreatFromRD = false;
	bool isThreatFromL = false;
	bool isThreatFromR = false;
	
	int howManyMovesLeft = 1;

	void findPossibleMoves(ChessBoard &board) override;

	
	bool isPieceThreatened(ChessBoard& board, int i, int j);
	bool canRookToShort(ChessBoard& board);
	bool canRookToLong(ChessBoard& board);
	bool isKingThreatened(ChessBoard& board);
	void protectTheKing(ChessBoard& board);
	bool vectorHasElement(std::vector<sf::Vector2i>, sf::Vector2i);
	void resetBooleans();
};
