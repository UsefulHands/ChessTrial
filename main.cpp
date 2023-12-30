#include "SFML/Graphics.hpp"
#include "ChessBoard.h"
#include <iostream>

class ChessBoard;

sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title"); 
    ChessBoard chessBoard;


int main()
{
    window.setFramerateLimit(100);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            chessBoard.mListener.Listen(event,chessBoard);
        }
        window.clear(); 
        window.draw(chessBoard.boardSprite);
        chessBoard.drawPiecesOnChessBoard(window);  
        chessBoard.drawSquaresPieceCanGo(window, chessBoard.mListener.selectedPiece.x, chessBoard.mListener.selectedPiece.y);
        window.display();

    }

    return 0;
}


