#ifndef BOMB_H
#define BOMB_H

#include "physicitem.h"
#include "material.h"
#include "world.h"

class Bomb : public PhysicItem
{
public:
    Bomb(QPointF pos, Material *material);
    ~Bomb();
    void buildItem();
    void reactionToClick();
    void advance(int phase);
    void applyBlastImpulse(b2Body *body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
    QPointF _pos;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


};

#endif // BOMB_H
