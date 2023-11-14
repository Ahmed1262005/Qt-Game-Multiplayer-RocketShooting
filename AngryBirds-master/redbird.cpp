#include "redbird.h"
#include "defs.h"
#include <QDebug>
#include <QPainter>

RedBird::RedBird(QPointF pos, Material *material)
    : _pos(pos)
{
    _mode = PhysicItem::EditMoade;
    _body = 0;
    _simulated = false;
    _shooted = false;
    _material = material;

    setTransformOriginPoint(boundingRect().center());
    setPos(_pos);

}

RedBird::~RedBird()
{
    if(_body)
        _world->DestroyBody(_body);
}

void RedBird::buildItem()
{

    int rigidWidth = boundingRect().width();
    int rigidHeight = boundingRect().height();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = -(rotation() *2*PI/360.0 );
    bodyDef.position.Set((x()+ rigidWidth/2.0)/RATIO, -(y() + rigidHeight/2.0)/RATIO);

    _body = _world->CreateBody(&bodyDef);

    b2CircleShape redbird;
    redbird.m_radius = boundingRect().width()/2.0/RATIO;

    b2FixtureDef fixture;

    fixture.shape = &redbird;
    fixture.density = _material->density;
    fixture.friction = _material->friction;
    fixture.restitution = _material->restution;

    _body->CreateFixture(&fixture);
}

void RedBird::advance(int phase)
{
    if(!phase) return;

    b2Vec2 p = _body->GetPosition();
    _angle = _body->GetAngle();
    setPos(p.x*RATIO-boundingRect().width()/2.0, -(p.y*RATIO+boundingRect().height()/2.0));
    setRotation(-(_angle * 360.0) / (2 * PI));

}

void RedBird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, _material->pix);
}

QRectF RedBird::boundingRect() const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());
}

void RedBird::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void RedBird::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_shooted )
    {
        _shooted = true;
        _body->ApplyLinearImpulse(b2Vec2(400/RATIO, 350/RATIO), _body->GetWorldCenter());
    }
}
