#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class ChessBoard;

enum ColorType {
	White,
	Black,
};

enum PieceType {
	KnightE,
	BishopE,
	RookE,
	QueenE,
	PawnE,
	KingE
};

class Piece {
	public:
		Piece(ColorType colorType, PieceType pieceType, sf::Vector2f location);

		bool isMoved;

		ColorType colorType;
		PieceType pieceType;
		std::vector<sf::Vector2i> possibleMoves;
		sf::Vector2i location;

		virtual void findPossibleMoves(ChessBoard &board);
		virtual void findIfPinned(ChessBoard &board, int i, int j);

		bool isPieceTypeOnLU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnLD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnRU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnRD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnL(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnR(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);
		bool isPieceTypeOnD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType);

};
