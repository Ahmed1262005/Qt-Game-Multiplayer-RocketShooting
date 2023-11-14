#ifndef BLOCKS_H
#define BLOCKS_H

#include <QPolygonF>
#include "physicitem.h"
#include "material.h"
#include "world.h"

class Blocks : public PhysicItem
{
public:
    Blocks(QPointF pos, Material *material);
    void buildItem();
    void updateShape();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
    QRectF boundingRect()const;
    ~Blocks();

private:
    QRectF _boundingRect;
    QPointF _pos;
    QPolygonF _polygon;
    b2EdgeShape _ground;
    b2PolygonShape _shape;
    b2FixtureDef _fixture;

};

#endif // BLOCKS_H
