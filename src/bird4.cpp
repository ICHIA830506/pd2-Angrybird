#include "bird4.h"
#include <iostream>


bool Bird4::putbird4 = false;
bool Bird4::deletebird4 = false;
bool Bird4::explore = true;


Bird4::Bird4(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene){



}


void Bird4::ability()
{
    if(explore){
        putbird4 = true;
        deletebird4 = true;
    }


    else
        putbird4 = false;

}


