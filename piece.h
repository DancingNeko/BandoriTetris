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
    QLabel image;
    const Piece& operator = (const Piece& rhs);
private:
    int characterID = -1; //-1: blank
    int X = 0;
    int Y = 0;
    int dir = 0;
    QPixmap imageMap;
};

#endif // PIECE_H
