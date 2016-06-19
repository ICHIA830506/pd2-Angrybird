#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);

   QGraphicsPixmapItem g_pixmap;
static QSizeF g_worldsize, g_windowsize;
b2Body *g_body;





public slots:
    void paint();
    virtual void checkVel();


protected:


    QSizeF g_size;
    b2World *g_world;


    // b2ContactListener interface

};


#endif // GAMEITEM_H
