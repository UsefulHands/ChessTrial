#include "ChessBoard.h"
#include <iostream>

ChessBoard::ChessBoard() :isWhiteToMove(true){
    this->boardTexture.loadFromFile("RelativeToWhite.png");
    boardSprite = sf::Sprite(boardTexture);   
    initializeBoardRelativeToWhite();
}

ChessBoard::~ChessBoard(){
    for (int i = 0; i < boardWithPieces.size(); i++) {
        for (int j = 0; j < boardWithPieces[i].size(); j++) {
            delete boardWithPieces[i][j];
        }
    }
}

void ChessBoard::initializeBoardRelativeToWhite() {

    //What this method does ->
    //There should be a specific coordinate for every piece at the very beginning. I choose to give information with constructor.
    //Realise that there are many kind of implement at this point as ,this->boardWithPieces = {new Rook, new Knight, ...},
    //or using the for loops to give colorType and PieceType except coordinates (we can have another constructor for only coordinate info) etc.
    
    //Black pieces
    Knight* BlackKnight1 = new Knight(ColorType::Black, PieceType::KnightE, sf::Vector2f(0, 1));
    Knight* BlackKnight2 = new Knight(ColorType::Black, PieceType::KnightE, sf::Vector2f(0, 6));
    Bishop* BlackBishop1 = new Bishop(ColorType::Black, PieceType::BishopE, sf::Vector2f(0, 2));
    Bishop* BlackBishop2 = new Bishop(ColorType::Black, PieceType::BishopE, sf::Vector2f(0, 5));
    Rook* BlackRook1 = new Rook(ColorType::Black, PieceType::RookE, sf::Vector2f(0, 0));
    Rook* BlackRook2 = new Rook(ColorType::Black, PieceType::RookE, sf::Vector2f(0, 7));
    Queen* BlackQueen = new Queen(ColorType::Black, PieceType::QueenE, sf::Vector2f(0, 3));
    King* BlackKing = new King(ColorType::Black, PieceType::KingE, sf::Vector2f(0, 4));
    Pawn* BlackPawn1 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 0));
    Pawn* BlackPawn2 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 1));
    Pawn* BlackPawn3 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 2));
    Pawn* BlackPawn4 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 3));
    Pawn* BlackPawn5 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 4));
    Pawn* BlackPawn6 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 5));
    Pawn* BlackPawn7 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 6));
    Pawn* BlackPawn8 = new Pawn(ColorType::Black, PieceType::PawnE, sf::Vector2f(1, 7));

    //White pieces
    Knight* WhiteKnight1 = new Knight(ColorType::White, PieceType::KnightE, sf::Vector2f(7, 1));
    Knight* WhiteKnight2 = new Knight(ColorType::White, PieceType::KnightE, sf::Vector2f(7, 6));
    Bishop* WhiteBishop1 = new Bishop(ColorType::White, PieceType::BishopE, sf::Vector2f(7, 2));
    Bishop* WhiteBishop2 = new Bishop(ColorType::White, PieceType::BishopE, sf::Vector2f(7, 5));
    Rook* WhiteRook1 = new Rook(ColorType::White, PieceType::RookE, sf::Vector2f(7, 0));
    Rook* WhiteRook2 = new Rook(ColorType::White, PieceType::RookE, sf::Vector2f(7, 7));
    Queen* WhiteQueen = new Queen(ColorType::White, PieceType::QueenE, sf::Vector2f(7, 3));
    King* WhiteKing = new King(ColorType::White, PieceType::KingE, sf::Vector2f(7, 4));
    Pawn* WhitePawn1 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 0));
    Pawn* WhitePawn2 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 1));
    Pawn* WhitePawn3 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 2));
    Pawn* WhitePawn4 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 3));
    Pawn* WhitePawn5 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 4));
    Pawn* WhitePawn6 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 5));
    Pawn* WhitePawn7 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 6));
    Pawn* WhitePawn8 = new Pawn(ColorType::White, PieceType::PawnE, sf::Vector2f(6, 7));

    this->boardWithPieces = {
        {BlackRook1, BlackKnight1, BlackBishop1, BlackQueen, BlackKing, BlackBishop2, BlackKnight2, BlackRook2},
        {BlackPawn1, BlackPawn2, BlackPawn3, BlackPawn4, BlackPawn5, BlackPawn6, BlackPawn7, BlackPawn8},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {WhitePawn1, WhitePawn2, WhitePawn3, WhitePawn4, WhitePawn5, WhitePawn6, WhitePawn7, WhitePawn8},
        {WhiteRook1, WhiteKnight1, WhiteBishop1, WhiteQueen, WhiteKing, WhiteBishop2, WhiteKnight2, WhiteRook2},
    };
}

