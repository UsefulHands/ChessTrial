#include "Pawn.h"
#include <iostream>

Pawn::Pawn(ColorType colorType, PieceType pieceType, sf::Vector2f location) : Piece(colorType, pieceType, location) {
}

void Pawn::findPossibleMoves(ChessBoard& board) {

	int i = location.x;
	int j = location.y;

	possibleMoves.clear();

	if (colorType == ColorType::Black) {
		if (i + 1 < 8 && board.boardWithPieces[i + 1][j] == nullptr)
			possibleMoves.push_back(sf::Vector2i(i + 1, j));
		if (i == 1 && board.boardWithPieces[i + 1][j] == nullptr && board.boardWithPieces[i + 2][j] == nullptr)
			possibleMoves.push_back(sf::Vector2i(i + 2, j));
		if (i + 1 < 8 && j + 1 < 8 && board.boardWithPieces[i + 1][j + 1] != nullptr && board.boardWithPieces[i + 1][j + 1]->colorType == ColorType::White)
			possibleMoves.push_back(sf::Vector2i(i + 1, j + 1));
		if (i + 1 < 8 && j - 1 > -1 && board.boardWithPieces[i + 1][j - 1] != nullptr && board.boardWithPieces[i + 1][j - 1]->colorType == ColorType::White)
			possibleMoves.push_back(sf::Vector2i(i + 1, j - 1));
		// en passant for black pawns------------------------------------------------------------------
		if (i + 1 < 8 && j + 1 < 8
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1]) != nullptr
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1])->moveNumber == 1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1])->colorType == ColorType::White) {
			possibleMoves.push_back(sf::Vector2i(i + 1, j + 1));
		}
		if (i + 1 < 8 && j - 1 > -1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1]) != nullptr
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1])->moveNumber == 1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1])->colorType == ColorType::White) {
			possibleMoves.push_back(sf::Vector2i(i + 1, j - 1));
		}
		//---------------------------------------------------------------------------------------------
	}
	else {
		if (i - 1 > -1 && board.boardWithPieces[i - 1][j] == nullptr)
			possibleMoves.push_back(sf::Vector2i(i - 1, j));
		if (i == 6 && board.boardWithPieces[i - 1][j] == nullptr && board.boardWithPieces[i - 2][j] == nullptr)
			possibleMoves.push_back(sf::Vector2i(i - 2, j));
		if (i - 1 > -1 && j - 1 > -1 && board.boardWithPieces[i - 1][j - 1] != nullptr && board.boardWithPieces[i - 1][j - 1]->colorType == ColorType::Black)
			possibleMoves.push_back(sf::Vector2i(i - 1, j - 1));
		if (i - 1 > -1 && j + 1 < 8 && board.boardWithPieces[i - 1][j + 1] != nullptr && board.boardWithPieces[i - 1][j + 1]->colorType == ColorType::Black)
			possibleMoves.push_back(sf::Vector2i(i - 1, j + 1));
		// en passant for white pawns------------------------------------------------------------------
		if (i - 1 > -1 && j + 1 < 8
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1]) != nullptr
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1])->moveNumber == 1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j + 1])->colorType ==ColorType::Black) {
			possibleMoves.push_back(sf::Vector2i(i - 1, j + 1));
		}
		if (i - 1 > -1 && j - 1 > -1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1]) != nullptr
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1])->moveNumber == 1
			&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j - 1])->colorType == ColorType::Black) {
			possibleMoves.push_back(sf::Vector2i(i - 1, j - 1));
		}
		//---------------------------------------------------------------------------------------------
	}

	findIfPinned(board, i, j);
}

void Pawn::findIfPinned(ChessBoard& board, int i, int j) {

	//if queen or bishop pins the pawn to king on diagonals pawn can eat pinner	
	if ((isPieceTypeOnLU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		if (colorType == ColorType::White) {
			if (i - 1 > -1 && j - 1 > -1 && board.boardWithPieces[i - 1][j - 1] != nullptr && board.boardWithPieces[i - 1][j - 1]->colorType == ColorType::Black) {
				possibleMoves.push_back(sf::Vector2i(i - 1, j - 1));
			}
		}
		else {
			if (i + 1 < 8 && j + 1 < 8 && board.boardWithPieces[i + 1][j + 1] != nullptr && board.boardWithPieces[i + 1][j + 1]->colorType == ColorType::White) {
				possibleMoves.push_back(sf::Vector2i(i + 1, j + 1));
			}
		}
	}
	else if ((isPieceTypeOnLD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		if (colorType == ColorType::White) {
			if (i - 1 > -1 && j + 1 < 8 && board.boardWithPieces[i - 1][j + 1] != nullptr && board.boardWithPieces[i - 1][j + 1]->colorType == ColorType::Black) {
				possibleMoves.push_back(sf::Vector2i(i - 1, j + 1));
			}
		}
		else {
			if (i + 1 < 8 && j - 1 > -1 && board.boardWithPieces[i + 1][j - 1] != nullptr && board.boardWithPieces[i + 1][j - 1]->colorType == ColorType::White) {
				possibleMoves.push_back(sf::Vector2i(i + 1, j - 1));
			}
		}
	}

	//if queen or rook pins the pawn to king on L / R pawn can't move
	if ((isPieceTypeOnL(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnL(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();
	}
	else if ((isPieceTypeOnU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnU(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		if (colorType == ColorType::White) {
			if (i - 1 > -1 && board.boardWithPieces[i - 1][j] == nullptr) {
				possibleMoves.push_back(sf::Vector2i(i - 1, j));
			}
		}
		else {
			if (i + 1 < 8 && board.boardWithPieces[i + 1][j - 1] == nullptr) {
				possibleMoves.push_back(sf::Vector2i(i + 1, j));
			}
		}
	}
}
