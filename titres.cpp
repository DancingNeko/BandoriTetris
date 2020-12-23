#include "titres.h"
#include<QPixmap>
#include<QLabel>
#include<QList>
#include"piece.h"
#include<cmath>

titres::titres(bool ppp,bool ag,bool hhw,bool pp,bool r)
{
    pppSelected = ppp;
    agSelected = ag;
    hhwSelected = hhw;
    ppSelected = pp;
    rSelected = r;
    map = new int[48];
    for(int i = 0; i <48; i++)
        map[i] = 0;
    initialize();
    generateDeck();
}

void titres::initialize()
{
    characters = new QPixmap [26];
    characters[0] = QPixmap(":/characterPNG(ps)/marina.png");
    characters[1] = QPixmap(":/characterPNG(ps)/kasumi.png");
    characters[2] = QPixmap(":/characterPNG(ps)/otae.png");
    characters[3] = QPixmap(":/characterPNG(ps)/rimi.png");
    characters[4] = QPixmap(":/characterPNG(ps)/saaya.png");
    characters[5] = QPixmap(":/characterPNG(ps)/arisa.png");
    characters[6] = QPixmap(":/characterPNG(ps)/ran.png");
    characters[7] = QPixmap(":/characterPNG(ps)/moca.png");
    characters[8] = QPixmap(":/characterPNG(ps)/himari.png");
    characters[9] = QPixmap(":/characterPNG(ps)/tomoe.png");
    characters[10] = QPixmap(":/characterPNG(ps)/tsugumi.png");
    characters[11] = QPixmap(":/characterPNG(ps)/kokoro.png");
    characters[12] = QPixmap(":/characterPNG(ps)/kaoru.png");
    characters[13] = QPixmap(":/characterPNG(ps)/hagumi.png");
    characters[14] = QPixmap(":/characterPNG(ps)/kanon.png");
    characters[15] = QPixmap(":/characterPNG(ps)/misaki.png");
    characters[16] = QPixmap(":/characterPNG(ps)/aya.png");
    characters[17] = QPixmap(":/characterPNG(ps)/hina.png");
    characters[18] = QPixmap(":/characterPNG(ps)/chisato.png");
    characters[19] = QPixmap(":/characterPNG(ps)/maya.png");
    characters[20] = QPixmap(":/characterPNG(ps)/eve.png");
    characters[21] = QPixmap(":/characterPNG(ps)/yukina.png");
    characters[22] = QPixmap(":/characterPNG(ps)/sayo.png");
    characters[23] = QPixmap(":/characterPNG(ps)/risa.png");
    characters[24] = QPixmap(":/characterPNG(ps)/ako.png");
    characters[25] = QPixmap(":/characterPNG(ps)/rinko.png");

    allPieces = new piece[48];
}

QPixmap titres::getPiece(int& ID)
{
    int random = (int)(rand() % (deckSize - 1)) + 1; //-1: marina
    QPixmap result(characters[deck[random]]);
    ID = random;
    return result;
}

void titres::generateDeck()
{
    int totalSelected = 0;
    if(pppSelected)
        totalSelected++;
    if(agSelected)
        totalSelected++;
    if(hhwSelected)
        totalSelected++;
    if(ppSelected)
        totalSelected++;
    if(rSelected)
        totalSelected++;
    deck = new int[totalSelected * 5 + 1]; // +1: marina
    deckSize = totalSelected * 5 + 1;
    deck[0] = 0;
    int i = 1;
    if(pppSelected)
    {
        for(int j = 1; j <= 5; j++)
        {
            deck[i] = j;
            i++;
        }
    }
    if(agSelected)
    {
        for(int j = 6; j <= 10; j++)
        {
            deck[i] = j;
            i++;
        }
    }
    if(hhwSelected)
    {
        for(int j = 11; j <= 15; j++)
        {
            deck[i] = j;
            i++;
        }
    }
    if(ppSelected)
    {
        for(int j = 16; j <= 20; j++)
        {
            deck[i] = j;
            i++;
        }
    }
    if(rSelected)
    {
        for(int j = 21; j <= 25; j++)
        {
            deck[i] = j;
            i++;
        }
    }
}
