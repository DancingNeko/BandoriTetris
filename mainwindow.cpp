#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QTimer"
#include<QLabel>
#include<QPushButton>
#include<iostream>
#include<QKeyEvent>
#include<QList>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer.start(8);
    bg = QPixmap(":/system/bg.png");
    bg1 = QPixmap(":/system/bg1.png");
    bg2 = QPixmap(":/system/scoreBoard.png");
    QLabel *background = new QLabel(this);
    background->setGeometry(0,0,1920,1080);
    background->setPixmap(bg);
    background->move(0,0);
    trail.setParent(this);
    scoreBoard.setParent(this);
    background->show();
    ui->escape->setParent(this);
    ui->escape->setStyleSheet("QPushButton{background:transparent;}");
    ui->escape->setIcon(QIcon(":/system/esc.png"));
    ui->escape->setIconSize(QSize(150,150));
    ui->escape->raise();
    ui->escape->show();
    ui->label->setParent(this);
    ui->label->raise();
    ui->label->show();
    count.setGeometry(1500,100,500,100);
    count.setParent(this);
    count.setText("0");
    count.setFont(QFont("Segoe Print"));
    count.setStyleSheet("Font : 100pt; color : red");
    count.hide();
    setFocusPolicy(Qt::StrongFocus);
    ui->escape->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    map = new int[48];
    for(int i = 0; i < 48; i++)
        map[i] = 0;
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//system
void MainWindow::onTimeout()
{
    timeElapsed += (int)(speed + increment * pieceCount);
    if(!keyPressed)//animate the label
    {
        if((timeElapsed/100)%2 == 0)
            ui->label->move(560,800+timeElapsed%100);
        else
            ui->label->move(560,900-timeElapsed%100);
    }
    if(start)
    {
        //allPieces.last()->Y = updatePieceY();
        allPieces.last()->Y = updatePieceY();
        //cout<<timeElapsed-266<<" ";
        if(timeElapsed + (int)(speed + increment * pieceCount) >= (bottomY - 1)*133 - 50 + 266 && allPieces.last()->dir % 2 == 0) //if next frame will be over the bottom
        {
            recordPuzzle();
        }
        else if(timeElapsed + (int)(speed + increment * pieceCount) >= bottomY*133 - 110 + 266 && allPieces.last()->dir % 2 == 1)
        {
            recordPuzzle();
        }
      allPieces.last()->updateY(timeElapsed - 266);
    }

    update();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(keyPressed == false)
    {
        keyPressed = true;
        ui->label->hide();
        selectBand();
    }
    else
    {
         if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Down)
         {
             timeElapsed =100000;
         }
         else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
         {
             allPieces.last()->rotate(map);
             bottomY = checkBottom(allPieces.last()->dir,allPieces.last()->X);
         }
         else if(event->key() == Qt::Key_Right)
         {
             bottomY = checkCave(1);
         }
         else if(event->key() == Qt::Key_Left)
         {
             bottomY = checkCave(-1);
             allPieces.last()->updateY(timeElapsed-266);
         }
         return;
    }
}
void MainWindow::on_escape_clicked()
{
    QApplication::exit(0);
}

