#ifndef BIRD3_H
#define BIRD3_H


#include "bird.h"


class Bird3 : public Bird
{
public:
    Bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    static bool putegg;
    static bool put;
    static bool deletegg;

    virtual void ability();

};

#endif // BIRD3_H
