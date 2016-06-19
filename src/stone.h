#ifndef STONE_H
#define STONE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define STONE_DENSITY 500.0f
#define STONE_FRICTION 1.0f
#define STONE_RESTITUTION 0.025f

class Stone : public GameItem
{
public:
    Stone(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};


#endif // STONE_H