//select band
void MainWindow::selectBand()
{
    selectingBand = true;
    ppp.setPixmap(QPixmap(":/logos/ppp.png"));
    ag.setPixmap(QPixmap(":/logos/ag.png"));
    hhw.setPixmap(QPixmap(":/logos/hhw.png"));
    pp.setPixmap(QPixmap(":/logos/pp.png"));
    r.setPixmap(QPixmap(":/logos/r.png"));
    ppp.setParent(this);
    ag.setParent(this);
    hhw.setParent(this);
    pp.setParent(this);
    r.setParent(this);
    ppp.move(150,260);
    ag.move(750,260);
    hhw.move(1350,260);
    pp.move(350,560);
    r.move(1050,560);
    ppp.show();
    ag.show();
    hhw.show();
    pp.show();
    r.show();

    pppSelect.setParent(this);
    pppSelect.setGeometry(335,550,50,50);
    pppSelect.setIcon(QIcon(":/system/no.png"));
    pppSelect.setIconSize(QSize(50,50));
    pppSelect.setStyleSheet("QPushButton{background:transparent;}");
    auto res = connect(&pppSelect, SIGNAL(clicked()), this, SLOT(on_pppSelect_clicked()));
    pppSelect.show();
    pppSelect.raise();

    agSelect.setParent(this);
    agSelect.setGeometry(935,550,50,50);
    agSelect.setIcon(QIcon(":/system/no.png"));
    agSelect.setIconSize(QSize(50,50));
    agSelect.setStyleSheet("QPushButton{background:transparent;}");
    connect(&agSelect, SIGNAL(clicked()), this, SLOT(on_agSelect_clicked()));
    agSelect.show();
    agSelect.raise();

    hhwSelect.setParent(this);
    hhwSelect.setGeometry(1555,570,50,50);
    hhwSelect.setIcon(QIcon(":/system/no.png"));
    hhwSelect.setIconSize(QSize(50,50));
    hhwSelect.setStyleSheet("QPushButton{background:transparent;}");
    connect(&hhwSelect, SIGNAL(clicked()), this, SLOT(on_hhwSelect_clicked()));
    hhwSelect.show();
    hhwSelect.raise();

    ppSelect.setParent(this);
    ppSelect.setGeometry(535,880,50,50);
    ppSelect.setIcon(QIcon(":/system/no.png"));
    ppSelect.setIconSize(QSize(50,50));
    ppSelect.setStyleSheet("QPushButton{background:transparent;}");
    connect(&ppSelect, SIGNAL(clicked()), this, SLOT(on_ppSelect_clicked()));
    ppSelect.show();
    ppSelect.raise();

    rSelect.setParent(this);
    rSelect.setGeometry(1265,880,50,50);
    rSelect.setIcon(QIcon(":/system/no.png"));
    rSelect.setIconSize(QSize(50,50));
    rSelect.setStyleSheet("QPushButton{background:transparent;}");
    connect(&rSelect, SIGNAL(clicked()), this, SLOT(on_rSelect_clicked()));
    rSelect.show();
    rSelect.raise();

    ok.setParent(this);
    ok.setGeometry(1500,900,330,94);
    ok.setIcon(QIcon(":/system/confirm.png"));
    ok.setIconSize(QSize(330,94));
    ok.setStyleSheet("QPushButton{background:transparent;}");
    connect(&ok, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
    ok.show();

    ui->label_2->setParent(this);
    ui->label_2->raise();
    ui->label_2->show();


    ui->escape->raise();
}
void MainWindow::on_ok_clicked()
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
    if(totalSelected >= 2)
    {
        bandSelected = true;
        ok.hide();
        pppSelect.hide();
        agSelect.hide();
        hhwSelect.hide();
        ppSelect.hide();
        rSelect.hide();
        ppp.hide();
        ag.hide();
        hhw.hide();
        pp.hide();
        r.hide();


        //show game
        trail.setGeometry(400,0,887,1080);
        trail.setPixmap(bg1);
        trail.raise();
        trail.show();
        scoreBoard.setGeometry(1300,500,887,1080);
        scoreBoard.setPixmap(bg2);
        scoreBoard.raise();
        scoreBoard.show();
        startGame();
    }
    else
    {
        QPalette warning(Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red,Qt::red);
        ui->label_2->setPalette(warning);
        ui->label_2->setText("At least select 2 bands!");
    }
}
void MainWindow::on_pppSelect_clicked()
{
    if(!pppSelected)
    {
        pppSelect.setIcon(QIcon(":/system/yes.png"));
        pppSelected = true;
    }
    else
    {
        pppSelect.setIcon(QIcon(":/system/no.png"));
        pppSelected = false;
    }
    update();
}
void MainWindow::on_agSelect_clicked()
{
    if(!agSelected)
    {
        agSelect.setIcon(QIcon(":/system/yes.png"));
        agSelected = true;
    }
    else
    {
        agSelect.setIcon(QIcon(":/system/no.png"));
        agSelected = false;
    }
    update();
}
void MainWindow::on_hhwSelect_clicked()
{
    if(!hhwSelected)
    {
        hhwSelect.setIcon(QIcon(":/system/yes.png"));
        hhwSelected = true;
    }
    else
    {
        hhwSelect.setIcon(QIcon(":/system/no.png"));
        hhwSelected = false;
    }
    update();
}
void MainWindow::on_ppSelect_clicked()
{
    if(!ppSelected)
    {
        ppSelect.setIcon(QIcon(":/system/yes.png"));
        ppSelected = true;
    }
    else
    {
        ppSelect.setIcon(QIcon(":/system/no.png"));
        ppSelected = false;
    }
    update();
}
void MainWindow::on_rSelect_clicked()
{
    if(!rSelected)
    {
        rSelect.setIcon(QIcon(":/system/yes.png"));
        rSelected = true;
    }
    else
    {
        rSelect.setIcon(QIcon(":/system/no.png"));
        rSelected = false;
    }
    update();
}

