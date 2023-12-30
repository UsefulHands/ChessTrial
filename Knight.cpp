#include "Knight.h"
#include <iostream>

Knight::Knight(ColorType colorType, PieceType pieceType, sf::Vector2f location) : Piece(colorType , pieceType, location){
}

void Knight::findPossibleMoves(ChessBoard& board){	

	int i = location.x;
	int j = location.y;

	possibleMoves.clear();
	
	if (i - 2 > -1 && j - 1 > -1 && (board.boardWithPieces[i - 2][j - 1] == nullptr || board.boardWithPieces[i - 2][j - 1]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i - 2, j - 1));
	}
		
	if (i - 2 > -1 && j + 1 < 8 && (board.boardWithPieces[i - 2][j + 1] == nullptr || board.boardWithPieces[i - 2][j + 1]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i - 2, j + 1));
	}
		
	if (i - 1 > -1 && j - 2 > -1 && (board.boardWithPieces[i - 1][j - 2] == nullptr || board.boardWithPieces[i - 1][j - 2]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i - 1, j - 2));
	}
		
	if (i - 1 > -1 && j + 2 < 8 && (board.boardWithPieces[i - 1][j + 2] == nullptr || board.boardWithPieces[i - 1][j + 2]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i - 1, j + 2));
	}
		
	if (i + 2 < 8 && j - 1 > -1 && (board.boardWithPieces[i + 2][j - 1] == nullptr || board.boardWithPieces[i + 2][j - 1]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i + 2, j - 1));
	}

	if (i + 2 < 8 && j + 1 < 8 && (board.boardWithPieces[i + 2][j + 1] == nullptr || board.boardWithPieces[i + 2][j + 1]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i + 2, j + 1));
	}
		
	if (i + 1 < 8 && j - 2 > -1 && (board.boardWithPieces[i + 1][j - 2] == nullptr || board.boardWithPieces[i + 1][j - 2]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i + 1, j - 2));
	}
		
	if (i + 1 < 8 && j + 2 < 8 && (board.boardWithPieces[i + 1][j + 2] == nullptr || board.boardWithPieces[i + 1][j + 2]->colorType != colorType)) {
		possibleMoves.push_back(sf::Vector2i(i + 1, j + 2));
	}

	findIfPinned(board, i, j);
}

void Knight::findIfPinned(ChessBoard& board, int i, int j) {
	
	//if queen or bishop pins the knight to king on diagonals knight can't move 
	if ((isPieceTypeOnLU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();
	}
	//if queen or rook pins the knight to king on rows/columns knight can't move
	if ((isPieceTypeOnL(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnL(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnU(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();
	}
}


