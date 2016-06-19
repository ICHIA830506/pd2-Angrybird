#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define WOOD_DENSITY 0.8f
#define WOOD_FRICTION 0.5f
#define WOOD_RESTITUTION 0.025f

class construction : public GameItem
{
public:
    construction(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

};

#endif // CONSTRUCTION_H
