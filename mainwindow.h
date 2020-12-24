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

    void startGame();
    titres *game = NULL;
    QList<Piece*> allPieces;//store all the pieces' info.
    void recordPuzzle();//record puzzle when it reached bottom
    int checkBottom(int*, int dir,int X);//check bottomY and update, X: column
    bool checkClear();//check if any band have more than 5 members connected
    int* changes = NULL;
    int* translateToBand(int*);//translate all the data from member ID to band ID
    void searchConnectedBlocks(int& connectedNum, int pos,int*input, int band);

    //set piece
    void addPiece();
    QLabel test1;



private slots:
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
