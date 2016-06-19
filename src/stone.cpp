#include "stone.h"

Stone::Stone(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)

{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = STONE_DENSITY;
    fixturedef.friction = STONE_FRICTION;
    fixturedef.restitution = STONE_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);


    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    scene->addItem(&g_pixmap);

}
