#ifndef TERENCE_H
#define TERENCE_H

#include "physicitem.h"
#include "material.h"
#include "world.h"

class Terence : public PhysicItem
{
public:
    Terence(QPointF pos, Material *material);
    ~Terence();
    void buildItem();
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
    QPointF _pos;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // TERENCE_H
