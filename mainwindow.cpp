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
    timeElapsed += (int)(1 + 1 * pieceCount);
    if(!keyPressed)//animate the label
    {
        if((timeElapsed/100)%2 == 0)
            ui->label->move(560,800+timeElapsed%100);
        else
            ui->label->move(560,900-timeElapsed%100);
    }
    if(start)
    {
        if(timeElapsed + (int)(1 + 1 * pieceCount) >= 1070) //if next frame will be over 1070
        {
            allPieces.last()->updatePos(720);
            allPieces.last()->image.show();
            addPiece();
        }
        if(pieceAdded)//reset time elapsed
        {
            timeElapsed = 0;
            pieceAdded = false;
        }
      allPieces.last()->updatePos(timeElapsed-350);

      cout<< allPieces.last()->X <<endl;
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
         if (event->key() == Qt::Key_Space)
         {
             timeElapsed = 1070;
         }
         else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
         {
             allPieces.last()->rotate();
         }
         else if(event->key() == Qt::Key_Right)
         {
             if(allPieces.last()->X < 5)
                allPieces.last()->X += 1;
             allPieces.last()->updatePos(timeElapsed-350);
         }
         else if(event->key() == Qt::Key_Left)
         {
             if(allPieces.last()->X > 0)
                allPieces.last()->X -= 1;
             allPieces.last()->updatePos(timeElapsed-350);
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

void MainWindow::addPiece()
{
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

    pieceAdded = true;
}
