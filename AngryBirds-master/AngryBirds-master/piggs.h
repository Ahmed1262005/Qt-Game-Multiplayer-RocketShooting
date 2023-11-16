#ifndef PIGGS_H
#define PIGGS_H

#include "physicitem.h"
#include "material.h"
#include <QGraphicsObject>
#include <Box2D/Box2D.h>
#include <QTimer>

class Piggs : public PhysicItem
{
public:
    Piggs(QPointF pos, Material *material);
    void buildItem();
	QRectF boundingRect()const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    void startContact();
    void endContact();
	~Piggs();

private:
	QPointF _pos;
    int numContacts;
    bool isFirstColision;
    QTimer timer;
};

#endif // PIGGS_H
