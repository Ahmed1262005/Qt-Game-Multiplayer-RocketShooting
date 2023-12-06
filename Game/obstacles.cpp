#include "obstacles.h"
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QPainter>


Obstacles::Obstacles(float x, float y, float width, float height, QPixmap pixmap, b2World *world, qreal density = 10.0f, qreal friction = 0.2f, qreal restitution = 0.2f) : GameItem(world)
{
    g_pixmap.setPixmap(pixmap.scaled(width,height));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width() / 2,g_pixmap.boundingRect().height() / 2);
    g_size = QSize(width, height);

    this -> x = x;

    this ->y = y;

    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    gBody = world->CreateBody(&bodydef);

    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(width/2,height/2);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = density;
    fixturedef.friction = friction;
    fixturedef.restitution = restitution;
    gBody->SetAngularDamping(3);
    gBody->CreateFixture(&fixturedef);





}

QPixmap Obstacles::get_pixmap()
{
    return g_pixmap.pixmap();
}

int Obstacles::get_x()
{
    return x*25;
}

int Obstacles::get_y()
{
    return (-y)*25;
}

QSizeF Obstacles::get_size()
{
    return g_size;
}

b2Body* Obstacles::get_body()
{
    return gBody;
}
