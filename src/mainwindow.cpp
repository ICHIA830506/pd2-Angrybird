#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QImage>


bool MainWindow::isFire = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::rePlay = false;

void MainWindow::showEvent(QShowEvent *)
{
    isReady= 0;
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    scene->setBackgroundBrush(QBrush(QImage(":/image/sky.png").scaled(width(),height())));

    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(this);
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    //create the score
    score = new Score();
    score->setPos(0,0);
    scene->addItem(score);

    counter = new Counter();
    counter->setPos(120,0);
    scene->addItem(counter);

    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));


    slingShot = new Slingshot(3.5,4.5,0.5,1,QPixmap(":/image/SlingShot.png").scaled(height()/7.5,height()/5),world,scene);
    pigie = new Pig(24.0f,4.8f,0.35f,&timer,QPixmap(":/image/Pig.png").scaled(height()/9.0,height()/9.0),world,scene);
    stone1 = new Stone(13.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    wood1 = new construction(15.5f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    wood2 = new construction(20.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    wood3 = new construction(18.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    stone2 = new Stone(30.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    stone3 = new Stone(28.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    wood4 = new construction(26.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    itemList.push_back(wood1);


    // Create bird (You can edit here)-----------------------------------------------------------------------------------------------------
    birdie = new Bird(2.9f,8.0f,0.35f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(newBird()));

    itemList.push_back(birdie);



    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));


    timer.start(100/6);
    }



//----------------------------------------------------------------------------------------------------------------
void MainWindow::newBird()
{
    if (Counter::counter != 0)
    {
        isFire = 0;
        isReady= 0;

        int type;
        type = rand()%4;

        std::cout << type << std::endl ;
        switch (type) {
        case 0:
            birdie = new Bird(2.9f,8.0f,0.35f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
            counter->decrease();
            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(newBird()));
            break;
        case 1:
            birdie = new Bird2(2.9f,8.0f,0.35f,&timer,QPixmap(":/image/Bird_2.png").scaled(height()/9.0,height()/9.0),world,scene);
            counter->decrease();
            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(newBird()));
            break;
        case 2:
            birdie = new Bird3(2.9f,8.0f,0.35f,&timer,QPixmap(":/image/Bird_3.png").scaled(height()/9.0,height()/9.0),world,scene);

            counter->decrease();
            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(newBird()));
            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(deleteEgg()));
            Bird3::put = true;
            break;
        case 3:
            birdie = new Bird4(2.9f,8.0f,0.35f,&timer,QPixmap(":/image/Bird_4.png").scaled(height()/10.0,height()/10.0),world,scene);

            counter->decrease();

            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(newBird()));
            connect(birdie,SIGNAL(destroyed(QObject*)),this,SLOT(deleteBird4()));

            Bird4::explore = true;
            break;\
        default:
            break;
        }
    }
    if (Counter::counter == 0)
    {
        score->setFinalScore(score->getScore());
        gameOver();
    }
}

void MainWindow::deleteEgg()
{
    if (Bird3::deletegg)
        delete egge;
}

void MainWindow::deleteBird4()
{
    if(Bird4::deletebird4){
    delete birdie4_1;
    delete birdie4_2;
    delete birdie4_3;
    }
}


