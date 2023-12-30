#include "Rook.h"
#include <iostream>

Rook::Rook(ColorType colorType, PieceType pieceType, sf::Vector2f location) : Piece(colorType, pieceType, location) {
}

void Rook::findPossibleMoves(ChessBoard& board) {

	

	int i = location.x;
	int j = location.y;

	possibleMoves.clear();

	int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

	while(D < 8 || U > -1 || R < 8 || L > -1) { 

			if (L > -1 && board.boardWithPieces[i][L] == nullptr)  // sol
				possibleMoves.push_back(sf::Vector2i(i, L));
			else if (L > -1 && board.boardWithPieces[i][L]->colorType == colorType)
				L = -1;
			else if (L > -1 && board.boardWithPieces[i][L]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(i, L));
				L = -1;
			}

			if (R < 8 && board.boardWithPieces[i][R] == nullptr)  // sað
				possibleMoves.push_back(sf::Vector2i(i, R));
			else if (R < 8 && board.boardWithPieces[i][R]->colorType == colorType)
				R = 8;
			else if (R < 8 && board.boardWithPieces[i][R]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(i, R));
				R = 8;
			}

			if (U > -1 && board.boardWithPieces[U][j] == nullptr)  //yukarý
				possibleMoves.push_back(sf::Vector2i(U, j));
			else if (U > -1 && board.boardWithPieces[U][j]->colorType == colorType)
				U = -1;
			else if (U > -1 && board.boardWithPieces[U][j]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(U, j));
				U = -1;
			}

			if (D < 8 && board.boardWithPieces[D][j] == nullptr)  // aþaðý
				possibleMoves.push_back(sf::Vector2i(D, j));
			else if (D < 8 && board.boardWithPieces[D][j]->colorType == colorType)
				D = 8;
			else if (D < 8 && board.boardWithPieces[D][j]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(D, j));
				D = 8;
			}		
		
		D++;
		U--;
		R++;
		L--;
	}
	findIfPinned(board, i, j);
}

void Rook::findIfPinned(ChessBoard& board, int i, int j){

	//if queen or rook pins the rook to king on rows/columns rook can move on that row / column
	if ((isPieceTypeOnL(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnL(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnR(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnR(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnL(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		int R = j + 1, L = j - 1;

		while (R < 8 || L > -1) {

			if (L > -1 && board.boardWithPieces[i][L] == nullptr)  // sol
				possibleMoves.push_back(sf::Vector2i(i, L));
			else if (L > -1 && board.boardWithPieces[i][L]->colorType == colorType)
				L = -1;
			else if (L > -1 && board.boardWithPieces[i][L]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(i, L));
				L = -1;
			}

			if (R < 8 && board.boardWithPieces[i][R] == nullptr)  // sað
				possibleMoves.push_back(sf::Vector2i(i, R));
			else if (R < 8 && board.boardWithPieces[i][R]->colorType == colorType)
				R = 8;
			else if (R < 8 && board.boardWithPieces[i][R]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(i, R));
				R = 8;
			}

			R++;
			L--;
		}			
	}
	else if ((isPieceTypeOnU(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::RookE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnU(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		int D = i + 1, U = i - 1;

		while (D < 8 || U > -1) {

			if (U > -1 && board.boardWithPieces[U][j] == nullptr)  //yukarý
				possibleMoves.push_back(sf::Vector2i(U, j));
			else if (U > -1 && board.boardWithPieces[U][j]->colorType == colorType)
				U = -1;
			else if (U > -1 && board.boardWithPieces[U][j]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(U, j));
				U = -1;
			}

			if (D < 8 && board.boardWithPieces[D][j] == nullptr)  // aþaðý
				possibleMoves.push_back(sf::Vector2i(D, j));
			else if (D < 8 && board.boardWithPieces[D][j]->colorType == colorType)
				D = 8;
			else if (D < 8 && board.boardWithPieces[D][j]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(D, j));
				D = 8;
			}

			D++;
			U--;
		}
	}

	//if queen or bishop pins the rook to king on diagonals rook is pinned to king	
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
}
