#include "bird2.h"


Bird2::Bird2(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene){



}



void Bird2::ability()
{

    b2Vec2 forceVec(500,-1000);
    b2Vec2 p = g_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
    g_body->ApplyForce(forceVec, p, true);
    return;
}

