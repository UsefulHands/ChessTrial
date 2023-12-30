#include "Queen.h"
#include <iostream>

Queen::Queen(ColorType colorType, PieceType pieceType, sf::Vector2f location) : Piece(colorType, pieceType, location) {
}

void Queen::findPossibleMoves(ChessBoard& board) {

	int i = location.x;
	int j = location.y;

	possibleMoves.clear();

	bool canGoRightDown = true;
	bool canGoRightUp = true;
	bool canGoLeftDown = true;
	bool canGoLeftUp = true;

	int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

	while (D < 8 || U > -1 || R < 8 || L > -1) { //i artsýn, k azalsýn, j artsýn, z azalsýn

		if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R] == nullptr) { // sað alt
			possibleMoves.push_back(sf::Vector2i(D, R));

		}
		else if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R]->colorType == colorType) {
			canGoRightDown = false;
		}
		else if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R]->colorType != colorType) {
			possibleMoves.push_back(sf::Vector2i(D, R));
			canGoRightDown = false;
		}

		if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L] == nullptr) { // sað üst
			possibleMoves.push_back(sf::Vector2i(D, L));
		}
		else if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L]->colorType == colorType) {
			canGoRightUp = false;
		}
		else if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L]->colorType != colorType) {
			possibleMoves.push_back(sf::Vector2i(D, L));
			canGoRightUp = false;
		}

		if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R] == nullptr) { // sol alt
			possibleMoves.push_back(sf::Vector2i(U, R));
		}
		else if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R]->colorType == colorType) {
			canGoLeftDown = false;
		}
		else if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R]->colorType != colorType) {
			possibleMoves.push_back(sf::Vector2i(U, R));
			canGoLeftDown = false;
		}

		if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L] == nullptr) { // sol üst
			possibleMoves.push_back(sf::Vector2i(U, L));
		}
		else if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L]->colorType == colorType) {
			canGoLeftUp = false;
		}
		else if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L]->colorType != colorType) {
			possibleMoves.push_back(sf::Vector2i(U, L));
			canGoLeftUp = false;
		}

		D++;
		U--;
		R++;
		L--;
	}

	D = i + 1, U = i - 1, R = j + 1, L = j - 1;

	while (D < 8 || U > -1 || R < 8 || L > -1) { //i artsýn, k azalsýn, j artsýn, z azalsýn

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

void Queen::findIfPinned(ChessBoard& board, int i, int j) {
	//if queen or bishop pinned queen , queen move inside that diagonal

	if ((isPieceTypeOnLU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLU(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

		bool canGoLeftUp = true;
		bool canGoRightDown = true;

		while (D < 8 || U > -1 || R < 8 || L > -1) {

			if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L] == nullptr) { // sol üst
				possibleMoves.push_back(sf::Vector2i(U, L));
			}
			else if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L]->colorType == colorType) {
				canGoLeftUp = false;
			}
			else if (canGoLeftUp && U > -1 && L > -1 && board.boardWithPieces[U][L]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(U, L));
				canGoLeftUp = false;
			}

			if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R] == nullptr) { // sað alt
				possibleMoves.push_back(sf::Vector2i(D, R));
			}
			else if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R]->colorType == colorType) {
				canGoRightDown = false;
			}
			else if (canGoRightDown && D < 8 && R < 8 && board.boardWithPieces[D][R]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(D, R));
				canGoRightDown = false;
			}

			U--;
			L--;
			D++;
			R++;
		}
	}
	else if ((isPieceTypeOnLD(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::QueenE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnLD(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnRU(board, i, j, PieceType::KingE, colorType))
		|| (isPieceTypeOnRU(board, i, j, PieceType::BishopE, colorType) && isPieceTypeOnLD(board, i, j, PieceType::KingE, colorType))) {

		possibleMoves.clear();

		int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

		bool canGoRightUp = true;
		bool canGoLeftDown = true;

		while (D < 8 || U > -1 || R < 8 || L > -1) {

			if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L] == nullptr) { // sað üst
				possibleMoves.push_back(sf::Vector2i(D, L));
			}
			else if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L]->colorType == colorType) {
				canGoRightUp = false;
			}
			else if (canGoRightUp && D < 8 && L > -1 && board.boardWithPieces[D][L]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(D, L));
				canGoRightUp = false;
			}

			if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R] == nullptr) { // sol alt
				possibleMoves.push_back(sf::Vector2i(U, R));
			}
			else if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R]->colorType == colorType) {
				canGoLeftDown = false;
			}
			else if (canGoLeftDown && U > -1 && R < 8 && board.boardWithPieces[U][R]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(U, R));
				canGoLeftDown = false;
			}

			U--;
			L--;
			D++;
			R++;
		}
	}

	//if queen or rook pinned queen , queen move inside that row / column.
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
}
