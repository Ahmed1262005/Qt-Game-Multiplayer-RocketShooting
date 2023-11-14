#ifndef REDBIRD_H
#define REDBIRD_H

#include "physicitem.h"
#include "material.h"
#include "world.h"

class RedBird : public PhysicItem
{
public:
    RedBird(QPointF pos, Material *material);
    ~RedBird();
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

#endif // REDBIRD_H
