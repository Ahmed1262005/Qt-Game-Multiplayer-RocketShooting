#include "bomb.h"
#include "terence.h"
#include "myquerycallback.h"
#include "defs.h"
#include <QPainter>
#include <QDebug>


Bomb::Bomb(QPointF pos, Material *material)
    :_pos(pos)
{
    _material = material;
    _body = 0;
    _mode = PhysicItem::EditMoade;
    _simulated = false;
    _shooted = false;

    setTransformOriginPoint(boundingRect().center());
    setPos(_pos);

}

Bomb::~Bomb()
{
    if(_body)
        _world->DestroyBody(_body);
}

void Bomb::buildItem()
{
    int rigidWidth = boundingRect().width();
    int rigidHeight = boundingRect().height();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = -(rotation() *2*PI/360.0 );
    bodyDef.position.Set((x()+ rigidWidth/2.0)/RATIO, -(y() + rigidHeight/2.0)/RATIO);

    _body = _world->CreateBody(&bodyDef);
    b2CircleShape bomb;
    bomb.m_radius = boundingRect().width()/2.0/RATIO;

    b2FixtureDef fixture;

    fixture.shape = &bomb;
    fixture.density = _material->density;
    fixture.friction = _material->friction;
    fixture.restitution = _material->restution;

    _body->CreateFixture(&fixture);

}

void Bomb::reactionToClick()
{
    MyQueryCallBack queryCallBack;
    b2Vec2 center = _body->GetPosition();

    b2AABB aabb;

    aabb.lowerBound = center - b2Vec2(200/RATIO, 200/RATIO);
    aabb.upperBound = center + b2Vec2(200/RATIO, 200/RATIO);

    _world->QueryAABB(&queryCallBack, aabb);
    if(queryCallBack.foundBodies.isEmpty())
        qDebug() << "empty";
    for (int i = 0; i < queryCallBack.foundBodies.size(); i++)
    {
        b2Body* body = queryCallBack.foundBodies[i];
        b2Vec2 bodyCom = body->GetWorldCenter();

        if ( (bodyCom - center).Length() >= 200/RATIO )
            continue;
        if(body != this->_body)
            this->applyBlastImpulse(body, center, bodyCom, 10.0 );
    }
}



void Bomb::advance(int phase)
{
    if(!phase) return;

    b2Vec2 p = _body->GetPosition();
    _angle = _body->GetAngle();
    setPos(p.x*RATIO-boundingRect().width()/2.0, -(p.y*RATIO+boundingRect().height()/2.0));
    setRotation(-(_angle * 360.0) / (2 * PI));
}

void Bomb::applyBlastImpulse(b2Body *body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
{
    b2Vec2 blastDir = applyPoint-blastCenter;
    float distance = blastDir.Normalize();

    //    if(distance == 0)
    //        return;
    float invDistance = 1/distance;
    float impluseMag = blastPower * invDistance * invDistance;
    body->ApplyLinearImpulse(b2Vec2(2000/RATIO, 1800/RATIO), applyPoint);
}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, _material->pix);
}

QRectF Bomb::boundingRect() const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());
}

void Bomb::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Bomb::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!_shooted)
    {
        _shooted = true;
        _body->ApplyLinearImpulse(b2Vec2(2000/RATIO, 1400/RATIO), _body->GetWorldCenter());
    }
}
