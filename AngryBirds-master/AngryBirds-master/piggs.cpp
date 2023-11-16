#include "piggs.h"
#include "Defs.h"
#include <QPainter>
#include <QtTest/QTest>
#include <QGraphicsScene>
#include <QDebug>

Piggs::Piggs(QPointF pos, Material *material)
    : _pos(pos)
{
    _material = material;
    _mode = PhysicItem::EditMoade;
    _simulated = false;
    _body = 0;
    numContacts = 0;
    isFirstColision = true;

    setPos(_pos-boundingRect().center());
    setTransformOriginPoint(boundingRect().center());
}

Piggs::~Piggs()
{
    if(_body)
        _world->DestroyBody(_body);

}

void Piggs::buildItem()
{
    int rigidWidth = boundingRect().width();
    int rigidHeight = boundingRect().height();

    b2BodyDef bodyDef;
    bodyDef.bullet = true;
    bodyDef.position.Set((x()+rigidWidth/2.0)/RATIO, -(y()+rigidHeight/2.0)/RATIO);
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = -(rotation() * (2 * PI)) / 360.0;


    _body = _world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = (boundingRect().width())/2.0/RATIO;
    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = _material->density;
    fixture.friction = _material->friction;
    fixture.restitution = _material->restution;

    _body->SetUserData(this);
    _body->CreateFixture(&fixture);
}

QRectF Piggs::boundingRect() const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());
}

void Piggs::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->drawPixmap(0, 0, _material->pix);

    if(!isFirstColision && numContacts > 0)
    {
        _material->pix = QPixmap(":/fixture/fixture/score1.png");
        _world->DestroyBody(_body);
        this->scene()->removeItem(this);
    }
    else
        if(isFirstColision && numContacts > 2)
        {
            _material->pix = QPixmap(":/fixture/fixture/score1.png");
            _world->DestroyBody(_body);
            this->scene()->removeItem(this);

        }
}

void Piggs::startContact()
{
    numContacts++;

}

void Piggs::endContact()
{
    numContacts--;
    if(numContacts == 0)
        isFirstColision = false;

}