void ChessBoard::drawPiecesOnChessBoard(sf::RenderWindow& window){

    //What this method does ->
    //Looping through every boardElement and using its coordinate & png file to draw.

    for (int i = 0; i < boardWithPieces.size(); i++) {
        for (int j = 0; j < boardWithPieces[i].size(); j++) {

            sf::Texture texture;           
            if (dynamic_cast<Knight*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bN.png");                
            }
            else if (dynamic_cast<Bishop*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bB.png");
            }
            else if (dynamic_cast<Rook*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bR.png");
            }
            else if (dynamic_cast<Queen*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bQ.png");
            }
            else if (dynamic_cast<Pawn*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bP.png");
            }
            else if (dynamic_cast<King*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::Black) {
                texture.loadFromFile("bK.png");
            }
            else if (dynamic_cast<Knight*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wN.png");
            }
            else if (dynamic_cast<Bishop*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wB.png");
            }
            else if (dynamic_cast<Rook*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wR.png");
            }
            else if (dynamic_cast<Queen*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wQ.png");
            }
            else if (dynamic_cast<Pawn*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wP.png");
            }
            else if (dynamic_cast<King*>(boardWithPieces[i][j]) != nullptr && boardWithPieces[i][j]->colorType == ColorType::White) {
                texture.loadFromFile("wK.png");
            }
            sf::Sprite sprite(texture);
            sprite.setPosition(j * 100, i * 100);
            window.draw(sprite);
        }
    }
}

void ChessBoard::drawSquaresPieceCanGo(sf::RenderWindow& window, int i, int j) {

    //What this method does ->
    // If there are any check situation to one of the kings then we find possible moves of king.
    // We also getting the blocker piece's possible moves too to block the check.
    // If there are no check then we can continue to finding and showing pressed button's possible moves.
    // This method using in main method.

    if (boardWithPieces[i][j] == nullptr) {
        return;
    }

    bool isCheck = false;
    sf::Vector2i cKing;

    for (int i = 0; i < boardWithPieces.size(); i++) {
        for (int j = 0; j < boardWithPieces[i].size(); j++) {
            if (dynamic_cast<King*>(boardWithPieces[i][j]) != nullptr && dynamic_cast<King*>(boardWithPieces[i][j])->isKingThreatened(*this)) {
                isCheck = true;
                cKing.x = i;
                cKing.y = j;
            }
        }
    }

    if (isCheck) {
        boardWithPieces[i][j]->possibleMoves.clear();
        dynamic_cast<King*>(boardWithPieces[cKing.x][cKing.y])->howManyMovesLeft = 0;
        dynamic_cast<King*>(boardWithPieces[cKing.x][cKing.y])->findPossibleMoves(*this);
        dynamic_cast<King*>(boardWithPieces[cKing.x][cKing.y])->protectTheKing(*this);

        if (dynamic_cast<King*>(boardWithPieces[cKing.x][cKing.y])->howManyMovesLeft == 0) {
            std::cout << "check mate!";
        }

        std::vector<sf::Vector2i> vector = boardWithPieces[i][j]->possibleMoves;

        for (int k = 0; k < boardWithPieces[i][j]->possibleMoves.size(); k++) {
            sf::CircleShape shape(15);
            shape.setPosition(100 * vector[k].y + 35, 100 * vector[k].x + 35);
            shape.setFillColor(sf::Color(120, 120, 120, 100));
            window.draw(shape);
        }
        return;
    }

    if ((boardWithPieces[i][j]->colorType == ColorType::White && isWhiteToMove)
        || (boardWithPieces[i][j]->colorType == ColorType::Black && !isWhiteToMove)) {

        boardWithPieces[i][j]->findPossibleMoves(*this);
        std::vector<sf::Vector2i> vector = boardWithPieces[i][j]->possibleMoves;

        for (int k = 0; k < boardWithPieces[i][j]->possibleMoves.size(); k++) {
            sf::CircleShape shape(15);
            shape.setPosition(100 * vector[k].y + 35, 100 * vector[k].x + 35);
            shape.setFillColor(sf::Color(120, 120, 120, 100));
            window.draw(shape);
        }
    }
}



















