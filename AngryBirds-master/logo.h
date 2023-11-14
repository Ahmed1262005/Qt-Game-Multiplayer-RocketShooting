#ifndef LOGO_H
#define LOGO_H

#include <QGraphicsObject>

class logo : public QGraphicsObject
{
public:
    logo();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
};

#endif // LOGO_H
