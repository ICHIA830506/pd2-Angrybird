#include "bird.h"
#include <QWidget>
#include "mainwindow.h"




Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2+0.2f,radius*2+0.2f);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetActive(false);

    // Bound timer

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(checkVel()));

    scene->addItem(&g_pixmap);
}



void Bird::setPos(qreal pointx,qreal pointy)
{
    g_pixmap.setPos(QPointF(pointx,pointy));

}

void Bird::launch( QPointF& vector)
{
    b2Vec2 sPos(g_pixmap.x()*g_worldsize.width()/g_windowsize.width()+g_size.width()/2,
                (-g_pixmap.y()/g_windowsize.height()+1.0f)*g_worldsize.height()-g_size.height()/2);
    g_body->SetTransform(sPos,0.0);
    g_body->SetActive(true);

    b2Vec2 forceVec(vector.x()*30,-vector.y()*30);
    b2Vec2 p = g_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
    g_body->ApplyForce(forceVec, p, true);
    g_launched = true;

}

void Bird::ability()
{
    return;
}



void Bird::checkVel()
{

    if((g_pixmap.x()>130 && g_body->GetLinearVelocity().Length()<=0.1 ) || g_pixmap.x()>1800)
    {
        delete this;

        std::cout << "Delete !" << std::endl ;


    }
}


