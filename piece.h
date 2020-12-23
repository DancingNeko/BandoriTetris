#ifndef PIECE_H
#define PIECE_H

#include<QPixmap>
#include<QLabel>

class Piece
{
public:
    Piece(QPixmap,int,int,int);
    Piece();
    Piece(const Piece&);
    void move(int, int);
    void setImage(QPixmap);
    void rotate();
    void setpiece(QPixmap,int,int,int);
    void clearPiece();
    void updatePos(int);
    QLabel image;
    const Piece& operator = (const Piece& rhs);
    int X = 2;//which column, not pixel
    int Y = 7;
    int characterID = -1; //-1: blank
    int dir = 0;
private:
    QPixmap imageMap;
};

#endif // PIECE_H
