#ifndef BLUE_H
#define BLUE_H
#include "physicitem.h"
#include "material.h"
#include "world.h"

class QGraphicsScene;
class Blue : public PhysicItem
{
public:
    Blue(QPointF pos, Material *material);
    void buildItem();
    void setScene(QGraphicsScene *Scene);
    void reactionToClick();
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
    QPointF _pos;
    QGraphicsScene *_scene;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // BLUE_H
