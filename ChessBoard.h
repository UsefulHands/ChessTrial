#pragma once

#include "SFML/Graphics.hpp"
#include "MouseListener.h"
#include "Piece.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "King.h"
#include <typeinfo>
#include <SFML/System/Vector2.hpp>

class MouseListener;

class ChessBoard {
	public:
        ChessBoard();        
        ~ChessBoard(); 

        bool isWhiteToMove;

        MouseListener mListener;
        sf::Texture boardTexture;
        sf::Sprite boardSprite;       
        std::vector<std::vector<Piece*>> boardWithPieces;

        void initializeBoardRelativeToWhite();
        void drawPiecesOnChessBoard(sf::RenderWindow &window);
        void drawSquaresPieceCanGo(sf::RenderWindow& window, int i, int j);
};