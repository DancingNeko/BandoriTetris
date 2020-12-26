#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QLabel>
#include<QPushButton>
#include"titres.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    virtual void keyPressEvent(QKeyEvent *event) override;
    QLabel trail;
    QLabel scoreBoard;

    //system
    QPixmap bg;
    QPixmap bg1;
    QPixmap bg2;
    QIcon esc;
    QPushButton ok;

    //band select
    void selectBand();
    QLabel ppp;
    QLabel ag;
    QLabel hhw;
    QLabel pp;
    QLabel r;
    QPushButton pppSelect;
    QPushButton agSelect;
    QPushButton hhwSelect;
    QPushButton ppSelect;
    QPushButton rSelect;
    bool pppSelected = false;
    bool agSelected = false;
    bool hhwSelected = false;
    bool ppSelected = false;
    bool rSelected = false;
    bool pieceAdded = true;
    bool selectingBand = false;

    //status
    long long timeElapsed = 0;
    bool keyPressed = false;//if it's first time of key press
    bool bandSelected = false;
    bool start = false;//if all settings finished and game starts
    int pieceCount = 0;
    int bottomY = 7;
    int* map = NULL;
    int speed = 1;
    double increment = 0.05;

    class dropInfo{
    public:
        dropInfo(int i, int bottomY, int originalY) {pieceIndex = i; pieceBottomY = bottomY; originY = originalY;}
        int pieceIndex;
        int pieceBottomY;
        int originY;
    };

    void startGame();
    titres *game = NULL;
    QList<Piece*> allPieces;//store all the pieces' info.
    void recordPuzzle();//record puzzle when it reached bottom
    int checkBottom(int dir,int X);//check bottomY and update, X: column
    bool checkClear();//check if any band have more than 5 members connected
    bool checkDrop();
    int* changes = NULL;
    int* translateToBand(int*);//translate all the data from member ID to band ID
    void searchConnectedBlocks(int& connectedNum, int pos,int*input, int band);
    int checkCave(int moveDir);//check if moveable, move if possible, then return bottomY
    int updatePieceY();
    void dropAnimation();
    int dropY = 0;
    QList<dropInfo*> dropIndex;

    //set piece
    bool addPiece();
    QLabel count;
    QTimer drop;



private slots:
     void onDropStarts();
     void onTimeout();
     void on_escape_clicked();
     void on_pppSelect_clicked();
     void on_agSelect_clicked();
     void on_hhwSelect_clicked();
     void on_ppSelect_clicked();
     void on_rSelect_clicked();
     void on_ok_clicked();

};
#endif // MAINWINDOW_H