//game
void MainWindow::startGame()
{
    game = new titres(pppSelected,agSelected,hhwSelected,ppSelected,rSelected);
    game->generateDeck();
    addPiece();
    ui->label_2->hide();
}
void MainWindow::recordPuzzle()
{
    //cout<<bottomY<<endl;
    if(allPieces.last()->dir % 2 == 0)//vertical layout
    {
        allPieces.last()->updateY((bottomY - 1)*133 - 50);
        //cout<<990 - 130 * (7 - bottomY + 2)<<endl;
        map[bottomY * 6 + allPieces.last()->X] = allPieces.last()->characterID;
        bottomY--;
        map[bottomY * 6 + allPieces.last()->X] = allPieces.last()->characterID;
        allPieces.last()->Y = bottomY;
    }
    if(allPieces.last()->dir % 2 == 1)//horizontal layout
    {
        allPieces.last()->updateY(bottomY*133 - 110);
        //cout<<960 - 133 * (7 - bottomY + 1)<<endl;
        map[bottomY * 6 + allPieces.last()->X] = allPieces.last()->characterID;
        map[bottomY * 6 + allPieces.last()->X + 1] = allPieces.last()->characterID;
        allPieces.last()->Y = bottomY;
    }
    //cout<<allPieces.at(allPieces.size() - 1)->X<<allPieces.at(allPieces.size() - 1)->Y<<allPieces.at(allPieces.size() - 1)->dir<<endl;
    if(checkClear())
    {
        bool dropped = true;
        for(int y = 0; y < 8; y++)
            for(int x = 0; x < 6; x++)
            {
                if(map[x + y * 6] == -1)
                {
                    for(int i = 0; i < allPieces.size(); i++)
                    {
                        if(allPieces.at(i) -> X == x && allPieces.at(i) -> Y == y)
                        {
                            if(allPieces.at(i)->dir%2 == 0)
                            {
                                map[x + y * 6] = 0;
                                map[x + y * 6 + 6] = 0;
                            }
                            else
                            {
                                map[x + y * 6] = 0;
                                map[x + y * 6 + 1] = 0;
                            }
                            allPieces.at(i)->image.hide();
                            allPieces.removeAt(i);
                        }
                    }
                }
            }
// for(int i = 0; i < 48; i++)
//     cout<<i<<":"<<map[i]<<" ";
// cout<<endl;
        while(dropped)
            dropped = checkDrop();
    }
    if(!addPiece())
    {
        timer.stop();
        count.setText("X");
    }
//  for(int i = 0; i < 48; i++)
//      cout<<i<<":"<<map[i]<<" ";
//  cout<<endl;
}

int MainWindow::checkBottom(int dir, int X)
{
    if(dir % 2 == 0)//vertical layout
    {
        for(int i = 0; i <= 7; i++)
        {
            //cout<<i*6 + X<<endl;
            if(map[i*6 + X] != 0)
                return (i - 1);
        }
    }
    if(dir % 2 == 1)//horizontal layout
    {
        for(int i = allPieces.last()->Y; i <= 7; i++)
        {
            if(map[i*6 + X] != 0 || map[i * 6 + X + 1])
                return i - 1;
        }
    }
    //cout<<endl;
    return 7;
}

bool MainWindow::checkClear()
{
    changes = new int[48];
    for(int i = 0; i < 48; i++)
    {
        changes[i] = map[i];
    }
    changes = translateToBand(changes);
    int band = 1;
    int maxCombo = 0;//how many members connected
    while(band <= 5)
    {
        for(int i = 0; i < 48; i++)
        {
            maxCombo = 0;
            if(changes[i] == band)
            {
                searchConnectedBlocks(maxCombo, i, changes, band);
                if(maxCombo >= 10)
                {
                       for(int k = 0; k < 48; k++)
                       {
                           if(changes[k] == -1)
                               map[k] = changes[k];
                       }
                       return true;
                }
                else
                {
                    for (int i = 0; i < 48; i++)
                        if (changes[i] == -1)
                            changes[i] = 0;
                }
            }
        }
        band++;
    }
    return false;
}

bool MainWindow::checkDrop()
{
    bool dropped = false;
    for(int i = 0; i < allPieces.count(); i++)
    {
        if(allPieces.at(i)->dir % 2 == 0)
        {
            //cout<<"id:"<<allPieces.at(i)->characterID<<" Y:"<<allPieces.at(i)->Y<<endl;
            if(allPieces.at(i)->Y == 6)
                continue;
            else
            {
                int veryBottom = allPieces.at(i)->Y + 2;
                map[allPieces.at(i)->Y*6 +allPieces.at(i)->X] = 0;
                map[allPieces.at(i)->Y*6 + allPieces.at(i)->X + 6] = 0;
                while(map[veryBottom*6 + allPieces.at(i)->X] == 0 && veryBottom < 8)
                    veryBottom++;
                veryBottom--;
                if(veryBottom != allPieces.at(i)->Y + 1)
                    dropped = true;
                map[veryBottom*6 +allPieces.at(i)->X] = allPieces.at(i)->characterID;
                map[veryBottom*6 + allPieces.at(i)->X - 6] = allPieces.at(i)->characterID;
                allPieces.at(i)->Y = veryBottom - 1;
                allPieces.at(i)->updateY((bottomY - 1)*133 - 50 + 266);
            }
        }
        if(allPieces.at(i)->dir % 2 == 1)
        {
            //cout<<"id:"<<allPieces.at(i)->characterID<<" Y:"<<allPieces.at(i)->Y<<endl;
            if(allPieces.at(i)->Y == 7)
                continue;
            else
            {
                int veryBottom = allPieces.at(i)->Y + 1;
                map[allPieces.at(i)->Y*6 +allPieces.at(i)->X] = 0;
                map[allPieces.at(i)->Y*6 + allPieces.at(i)->X + 1] = 0;
                while(map[veryBottom*6 + allPieces.at(i)->X] == 0 && map[veryBottom*6 + allPieces.at(i)->X + 1] == 0 && veryBottom < 8)
                    veryBottom++;
                veryBottom--;
                if(veryBottom != allPieces.at(i)->Y)
                    dropped = true;
                map[veryBottom*6 +allPieces.at(i)->X] = allPieces.at(i)->characterID;
                map[veryBottom*6 + allPieces.at(i)->X + 1] = allPieces.at(i)->characterID;
                allPieces.at(i)->Y = veryBottom;
                allPieces.at(i)->updateY(bottomY*133 - 110 + 266);
            }
        }
    }
    return dropped;
}

