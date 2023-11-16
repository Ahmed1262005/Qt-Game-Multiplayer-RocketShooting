#ifndef CHUNCK_H
#define CHUNCK_H
#include "physicitem.h"
#include "material.h"
#include "world.h"


class Chunck : public PhysicItem
{
public:
    Chunck(QPointF pos, Material *material);
    void buildItem();
    void reactionToClick();
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
    QPointF _pos;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CHUNCK_H
