#include "terence.h"
#include "defs.h"
#include <QPainter>

Terence::Terence(QPointF pos, Material *material)
    : _pos(pos)
{
    _material = material;
    _body = 0;
    _mode = PhysicItem::EditMoade;
    _simulated = false;
    _shooted = false;

    setTransformOriginPoint(boundingRect().center());
    setPos(_pos);


}

Terence::~Terence()
{
    if(_body)
        _world->DestroyBody(_body);
}

void Terence::buildItem()
{

    int rigidWidth = boundingRect().width();
    int rigidHeight = boundingRect().height();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = -(rotation() *2*PI/360.0 );
    bodyDef.position.Set((x()+ rigidWidth/2.0)/RATIO, -(y() + rigidHeight/2.0)/RATIO);

    _body = _world->CreateBody(&bodyDef);
    b2CircleShape terence;
    terence.m_radius = boundingRect().width()/2.0/RATIO;

    b2FixtureDef fixture;

    fixture.shape = &terence;
    fixture.density = _material->density;
    fixture.friction = _material->friction;
    fixture.restitution = _material->restution;

    _body->CreateFixture(&fixture);
}

void Terence::advance(int phase)
{
    if(!phase) return;

    b2Vec2 p = _body->GetPosition();
    _angle = _body->GetAngle();
    setPos(p.x*RATIO-boundingRect().width()/2.0, -(p.y*RATIO+boundingRect().height()/2.0));
    setRotation(-(_angle * 360.0) / (2 * PI));

}

void Terence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, _material->pix);
}

QRectF Terence::boundingRect() const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());
}

void Terence::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Terence::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_shooted)
    {
        _shooted = true;
        _body->ApplyLinearImpulse(b2Vec2(6000/RATIO, 5500/RATIO), _body->GetWorldCenter());
    }
}
