#include "blocks.h"
#include "defs.h"
#include <QPainter>
#include <QDebug>

Blocks::Blocks(QPointF pos, Material *material)
    : _pos(pos)
{
    _material = material;
    _mode = PhysicItem::EditMoade;
    _body = 0;
    _simulated = false;

    setPos(_pos);
    setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    setTransformOriginPoint(boundingRect().center());
}

void Blocks::buildItem()
{
    int rigidWidth = boundingRect().width();
    int rigidHeight = boundingRect().height();

    b2BodyDef bodyDef;

    if(_material->name == "strip" || _material->name == "wood table"
            || _material->name == "wood hbox" || _material->name == "ice hbox"
            || _material->name == "stone hbox" || _material->name == "wood box"
            || _material->name == "stone box" || _material->name == "ice box"
            || _material->name == "wood vbox" || _material->name == "ice vbox"
            || _material->name == "stone vbox" || _material->name == "melon")
    {
        bodyDef.position.Set((x()+rigidWidth/2.0)/RATIO, -(y()+rigidHeight/2.0)/RATIO);
        _shape.SetAsBox(boundingRect().width()/2.0/RATIO, boundingRect().height()/2.0/RATIO);
        _fixture.shape = &_shape;
    }

    if(_material->name == "wood triangle")
    {
        bodyDef.position.Set((x())/RATIO, -(y())/RATIO);

        this->setTransformOriginPoint(boundingRect().topLeft().x(), boundingRect().topLeft().y());

        b2Vec2 vertices[3];
        vertices[0].Set(float(boundingRect().topLeft().x()/RATIO), -float(boundingRect().topLeft().y()/RATIO));
        vertices[1].Set(float(boundingRect().bottomLeft().x()/RATIO), -float(boundingRect().bottomLeft().y()/RATIO));
        vertices[2].Set(float(boundingRect().bottomRight().x()/RATIO), -float(boundingRect().bottomRight().y()/RATIO));

        _shape.Set(vertices, 3);
        _fixture.shape = &_shape;
    }

    if(_material->name == "wood triangle_1" || _material->name == "ice triangle" || _material->name == "stone triangle")
    {
        bodyDef.position.Set((x())/RATIO, -(y())/RATIO);

        this->setTransformOriginPoint(boundingRect().topLeft().x(), boundingRect().topLeft().y());

        QPointF top = QPointF(rigidWidth/2.0, 0.0);

        b2Vec2 vertices[3];
        vertices[0].Set(float(top.x()/RATIO), -float(top.y()/RATIO));
        vertices[1].Set(float(boundingRect().bottomLeft().x()/RATIO), -float(boundingRect().bottomLeft().y()/RATIO));
        vertices[2].Set(float(boundingRect().bottomRight().x()/RATIO), -float(boundingRect().bottomRight().y()/RATIO));

        _shape.Set(vertices, 3);
        _fixture.shape = &_shape;

    }

    bodyDef.angle = -(rotation()* 2*PI/360.0);

    if(_material->name == "strip")
        bodyDef.type = b2_staticBody;
    else
        bodyDef.type = b2_dynamicBody;

    _body = _world->CreateBody(&bodyDef);

    _fixture.density = _material->density;
    _fixture.friction = _material->friction;
    _fixture.restitution = _material->restution;

    _body->CreateFixture(&_fixture);

}

void Blocks::updateShape()
{

}

void Blocks::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, _material->pix);
}

QRectF Blocks::boundingRect() const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());

}

Blocks::~Blocks()
{
    if(_body)
        _world->DestroyBody(_body);
}
