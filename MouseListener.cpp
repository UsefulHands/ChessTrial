#include "MouseListener.h"
#include "ChessBoard.h"
#include "Piece.h"
#include <iostream>

MouseListener::MouseListener() {}

void MouseListener::Listen(const sf::Event& event, ChessBoard& board) {

	//What this method does -> 
	/* Firstly taking the x and y coordinates. And takes the element (index inside board) in getElement() method.
	*  Then checks if selected item is not null inside board. If null then it doesn't changing the selected Piece. (Release or keep the piece as selected)
	* if selected item is not null then next mouse event takes anoter element.
	* If selected item has a such move that where did us pressed and conditions happened then putting the selected piece to the second mouse event's square.
	* When all over we assing null to selected piece to release.
	* There are few extra moves as rook and en passant we assing it inside conditions underlined down below.
	* And lastly if there are any move then we give the move to opponent.
	*/


	//mousePressed
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {

			//current selectedPiece
			int i = selectedPiece.x;
			int j = selectedPiece.y;

			//Last selected Square
			int ElementI = getElement(event.mouseButton.x, event.mouseButton.y).x;
			int ElementJ = getElement(event.mouseButton.x, event.mouseButton.y).y;

			if (board.boardWithPieces[i][j] != nullptr
				&& ((board.boardWithPieces[i][j]->colorType == ColorType::White && board.isWhiteToMove)
					|| (board.boardWithPieces[i][j]->colorType == ColorType::Black && !board.isWhiteToMove))) {

				bool isContain = false;

				for (int loop1 = 0; loop1 < board.boardWithPieces[i][j]->possibleMoves.size(); loop1++) {
					if (ElementI == board.boardWithPieces[i][j]->possibleMoves[loop1].x
						&& ElementJ == board.boardWithPieces[i][j]->possibleMoves[loop1].y) {

						bool elementIsNullptr = board.boardWithPieces[ElementI][ElementJ] == nullptr;

						board.boardWithPieces[ElementI][ElementJ] = board.boardWithPieces[selectedPiece.x][selectedPiece.y];
						board.boardWithPieces[selectedPiece.x][selectedPiece.y]->location = sf::Vector2i(ElementI, ElementJ);
						board.boardWithPieces[selectedPiece.x][selectedPiece.y]->isMoved = true;
						board.boardWithPieces[selectedPiece.x][selectedPiece.y] = nullptr;
					
						//special condition for pawn which piece to choose---------------------------------

						if (dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ]) != nullptr
							&& dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ])->colorType == ColorType::Black
							&& ElementI == 7) {
							drawSubWindow(ElementI, ElementJ, ColorType::Black, board);
						}
						else if (dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ]) != nullptr
							&& dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ])->colorType == ColorType::White
							&& ElementI == 0) {
							drawSubWindow(ElementI, ElementJ, ColorType::White, board);
						}

						//---------------------------------------------------------------------------------

						//special condition for en passant-------------------------------------------------------
						if (dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ]) != nullptr
							&& elementIsNullptr && board.boardWithPieces[ElementI][ElementJ]->colorType == ColorType::White) {
							board.boardWithPieces[ElementI + 1][ElementJ] = nullptr;
						}
						else if (dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ]) != nullptr
							&& elementIsNullptr && board.boardWithPieces[ElementI][ElementJ]->colorType == ColorType::Black) {
							board.boardWithPieces[ElementI - 1][ElementJ] = nullptr;
						}

						for (int i = 0; i < board.boardWithPieces.size(); i++) {
							for (int j = 0; j < board.boardWithPieces[i].size(); j++) {
								if (dynamic_cast<Pawn*>(board.boardWithPieces[i][j]) != nullptr
									&& dynamic_cast<Pawn*>(board.boardWithPieces[i][j])->moveNumber == 1) {
									dynamic_cast<Pawn*>(board.boardWithPieces[i][j])->moveNumber = 0;
								}
							}
						}
						if (dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ]) != nullptr
							&& abs(selectedPiece.x - ElementI) == 2) {
							dynamic_cast<Pawn*>(board.boardWithPieces[ElementI][ElementJ])->moveNumber++;
						}
						//---------------------------------------------------------------------------------

						//special conditions for short / long rooks ------------------------------------------------------------------------------
						if (abs(ElementJ - selectedPiece.y) == 2 && board.boardWithPieces[ElementI][ElementJ]->pieceType == PieceType::KingE) {
							if (ElementJ == 6) {
								board.boardWithPieces[ElementI][ElementJ - 1] = board.boardWithPieces[selectedPiece.x][selectedPiece.y + 3];
								board.boardWithPieces[ElementI][ElementJ - 1]->location = sf::Vector2i(ElementI, ElementJ - 1);
								board.boardWithPieces[ElementI][ElementJ - 1]->isMoved = true;
								board.boardWithPieces[selectedPiece.x][selectedPiece.y + 3] = nullptr;
							}
							else if (ElementJ == 2) {
								board.boardWithPieces[ElementI][ElementJ + 1] = board.boardWithPieces[selectedPiece.x][selectedPiece.y - 4];
								board.boardWithPieces[ElementI][ElementJ + 1]->location = sf::Vector2i(ElementI, ElementJ + 1);
								board.boardWithPieces[ElementI][ElementJ + 1]->isMoved = true;
								board.boardWithPieces[selectedPiece.x][selectedPiece.y - 4] = nullptr;
							}
						}
						///------------------------------------------------------------------------------------------------------------------------

						for (int i = 0; i < board.boardWithPieces.size(); i++) {
							for (int j = 0; j < board.boardWithPieces[i].size(); j++) {
								if (board.boardWithPieces[i][j] == nullptr)
									selectedPiece = sf::Vector2i(i, j); // assign selectedPiece to no piece. I thing this is so wrong but i didn't find any better solution.
								goto label;
							}
						}
					label:

						isContain = true;

						//gives move to opponent
						if (board.isWhiteToMove) {
							board.isWhiteToMove = false;
						}
						else {
							board.isWhiteToMove = true;
						}
						break; // if we selected any move then we break possible move loop
					}
				}
				// If we selected a square that holds piece and there is no such move that we pressed then it selects the new piece
				if (!isContain) {
					selectedPiece.x = getElement(event.mouseButton.x, event.mouseButton.y).x;
					selectedPiece.y = getElement(event.mouseButton.x, event.mouseButton.y).y;
				}
			}
			// If selectedPiece is empty then we get the new selectedPiece
			else {
				selectedPiece.x = getElement(event.mouseButton.x, event.mouseButton.y).x;
				selectedPiece.y = getElement(event.mouseButton.x, event.mouseButton.y).y;
			}
		}
	}
}

