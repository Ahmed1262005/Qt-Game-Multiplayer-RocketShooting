#include "logo.h"
#include <QPainter>
#include <QPropertyAnimation>

logo::logo()
{
    this->setAcceptHoverEvents(true);
}

void logo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, QPixmap(":/fixture/fixture/logo.png"));
}

QRectF logo::boundingRect() const
{
    return QRectF(0, 0, 600, 400);
}

void logo::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity");
    anim->setDuration(5000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}

