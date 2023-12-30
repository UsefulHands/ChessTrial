#include "King.h"
#include <iostream>

King::King(ColorType colorType, PieceType pieceType, sf::Vector2f location) : Piece(colorType, pieceType, location)  {
}

void King::findPossibleMoves(ChessBoard& board) {

	possibleMoves.clear();

	isPieceThreatened(board, location.x, location.y);

	//checks 8 border square if squares are not threatening we push to possibleMoves.
	for (int i = location.x - 1; i < location.x + 2; i++) {
		for (int j = location.y - 1; j < location.y + 2; j++) {
			if (i == location.x && j == location.y) { continue; }
			if (i > -1 && i < 8 && j > -1 && j < 8 && !isPieceThreatened(board, i, j) && board.boardWithPieces[i][j] == nullptr) {				
				possibleMoves.push_back(sf::Vector2i(i, j));
				howManyMovesLeft++;
				bool pop = false;
				if (isThreatFromD && i == location.x - 1 && j == location.y) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromU && i == location.x + 1 && j == location.y) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromL && i == location.x && j == location.y + 1) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromR && i == location.x && j == location.y - 1) {
					possibleMoves.pop_back();
					pop = true;
				}	
				if (isThreatFromLD && i == location.x - 1 && j == location.y + 1) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromLU && i == location.x + 1 && j == location.y + 1) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromRD && i == location.x - 1 && j == location.y - 1) {
					possibleMoves.pop_back();
					pop = true;
				}
				if (isThreatFromRU && i == location.x + 1 && j == location.y - 1) {
					possibleMoves.pop_back();
					pop = true;
				}
				if(pop){ howManyMovesLeft--; }
			}
			else if (i > -1 && i < 8 && j > -1 && j < 8 && !isPieceThreatened(board, i, j) && board.boardWithPieces[i][j] != nullptr && board.boardWithPieces[i][j]->colorType != colorType) {
				possibleMoves.push_back(sf::Vector2i(i, j));
				howManyMovesLeft++;
			}
		}
	}

	resetBooleans();

	//rook conditions-----------------------------------------------------
	if (canRookToShort(board) && colorType == ColorType::White) {
		possibleMoves.push_back(sf::Vector2i(location.x, location.y + 2));
		howManyMovesLeft++;
	}
	else if (canRookToShort(board) && colorType == ColorType::Black) {
		possibleMoves.push_back(sf::Vector2i(location.x, location.y + 2));
		howManyMovesLeft++;
	}
	if (canRookToLong(board) && colorType == ColorType::White) {
		possibleMoves.push_back(sf::Vector2i(location.x, location.y - 2));
		howManyMovesLeft++;
	}
	else if (canRookToLong(board) && colorType == ColorType::Black) {
		possibleMoves.push_back(sf::Vector2i(location.x, location.y - 2));
		howManyMovesLeft++;
	}
	//---------------------------------------------------------------------
}