sf::Vector2i MouseListener::getElement(int i, int j){

	//Simply converting mouse coordinates to indexes.
	return sf::Vector2i( j / 100, i / 100);
}

void MouseListener::drawSubWindow(int i, int j, ColorType type, ChessBoard& board) {

	sf::RenderWindow window2(sf::VideoMode(400, 100), "SelectPiece");
	window2.setFramerateLimit(100);

	while (window2.isOpen())
	{

		sf::Texture boardTexture;
		sf::Texture texture1;
		sf::Texture texture2;
		sf::Texture texture3;
		sf::Texture texture4;

		if (type == ColorType::Black) {
			texture1.loadFromFile("bQ.png");
			texture2.loadFromFile("bB.png");
			texture3.loadFromFile("bN.png");
			texture4.loadFromFile("bR.png");	
			window2.setPosition(sf::Vector2i(880 + j*100, 320 + (i + 1) * 100));
		}
		else {
			texture1.loadFromFile("wQ.png");
			texture2.loadFromFile("wB.png");
			texture3.loadFromFile("wN.png");
			texture4.loadFromFile("wR.png");
		}
		window2.setPosition(sf::Vector2i(880 + j * 100, 320 - (i + 1) * 100));

		boardTexture.loadFromFile("4x1board.png");

		sf::Sprite spriteBoard(boardTexture);
		sf::Sprite sprite1(texture1);
		sf::Sprite sprite2(texture2);
		sf::Sprite sprite3(texture3);
		sf::Sprite sprite4(texture4);

		sprite1.setPosition(sf::Vector2f(0, 0));
		sprite2.setPosition(sf::Vector2f(100, 0));
		sprite3.setPosition(sf::Vector2f(200, 0));
		sprite4.setPosition(sf::Vector2f(300, 0));

		sf::Event event;

		while (window2.pollEvent(event))
		{

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left && event.mouseButton.x != 0) {

					int ElementI = event.mouseButton.y / 100;
					int ElementJ = event.mouseButton.x / 100;

					if (type == ColorType::Black) {
						if (ElementI == 0 && ElementJ == 0) {
							board.boardWithPieces[i][j] = new Queen(ColorType::Black, PieceType::QueenE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 1) {
							board.boardWithPieces[i][j] = new Bishop(ColorType::Black, PieceType::BishopE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 2) {
							board.boardWithPieces[i][j] = new Knight(ColorType::Black, PieceType::KnightE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 3) {
							board.boardWithPieces[i][j] = new Rook(ColorType::Black, PieceType::RookE, sf::Vector2f(i, j));
							window2.close();
						}
					}
					else {
						if (ElementI == 0 && ElementJ == 0) {
							board.boardWithPieces[i][j] = new Queen(ColorType::White, PieceType::QueenE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 1) {
							board.boardWithPieces[i][j] = new Bishop(ColorType::White, PieceType::BishopE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 2) {
							board.boardWithPieces[i][j] = new Knight(ColorType::White, PieceType::KnightE, sf::Vector2f(i, j));
							window2.close();
						}
						else if (ElementI == 0 && ElementJ == 3) {
							board.boardWithPieces[i][j] = new Rook(ColorType::White, PieceType::RookE, sf::Vector2f(i, j));
							window2.close();
						}
					}
				}
			}
		}
		window2.clear();
		window2.draw(spriteBoard);
		window2.draw(sprite1);
		window2.draw(sprite2);
		window2.draw(sprite3);
		window2.draw(sprite4);
		window2.display();
	}
}




