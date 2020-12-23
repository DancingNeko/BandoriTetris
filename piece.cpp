#include "piece.h"
#include<QLabel>

Piece::Piece(QPixmap input,int x,int y,int ID)
{
    characterID = ID;
    imageMap = input;
    image.setPixmap(imageMap);
    move(x,y);
    X=x;
    Y=y;
    image.show();
    image.raise();
}

Piece::Piece()
{
}

Piece::Piece(const Piece& copy)
{
    characterID = copy.characterID; //-1: blank
    X = copy.X;
    Y = copy.Y;
    dir = copy.dir;
    imageMap = copy.imageMap;
    image.setPixmap(imageMap);
}

void Piece::move(int x, int y)
{
    image.setGeometry(x,y,200,350);
}

void Piece::rotate()
{
    QTransform rotate;
    rotate.rotate(90);
    image.setPixmap(imageMap.transformed(rotate));
    if(dir != 3)
        dir++;
    else
        dir = 0;
}

void Piece::setpiece(QPixmap input,int x,int y, int ID)
{
    characterID = ID;
    imageMap = input;
    image.setPixmap(imageMap);
    move(x,y);
    image.show();
}

void Piece::clearPiece()
{
    image.hide();
}

const Piece &Piece::operator =(const Piece &rhs)
{
    if(&rhs == this)
        return *this;
    characterID = rhs.characterID; //-1: blank
    X = rhs.X;
    Y = rhs.Y;
    dir = rhs.dir;
    imageMap = rhs.imageMap;
    image.setPixmap(imageMap);
    return *this;
}
