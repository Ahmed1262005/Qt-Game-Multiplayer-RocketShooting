#include "fixtureitem.h"
#include "defs.h"
#include <QPainter>
#include <QDebug>

FixtureItem::FixtureItem(QPointF pos, Material *material)
    : _pos(pos)
{
    _material = material;
    _mode = PhysicItem::EditMoade;
    _simulated = false;

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    setPos(_pos);


}

FixtureItem::~FixtureItem()
{
}

void FixtureItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, _material->pix);
}

QRectF FixtureItem::boundingRect()const
{
    return QRectF(0, 0, _material->pix.width(), _material->pix.height());
}

void FixtureItem::advance(int phase)
{
}