//-------------------------------------------------------------------------------------------------------------
QLineF generateLine(QPointF startPos,QPointF endPos)
{
    if(startPos.x() <endPos.x())
        return QLineF(startPos,endPos);
    else
        return QLineF(endPos,startPos);
}
QRectF MainWindow::boundingRect() const
{
    return QRectF(0,0,GameItem::g_windowsize.width(),GameItem::g_windowsize.height());
}
//--------------------------------------------------
void MainWindow::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()== pigie->g_body)
    {
        std::cout << "Contact !" << std::endl ;
        score->increase();
    }

}
//----------------------------------------------------
bool MainWindow::eventFilter(QObject *, QEvent *event)
{

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    QPoint pt = mouseEvent->pos();


    if(event->type() == QEvent::MouseButtonPress)
    {

        if(isFire == false && QRectF(110,320,145,360).contains(pt)){


                g_pressPos = QLineF(110,320,145,360).pointAt(0.5);
                isReady= true;
        }


        if(!isReady && isFire){
            birdie->ability();

            if(Bird3::putegg)
            {
                b2Vec2 pos_egg = birdie->g_body->GetPosition();
                egge = new egg(pos_egg.x,pos_egg.y,0.36f,&timer,QPixmap(":/image/egg.png").scaled(height()/10.0,height()/10.0),world,scene);\
                Bird3::put = false;
            }
            if(Bird4::putbird4)
            {
                b2Vec2 pos_bird4 = birdie->g_body->GetPosition();
                birdie4_1 = new bird4_copy(pos_bird4.x,pos_bird4.y,0.35f,&timer,QPixmap(":/image/Bird_4.png").scaled(height()/10.0,height()/10.0),world,scene);
                birdie4_2 = new bird4_copy(pos_bird4.x,pos_bird4.y,0.35f,&timer,QPixmap(":/image/Bird_4.png").scaled(height()/10.0,height()/10.0),world,scene);
                birdie4_3 = new bird4_copy(pos_bird4.x,pos_bird4.y,0.35f,&timer,QPixmap(":/image/Bird_4.png").scaled(height()/10.0,height()/10.0),world,scene);
                b2Vec2 forceVec1(2000,2000);
                b2Vec2 forceVec2(2000,0);
                b2Vec2 forceVec3(2000,-2000);
                b2Vec2 p1 = birdie4_1->g_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
                b2Vec2 p2 = birdie4_2->g_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
                b2Vec2 p3 = birdie4_3->g_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
                birdie4_1->g_body->ApplyForce(forceVec1, p1, true);
                birdie4_2->g_body->ApplyForce(forceVec2, p2, true);
                birdie4_2->g_body->ApplyForce(forceVec3, p3, true);
                Bird4::explore = false;
            }
        }




    }
    if(event->type() == QEvent::MouseMove)
    {
        if(isReady==true && !isFire){

                QPointF middle = QLineF(105,320,145,380).pointAt(0.5);
                QPointF current = pt;
                //std::cout << pt.y() << std::endl ;
                if(current.x() < middle.x()+60){


                QLineF lineF = generateLine(current,middle);
                if(lineF.length()>120){
                    qreal extra = lineF.length() - 120;
                    qreal angle = lineF.angleTo(QLineF(current,current+QPointF(100,0))) * 3.1415/180.0;
                    qreal nx = current.x()+extra*cos(angle);
                    qreal ny = current.y()+extra*sin(angle);
                    g_pressPos.setX(nx);
                    g_pressPos.setY(ny);
                    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
                    timer.start(10000);
                }
                else{

                    qreal nx = current.x();
                    qreal ny = current.y();
                    g_pressPos.setX(nx);
                    g_pressPos.setY(ny);
                    birdie->g_pixmap.setPos(QPointF(g_pressPos.x()-birdie->g_pixmap.boundingRect().width()/2,
                                                    g_pressPos.y()-birdie->g_pixmap.boundingRect().height()/2));

                    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
                    timer.start(10000);

            }
        }
      }



    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        isReady= false;




        QPointF curr = g_pressPos;
        QPointF vec = QLineF(110,320,145,360).pointAt(0.5)-curr;

        if (!isFire && QRectF(0,0,155,500).contains(pt))
        {
            birdie->launch(vec);
            isFire = true;
        }

        connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
        timer.start(10);



        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
    }
    return false;
}


void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{

    world->Step(1.0/60.0,6,2);

    scene->update();
}

void MainWindow::gameOver(){

    //hide();

    gameOverWindow = new Dialog(this);
    gameOverWindow->show();
    connect(gameOverWindow,SIGNAL(restartGame()),this,SLOT(OPENSLOT()));
    connect(gameOverWindow,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));


}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    this->close();
}

void MainWindow::OPENSLOT()
{
    std::cout << "OPEN Game Signal receive !" << std::endl ;
    Counter::counter = 11;
    counter->decrease();

    delete pigie;
    delete wood1;
    delete wood2;
    delete wood3;
    delete wood4;
    delete stone1;
    delete stone2;
    delete stone3;
    delete score;
    pigie = new Pig(24.0f,4.8f,0.35f,&timer,QPixmap(":/image/Pig.png").scaled(height()/9.0,height()/9.0),world,scene);
    wood1 = new construction(15.5f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    wood2 = new construction(20.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    wood3 = new construction(18.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    wood4 = new construction(26.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Wood1.png").scaled(height()/25,height()/5),world,scene);
    stone1 = new Stone(13.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    stone2 = new Stone(30.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    stone3 = new Stone(28.0f, 6.0f, 0.10f, 1.5f,&timer,QPixmap(":/image/Stone.png").scaled(height()/25,height()/5),world,scene);
    score = new Score();    score->setPos(0,0);    scene->addItem(score);

}


