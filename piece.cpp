#include "piece.h"
#include<QLabel>

piece::piece(QPixmap input,int x,int y,int ID)
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

piece::piece()
{
}

void piece::move(int x, int y)
{
    image.setGeometry(x,y,200,350);
}

void piece::rotate()
{
    QTransform rotate;
    rotate.rotate(90);
    image.setPixmap(imageMap.transformed(rotate));
    if(dir != 3)
        dir++;
    else
        dir = 0;
}

void piece::setpiece(QPixmap input,int x,int y, int ID)
{
    characterID = ID;
    imageMap = input;
    image.setPixmap(imageMap);
    move(x,y);
    image.show();
}

void piece::clearPiece()
{
    image.hide();
}
