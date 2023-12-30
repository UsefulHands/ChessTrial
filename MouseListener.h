#pragma once

#include "SFML/Graphics.hpp"
#include "piece.h"

class ChessBoard;

class MouseListener {
	public:
		MouseListener();

		sf::Vector2i selectedPiece;		
		void Listen(const sf::Event& e, ChessBoard& board);
		sf::Vector2i getElement(int i, int j);
		void drawSubWindow(int i, int j, ColorType type, ChessBoard& board);
};