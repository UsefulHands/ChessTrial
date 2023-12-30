#include "Piece.h"
#include <iostream>
#include "ChessBoard.h"
Piece::Piece(ColorType colorType, PieceType pieceType, sf::Vector2f location) : colorType(colorType), pieceType(pieceType), location(location){

}

void Piece::findPossibleMoves(ChessBoard &board){
	//Going to override
}

void Piece::findIfPinned(ChessBoard& board, int i, int j){
	//Going to override
}

/*
* Every piece has colorType, PieceType(King, Knight), possibleMoves vector and location (as index)
* Every special piece has its special findig possible moves method.
* Every special piece has its special find If Pinned method. Because A Knight can't eat the threatening but queen etc. eat lets say.
* 
* All this isPieceTypeOn..() method is used for finding algorithm. If isPieceTypeOnL is used for a square for whites then it checks if there are any black specific typed piece threatening in Left side.
* There are 8 sides so 8 methods. Because Pawns and Knights threats differ from queen or rook or bishop. Pawn and Knight's threats checks inside King's special method.
* Be careful at which class you are using them because it acts different at different colors.
*/

// In every piece select findPossibleMoves method step in . In findPossibleMoves method current possibleMoves deleting and re - finding.
// After findPossibleMoves method checks if current piece is pinned to King. If pinned and can't eat threatening no possible moves. If pinned and can eat threatening, piece can move in that line.

// Remember that L is Left R is Right U is Up D is Down and combinations for diagonals as LU etc. Used in many places.

bool Piece::isPieceTypeOnLU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int L = j - 1;
	int U = i - 1;

	while (L > -1 && U > -1) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[U][L] != nullptr) {
				if (board.boardWithPieces[U][L]->pieceType == type && board.boardWithPieces[U][L]->colorType!= colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[U][L] != nullptr && board.boardWithPieces[U][L]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[U][L]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[U][L]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[U][L] != nullptr && board.boardWithPieces[U][L]->pieceType != type) { return false; }

		L--;
		U--;
	}
	return false;
}

bool Piece::isPieceTypeOnLD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int L = j - 1;
	int D = i + 1;

	while (L > -1 && D < 8) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[D][L] != nullptr) {
				if (board.boardWithPieces[D][L]->pieceType == type && board.boardWithPieces[D][L]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[D][L] != nullptr && board.boardWithPieces[D][L]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[D][L]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[D][L]->colorType != colorType) { return true; }

			else { return false; }
		}

		else if (board.boardWithPieces[D][L] != nullptr && board.boardWithPieces[D][L]->pieceType != type) { return false; }

		L--;
		D++;
	}
	return false;
}

bool Piece::isPieceTypeOnRU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int R = j + 1;
	int U = i - 1;

	while (R < 8 && U > -1) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[U][R] != nullptr) {
				if (board.boardWithPieces[U][R]->pieceType == type && board.boardWithPieces[U][R]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[U][R] != nullptr && board.boardWithPieces[U][R]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[U][R]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[U][R]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[U][R] != nullptr && board.boardWithPieces[U][R]->pieceType != type) { return false; }

		R++;
		U--;
	}
	return false;
}

bool Piece::isPieceTypeOnRD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int R = j + 1;
	int D = i + 1;

	while (R < 8 && D < 8) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[D][R] != nullptr) {
				if (board.boardWithPieces[D][R]->pieceType == type && board.boardWithPieces[D][R]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[D][R] != nullptr && board.boardWithPieces[D][R]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[D][R]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[D][R]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[D][R] != nullptr && board.boardWithPieces[D][R]->pieceType != type) { return false; }

		R++;
		D++;
	}
	return false;
}

bool Piece::isPieceTypeOnL(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int L = j - 1;

	while (L > -1) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[i][L] != nullptr) {
				if (board.boardWithPieces[i][L]->pieceType == type && board.boardWithPieces[i][L]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[i][L] != nullptr && board.boardWithPieces[i][L]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[i][L]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[i][L]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[i][L] != nullptr && board.boardWithPieces[i][L]->pieceType != type) { return false; }

		L--;
	}
	return false;;
}

bool Piece::isPieceTypeOnR(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int R = j + 1;

	while (R < 8) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[i][R] != nullptr) {
				if (board.boardWithPieces[i][R]->pieceType == type && board.boardWithPieces[i][R]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[i][R] != nullptr && board.boardWithPieces[i][R]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[i][R]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[i][R]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[i][R] != nullptr && board.boardWithPieces[i][R]->pieceType != type) { return false; }

		R++;
	}
	return false;
}

bool Piece::isPieceTypeOnU(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int U = i - 1;

	while (U > -1) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[U][j] != nullptr) {
				if (board.boardWithPieces[U][j]->pieceType == type && board.boardWithPieces[U][j]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[U][j] != nullptr && board.boardWithPieces[U][j]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[U][j]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[U][j]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[U][j] != nullptr && board.boardWithPieces[U][j]->pieceType != type) { return false; }

		U--;
	}
	return false;
}

bool Piece::isPieceTypeOnD(ChessBoard& board, int i, int j, PieceType type, ColorType colorType) {

	int D = i + 1;

	while (D < 8) {

		if (board.boardWithPieces[i][j] == nullptr) {
			if (board.boardWithPieces[D][j] != nullptr) {
				if (board.boardWithPieces[D][j]->pieceType == type && board.boardWithPieces[D][j]->colorType != colorType) { return true; }
				else { return false; }
			}
		}

		else if (board.boardWithPieces[D][j] != nullptr && board.boardWithPieces[D][j]->pieceType == type) {
			if (type == PieceType::KingE) {
				if (board.boardWithPieces[D][j]->colorType == colorType) { return true; }
				else { return false; }
			}
			if (board.boardWithPieces[D][j]->colorType != colorType) { return true; }
			else { return false; }
		}

		else if (board.boardWithPieces[D][j] != nullptr && board.boardWithPieces[D][j]->pieceType != type) { return false; }

		D++;
	}
	return false;
}