bool King::isPieceThreatened(ChessBoard& board, int i, int j){

	//What this method does ->
	// if location i, j threatening by opponent which is has queen or bishop in diagonals or queen or rook in rows/columns or opponent's pawn/knight has a possible moves to that square return true.
	// while returning true to show us which direction we got threat 8 kind of boolean returns true. (relative to direction).
	// That 8 boolean used for protect the king method. (blocking the attacker)
	// there is no way to block pawn and knight's attack thats why we need only 8 kind of boolean.
	// resetbooleans method resets that booleans to false because we may need to use isPieceThreatened method without need that 8 booleans information. When we don't need info, after this method using resetBooleans().
	// we used result ase a return type. Because if we return directly in any condition then may other direction has a threat too but we cant learn. Better return result at last.

	bool result = false;

		if (isPieceTypeOnLU(board, i, j, PieceType::BishopE, colorType)
		||  isPieceTypeOnLU(board, i, j, PieceType::QueenE, colorType)
		||  isPieceTypeOnRD(board, i, j, PieceType::BishopE, colorType)
			|| isPieceTypeOnRD(board, i, j, PieceType::QueenE, colorType)) {

			int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

			while (D < 8 || U > -1 || R < 8 || L > -1) {	

				if (U > -1 && L > -1 && board.boardWithPieces[U][L] != nullptr && board.boardWithPieces[U][L]->colorType != colorType) {
					isThreatFromLU = true;
					result = true;					
				}
				else if (U > -1 && L > -1 && board.boardWithPieces[U][L] != nullptr && board.boardWithPieces[U][L]->colorType == colorType) {
					U = -1;
					L = -1;
				}
				if (D < 8 && R < 8 &&board.boardWithPieces[D][R] != nullptr && board.boardWithPieces[D][R]->colorType != colorType) {
					isThreatFromRD = true;
					result = true;					
				}
				else if (D < 8 && R < 8 && board.boardWithPieces[D][R] != nullptr && board.boardWithPieces[D][R]->colorType == colorType) {
					D = 8;
					R = 8;
				}
				U--;
				L--;
				D++;
				R++;
			}
		}	

		if (isPieceTypeOnRU(board, i, j, PieceType::BishopE, colorType)
			|| isPieceTypeOnRU(board, i, j, PieceType::QueenE, colorType)
			|| isPieceTypeOnLD(board, i, j, PieceType::BishopE, colorType)
			|| isPieceTypeOnLD(board, i, j, PieceType::QueenE, colorType)) {

			int D = i + 1, U = i - 1, R = j + 1, L = j - 1;

			while (D < 8 || U > -1 || R < 8 || L > -1) {

				if (U > -1 && R < 8 && board.boardWithPieces[U][R] != nullptr && board.boardWithPieces[U][R]->colorType != colorType) {		
					isThreatFromRU = true;
					result = true;				
				}
				else if (U > -1 && R < 8 && board.boardWithPieces[U][R] != nullptr && board.boardWithPieces[U][R]->colorType == colorType) {
					U = -1;
					R = 8;
				}
				if (D < 8 && L > -1 && board.boardWithPieces[D][L] != nullptr && board.boardWithPieces[D][L]->colorType != colorType) {	
					isThreatFromLD = true;
					result = true;				
				}
				else if (D < 8 && L > -1 && board.boardWithPieces[D][L] != nullptr && board.boardWithPieces[D][L]->colorType == colorType) {
					D = 8;
					L = -1;
				}
				U--;
				L--;
				D++;
				R++;
			}
		}
		
		if (isPieceTypeOnL(board, i, j, PieceType::RookE, colorType)
			|| isPieceTypeOnL(board, i, j, PieceType::QueenE, colorType)
			|| isPieceTypeOnR(board, i, j, PieceType::RookE, colorType)
			|| isPieceTypeOnR(board, i, j, PieceType::QueenE, colorType)) {

			int R = j + 1, L = j - 1;
			
			while (R < 8 || L > -1) {
				
				if (R < 8 && board.boardWithPieces[i][R] != nullptr && board.boardWithPieces[i][R]->colorType != colorType) {			
					isThreatFromR = true;
					result = true;					
				}
				else if (R < 8 && board.boardWithPieces[i][R] != nullptr && board.boardWithPieces[i][R]->colorType == colorType) {
					R = 8;
				}
				if (L > -1 && board.boardWithPieces[i][L] != nullptr && board.boardWithPieces[i][L]->colorType != colorType) {		
					isThreatFromL = true;
					result = true;					
				}
				else if (L > -1 && board.boardWithPieces[i][L] != nullptr && board.boardWithPieces[i][L]->colorType == colorType) {
					L = -1;
				}
				L--;
				R++;
			}
		}
		
		if (isPieceTypeOnU(board, i, j, PieceType::RookE, colorType)
			|| isPieceTypeOnU(board, i, j, PieceType::QueenE, colorType)
			|| isPieceTypeOnD(board, i, j, PieceType::RookE, colorType)
			|| isPieceTypeOnD(board, i, j, PieceType::QueenE, colorType)) {

			int D = i + 1, U = i - 1;

			while (D < 8 || U > -1) {
				
				if (U > -1 && board.boardWithPieces[U][j] != nullptr && board.boardWithPieces[U][j]->colorType != colorType) {			
					isThreatFromU = true;
					result = true;					
				}
				else if (U > -1 && board.boardWithPieces[U][j] != nullptr && board.boardWithPieces[U][j]->colorType == colorType) {
					U = -1;
				}
				if (D < 8 && board.boardWithPieces[D][j] != nullptr && board.boardWithPieces[D][j]->colorType != colorType) {		
					isThreatFromD = true;
					result = true;
					
				}
				else if (D < 8 && board.boardWithPieces[D][j] != nullptr && board.boardWithPieces[D][j]->colorType == colorType) {
					D = 8;
				}
				U--;
				D++;
			}
		}

		//for knight-------------------------------------------------------------------
		if (i - 2 > -1 && j - 1 > -1 && board.boardWithPieces[i - 2][j - 1] != nullptr
			&& board.boardWithPieces[i - 2][j - 1]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i - 2][j - 1]->colorType != colorType) {
			result = true;
		}
		if (i - 2 > -1 && j + 1 < 8 && board.boardWithPieces[i - 2][j + 1] != nullptr
			&& board.boardWithPieces[i - 2][j + 1]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i - 2][j + 1]->colorType != colorType) {
			result = true;			
		}
		if (i - 1 > -1 && j - 2 > -1 && board.boardWithPieces[i - 1][j - 2] != nullptr
			&& board.boardWithPieces[i - 1][j - 2]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i - 1][j - 2]->colorType != colorType) {
			result = true;			
		}
		if (i - 1 > -1 && j + 2 < 8 && board.boardWithPieces[i - 1][j + 2] != nullptr
			&& board.boardWithPieces[i - 1][j + 2]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i - 1][j + 2]->colorType != colorType) {
			result = true;
		}
		if (i + 2 < 8 && j - 1 > -1 && board.boardWithPieces[i + 2][j - 1] != nullptr
			&& board.boardWithPieces[i + 2][j - 1]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i + 2][j - 1]->colorType != colorType) {
			result = true;			
		}
		if (i + 2 < 8 && j + 1 < 8 && board.boardWithPieces[i + 2][j + 1] != nullptr
			&& board.boardWithPieces[i + 2][j + 1]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i + 2][j + 1]->colorType != colorType) {
			result = true;			
		}
		if (i + 1 < 8 && j - 2 > -1 && board.boardWithPieces[i + 1][j - 2] != nullptr
			&& board.boardWithPieces[i + 1][j - 2]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i + 1][j - 2]->colorType != colorType) {
			result = true;			
		}
		if (i + 1 < 8 && j + 2 < 8 && board.boardWithPieces[i + 1][j + 2] != nullptr
			&& board.boardWithPieces[i + 1][j + 2]->pieceType == PieceType::KnightE
			&& board.boardWithPieces[i + 1][j + 2]->colorType != colorType) {
			result = true;			
		}
		//for knight-------------------------------------------------------------------

		//for pawn---------------------------------------------------------------------
		if (colorType == ColorType::White) {

			if (i - 1 > -1 && j - 1 > -1 && board.boardWithPieces[i - 1][j - 1] != nullptr
				&& board.boardWithPieces[i - 1][j - 1]->pieceType == PieceType::PawnE
				&& board.boardWithPieces[i - 1][j - 1]->colorType != colorType) {
				result = true;
			}
			if (i - 1 > -1 && j + 1 < 8 && board.boardWithPieces[i - 1][j + 1] != nullptr
				&& board.boardWithPieces[i - 1][j + 1]->pieceType == PieceType::PawnE
				&& board.boardWithPieces[i - 1][j + 1]->colorType != colorType) {
				result = true;
			}
		}
		if (colorType == ColorType::Black) {

			if (i + 1 < 8 && j - 1 > -1 && board.boardWithPieces[i + 1][j - 1] != nullptr
				&& board.boardWithPieces[i + 1][j - 1]->pieceType == PieceType::PawnE
				&& board.boardWithPieces[i + 1][j - 1]->colorType != colorType) {
				result = true;
			}
			if (i + 1 < 8 && j + 1 < 8 && board.boardWithPieces[i + 1][j + 1] != nullptr
				&& board.boardWithPieces[i + 1][j + 1]->pieceType == PieceType::PawnE
				&& board.boardWithPieces[i + 1][j + 1]->colorType != colorType) {
				result = true;
			}
		}
		//for pawn---------------------------------------------------------------------

	return result;
}

