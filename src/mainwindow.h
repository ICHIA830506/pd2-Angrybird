#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include <bird3.h>
#include <bird4.h>
#include "egg.h"
#include "bird4_copy.h"
#include <pig.h>
#include <slingshot.h>
#include <construction.h>
#include <stone.h>
#include "score.h"
#include "counter.h"
#include "Dialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public b2ContactListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);



    QRectF boundingRect() const;

    static bool isFire;

    // b2ContactListener interface
    void BeginContact(b2Contact *contact);

    void gameOver();

    static bool rePlay;


signals:
    // Signal for closing the game
    void quitGame();
    void moveRight();



private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void OPENSLOT();


    void newBird();
    void deleteEgg();
    void deleteBird4();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;

    QPointF g_pressPos;
    bool isReady;

    //------------------
    Bird *birdie;
    //Bird2 *birdie;
    //Bird3 *birdie;
    egg *egge;
    bird4_copy *birdie4_1;
    bird4_copy *birdie4_2;
    bird4_copy *birdie4_3;
    //-------------------


    Pig *pigie;
    Slingshot *slingShot;

    construction *wood1;
    construction *wood2;
    construction *wood3;
    construction *wood4;
    Stone *stone1;
    Stone *stone2;
    Stone *stone3;

    Score * score;
    Counter * counter;

    Dialog * gameOverWindow;

};

#endif // MAINWINDOW_H