int* MainWindow::translateToBand(int* data)
{
    for(int i = 0; i < 48; i++)
    {
        if(data[i] == 0)
            continue;
        int temp = data[i];
        temp = (temp - 1) / 5 + 1;
        data[i] = temp;
    }
    return data;
}

void MainWindow::searchConnectedBlocks(int& connectedNum, int pos, int *input, int band)
{
    connectedNum++;
    input[pos] = 0;
    if(pos % 6 != 5)
    {
        if(input[pos+1] == band)
            searchConnectedBlocks(connectedNum, pos+1, input, band);
    }
    if(pos % 6 != 0)
    {
        if(input[pos-1] == band)
            searchConnectedBlocks(connectedNum, pos-1, input, band);
    }
    if(pos / 6 != 7)
    {
        if(input[pos+6] == band)
            searchConnectedBlocks(connectedNum, pos+6, input, band);
    }
    if(pos / 6 != 0)
    {
        if(input[pos-6] == band)
            searchConnectedBlocks(connectedNum, pos-6, input, band);
    }
    input[pos] = -1;
    return;
}

int MainWindow::checkCave(int moveDir)
{
    if(allPieces.last()->dir % 2 == 0)
    {
        int x = allPieces.last()->X;
        int y = allPieces.last()->Y;
        if(x+moveDir!=-1 && x+moveDir!=6 && map[x+6*y+moveDir] == 0 && map[x+6+6*y+moveDir] == 0)
        {
            allPieces.last()->X += moveDir;
            x += moveDir;
            int veryBottom = allPieces.last()->Y + 2;
            while(map[veryBottom*6 + allPieces.last()->X] == 0 && veryBottom < 8)
                veryBottom++;
            veryBottom--;
            cout<<veryBottom<<endl;
            return veryBottom;
        }
    }
    if(allPieces.last()->dir % 2 == 1)
    {
        int x = allPieces.last()->X;
        int y = allPieces.last()->Y;
        if(x+moveDir!=-1 && x+moveDir!=5 && map[x+6*y+1+moveDir] == 0 && map[x+6*y+moveDir] == 0)
        {
            allPieces.last()->X += moveDir;
            x += moveDir;
            int veryBottom = allPieces.last()->Y + 1;
            while(map[veryBottom*6 + allPieces.last()->X] == 0 && map[veryBottom*6 + allPieces.last()->X + 1] == 0 && veryBottom < 8)
                veryBottom++;
            veryBottom--;
            cout<<veryBottom;
            return veryBottom;
        }
    }
    return bottomY;
}

    int MainWindow::updatePieceY()
    {
        if(allPieces.last()->dir % 2 ==0)
        {
            int y = (timeElapsed - 266 + 150) / 133;
            return y;
        }
        if(allPieces.last()->dir % 2 ==1)
        {
            int y = (timeElapsed - 266 + 210) / 133;
            return y;
        }
    }


bool MainWindow::addPiece()
{
    if(map[2] != 0 && map[8] != 0)
        return false;
    timeElapsed = 0;
    Piece* temp = new Piece(bg,-1000,-1000,0);
    allPieces.append(temp);
    if(start == false)
        start = true;
    else
        pieceCount++;
    int id = -1;
    QPixmap tempImage = game->generateImage(id);
    allPieces.last()->image.setParent(this);
    allPieces.last()->setpiece(tempImage,700,-300,id);
    allPieces.last()->image.raise();
    allPieces.last()->image.show();
    count.setText(QString::number(pieceCount));
    count.show();
    bottomY = checkBottom(allPieces.last()->dir,allPieces.last()->X);
    return true;
}
