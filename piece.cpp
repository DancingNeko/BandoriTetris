#include "piece.h"
#include<QLabel>

Piece::Piece(QPixmap input,int x,int y,int ID)
{
    characterID = ID;
    imageMap = input;
    image.setPixmap(imageMap);
    move(x,y);
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
    image.setGeometry(x,y,350,350);
}

void Piece::rotate()
{
    if(dir != 3)
        dir++;
    else
        dir = 0;
    QTransform rotate;
    rotate.rotate(dir*90);
    image.setPixmap(imageMap.transformed(rotate));
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

void Piece::updatePos(int yPos)
{
    image.setGeometry(700 + 133 * (X - 2), yPos,350,350);
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
