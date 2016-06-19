#include "bird3.h"





bool Bird3::putegg = false;
bool Bird3::deletegg = false;
bool Bird3::put = true;

Bird3::Bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene){


}



void Bird3::ability()
{
    if(put){
        putegg = true;
        deletegg = true;

    }

    else
        putegg = false;

}