bool King::canRookToShort(ChessBoard& board) {

	//this part checks if king and rook didn't moved
	if (isMoved
		|| (location.y + 3 < 8 && dynamic_cast<Rook*>(board.boardWithPieces[location.x][location.y + 3]) != nullptr
		&& board.boardWithPieces[location.x][location.y + 3]->isMoved)) { return false; }

		int R = location.y;		

		//this part checks if squares between rook and king (included) are not threatened
		while (R < 8) {
			if (isPieceThreatened(board, location.x, R)) {
				resetBooleans();
				return false;
			}
			R++;
		}

		R = location.y + 1;
		//this part checks if between rook and king is empty
		while (R < 7) {
			if (board.boardWithPieces[location.x][R] != nullptr) {
				return false;
			}
			R++;
		}

	return true;
}

bool King::canRookToLong(ChessBoard& board) {

	if (isMoved
		|| (location.y - 4 > -1 && dynamic_cast<Rook*>(board.boardWithPieces[location.x][location.y - 4]) != nullptr
		&& board.boardWithPieces[location.x][location.y - 4]->isMoved)) {
		return false;
	}

		int L = location.y;

		while (L > -1) {
			if (isPieceThreatened(board, location.x, L)) {
				resetBooleans();
				return false;
			}
			L--;
		}

		L = location.y - 1;

		while (L > 0) {
			if (board.boardWithPieces[location.x][L] != nullptr) {
				return false;
			}
			L--;
		}

	return true;
}

