#ifndef TITRES_H
#define TITRES_H
#include<QPixmap>
#include<QLabel>
#include<piece.h>
#include<QList>


class titres
{
public:
    titres(bool,bool,bool,bool,bool);

    int* map;
    QPixmap getPiece(int &);
    void initialize();
    void generateDeck();

private:
    QPixmap* characters;
    int* deck;
    int deckSize = 0;
    piece* allPieces;

    bool pppSelected = false;
    bool agSelected = false;
    bool hhwSelected = false;
    bool ppSelected = false;
    bool rSelected = false;
};

#endif // TITRES_H
