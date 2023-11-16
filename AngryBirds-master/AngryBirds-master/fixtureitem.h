#ifndef FIXTUREITEM_H
#define FIXTUREITEM_H

#include <QPolygonF>
#include "physicitem.h"
#include "material.h"
#include "world.h"

class FixtureItem : public PhysicItem
{
public:
    FixtureItem(QPointF pos, Material *material);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    void advance(int phase);
    ~FixtureItem();
private:
    QPointF _pos;
};

#endif // FIXTUREITEM_H