bool King::isKingThreatened(ChessBoard& board){
	return isPieceThreatened(board,location.x, location.y);
}

void King::protectTheKing(ChessBoard& board){

	//notice that if threatening is knight or pawn then there is no protect procedure then we check only 8 sides.

	isPieceThreatened(board, location.x, location.y);
	//now we need 8 booleans info so we didn't used resetBooleans() method.

	for (int i = 0; i < board.boardWithPieces.size(); i++) {
		for (int j = 0; j < board.boardWithPieces[i].size(); j++) {

			if (board.boardWithPieces[i][j] != nullptr && board.boardWithPieces[i][j]->colorType == colorType && board.boardWithPieces[i][j]->pieceType != pieceType) {

				board.boardWithPieces[i][j]->findPossibleMoves(board);
				std::vector<sf::Vector2i> vector = board.boardWithPieces[i][j]->possibleMoves;
				board.boardWithPieces[i][j]->possibleMoves.clear();

				//for knight ----------------------------------------------------------------------------------------------------------------------------
				if (location.x - 2 > -1 && location.y + 1 < 8 && dynamic_cast<Knight*>(board.boardWithPieces[location.x - 2][location.y + 1]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x - 2][location.y + 1])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x - 2, location.y + 1))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x - 2, location.y + 1));
					howManyMovesLeft++;
				}
				if (location.x - 1 > -1 && location.y - 2 > -1 && dynamic_cast<Knight*>(board.boardWithPieces[location.x - 1][location.y - 2]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x - 1][location.y - 2])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x - 1, location.y - 2))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x - 1, location.y - 2));
					howManyMovesLeft++;
				}
				if (location.x - 1 > -1 && location.y + 2 < 8 && dynamic_cast<Knight*>(board.boardWithPieces[location.x - 1][location.y + 2]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x - 1][location.y + 2])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x - 1, location.y + 2))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x - 1, location.y + 2));
					howManyMovesLeft++;
				}
				if (location.x + 2 < 8 && location.y - 1 > -1 && dynamic_cast<Knight*>(board.boardWithPieces[location.x + 2][location.y - 1]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x + 2][location.y - 1])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x + 2, location.y - 1))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 2, location.y - 1));
					howManyMovesLeft++;
				}
				if (location.x + 2 < 8 && location.y + 1 < 8 && dynamic_cast<Knight*>(board.boardWithPieces[location.x + 2][location.y + 1]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x + 2][location.y + 1])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x + 2, location.y + 1))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 2, location.y + 1));
					howManyMovesLeft++;
				}
				if (location.x + 1 < 8 && location.y - 2 > -1 && dynamic_cast<Knight*>(board.boardWithPieces[location.x + 1][location.y - 2]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x + 1][location.y - 2])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x + 1, location.y - 2))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 1, location.y - 2));
					howManyMovesLeft++;
				}
				if (location.x + 1 < 8 && location.y + 2 < 8 && dynamic_cast<Knight*>(board.boardWithPieces[location.x + 1][location.y + 2]) != nullptr
					&& dynamic_cast<Knight*>(board.boardWithPieces[location.x + 1][location.y + 2])->colorType != colorType
					&& vectorHasElement(vector, sf::Vector2i(location.x + 1, location.y + 2))) {
					board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 1, location.y + 2));
					howManyMovesLeft++;
				}
				//for knight ----------------------------------------------------------------------------------------------------------------------------

				//for pawn ----------------------------------------------------------------------------------------------------------------------------
				if (colorType == ColorType::White) {

					if (location.x - 1 > -1 && location.y - 1 > -1 && board.boardWithPieces[location.x - 1][location.y - 1] != nullptr
						&& board.boardWithPieces[location.x - 1][location.y - 1]->pieceType == PieceType::PawnE
						&& board.boardWithPieces[location.x - 1][location.y - 1]->colorType != colorType
						&& vectorHasElement(vector, sf::Vector2i(location.x - 1, location.y - 1))) {
						board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x - 1, location.y - 1));
						howManyMovesLeft++;
					}
					if (location.x - 1 > -1 && location.y + 1 < 8 && board.boardWithPieces[location.x - 1][location.y + 1] != nullptr
						&& board.boardWithPieces[location.x - 1][location.y + 1]->pieceType == PieceType::PawnE
						&& board.boardWithPieces[location.x - 1][location.y + 1]->colorType != colorType
						&& vectorHasElement(vector, sf::Vector2i(location.x - 1, location.y + 1))) {
						board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x - 1, location.y + 1));
						howManyMovesLeft++;
					}
				}
				if (colorType == ColorType::Black) {

					if (location.x + 1 < 8 && location.y - 1 > -1 && board.boardWithPieces[location.x + 1][location.y - 1] != nullptr
						&& board.boardWithPieces[location.x + 1][location.y - 1]->pieceType == PieceType::PawnE
						&& board.boardWithPieces[location.x + 1][location.y - 1]->colorType != colorType
						&& vectorHasElement(vector, sf::Vector2i(location.x + 1, location.y - 1))) {
						board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 1, location.y - 1));
						howManyMovesLeft++;
					}
					if (location.x + 1 < 8 && location.y + 1 < 8 && board.boardWithPieces[location.x + 1][location.y + 1] != nullptr
						&& board.boardWithPieces[location.x + 1][location.y + 1]->pieceType == PieceType::PawnE
						&& board.boardWithPieces[location.x + 1][location.y + 1]->colorType != colorType
						&& vectorHasElement(vector, sf::Vector2i(location.x + 1, location.y + 1))) {
						board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x + 1, location.y + 1));
						howManyMovesLeft++;
					}
				}
				//for pawn ----------------------------------------------------------------------------------------------------------------------------
				if (isThreatFromLU) {

					int L = location.y - 1;
					int U = location.x - 1;

					while (L > -1 || U > -1) {

						if (L > -1 && U > -1 && board.boardWithPieces[U][L] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(U, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, L));
								howManyMovesLeft++;
							}
						}
						else if (L > -1 && U > -1 && board.boardWithPieces[U][L]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(U, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, L));
								howManyMovesLeft++;
							}						
							L = -1;
							U = -1;
						}
						L--;
						U--;
					}					
				}
				if (isThreatFromLD) {

					int L = location.y - 1;
					int D = location.x + 1;

					while (L > -1 || D < 8) {

						if (L > -1 && D < 8 && board.boardWithPieces[D][L] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(D, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, L));
								howManyMovesLeft++;
							}
						}
						else if (L > -1 && D < 8 && board.boardWithPieces[D][L]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(D, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, L));
								howManyMovesLeft++;
							}
							L = -1;
							D = 8;
						}
						L--;
						D++;
					}
				}
				if (isThreatFromRU) {

					int R = location.y + 1;
					int U = location.x - 1;

					while (R < 8 || U > -1) {

						if (R < 8 && U > -1 && board.boardWithPieces[U][R] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(U, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, R));
								howManyMovesLeft++;
							}
						}
						else if (R < 8 && U > -1 && board.boardWithPieces[U][R]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(U, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, R));
								howManyMovesLeft++;
							}
							R = 8;
							U = -1;
						}
						R++;
						U--;
					}
				}
				if (isThreatFromRD) {

					int R = location.y + 1;
					int D = location.x + 1;

					while (R < 8 || D < 8) {

						if (R < 8 && D < 8 && board.boardWithPieces[D][R] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(D, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, R));
								howManyMovesLeft++;
							}
						}
						else if (R < 8 && D < 8 && board.boardWithPieces[D][R]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(D, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, R));
								howManyMovesLeft++;
							}
							R = 8;
							D = 8;
						}
						R++;
						D++;
					}
				}
				if (isThreatFromL) {

					int L = location.y - 1;

					while (L > -1) {

						if (L > -1&& board.boardWithPieces[location.x][L] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(location.x, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x, L));
								howManyMovesLeft++;
							}
						}
						else if (L > -1 && board.boardWithPieces[location.x][L]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(location.x, L))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x, L));
								howManyMovesLeft++;
							}
							L = -1;
						}
						L--;
					}
				}
				if (isThreatFromR) {

					int R = location.y + 1;

					while (R < 8) {

						if (R < 8 && board.boardWithPieces[location.x][R] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(location.x, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x, R));
								howManyMovesLeft++;
							}
						}
						else if (R < 8 && board.boardWithPieces[location.x][R]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(location.x, R))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(location.x, R));
								howManyMovesLeft++;
							}
							R = 8;
						}
						R++;
					}
				}
				if (isThreatFromD) {

					int D = location.x + 1;

					while (D < 8) {

						if (D < 8 && board.boardWithPieces[D][location.y] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(D, location.y))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, location.y));
								howManyMovesLeft++;
							}
						}
						else if (D < 8 && board.boardWithPieces[D][location.y]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(D, location.y))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(D, location.y));
								howManyMovesLeft++;
							}
							D = 8;
						}
						D++;
					}
				}
				if (isThreatFromU) {

					int U = location.x - 1;

					while (U > -1) {

						if (U > -1 && board.boardWithPieces[U][location.y] == nullptr) {
							if (vectorHasElement(vector, sf::Vector2i(U, location.y))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, location.y));
								howManyMovesLeft++;
							}
						}
						else if (U > -1 && board.boardWithPieces[U][location.y]->colorType != colorType) {
							if (vectorHasElement(vector, sf::Vector2i(U, location.y))) {
								board.boardWithPieces[i][j]->possibleMoves.push_back(sf::Vector2i(U, location.y));
								howManyMovesLeft++;
							}
							U = -1;
						}
						U--;
					}
				}
			}

		}
	}
	resetBooleans();
}

bool King::vectorHasElement(std::vector<sf::Vector2i> vector, sf::Vector2i element){

	if (std::find(vector.begin(), vector.end(), element) != vector.end()) {
		return true;
	}
	return false;
}

void King::resetBooleans() {
	isThreatFromU = false;
	isThreatFromD = false;
	isThreatFromLU = false;
	isThreatFromLD = false;
	isThreatFromRU = false;
	isThreatFromRD = false;
	isThreatFromL = false;
	isThreatFromR = false;
}
