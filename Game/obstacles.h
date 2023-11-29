#ifndef OBSTACLES_H
#define OBSTACLES_H
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include "gameitem.h"
#include <QObject>
#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QTimer>


#define OBSTACLE_DENSITY 10.0f
#define OBSTACLE_FRICTION 0.2f
#define OBSTACLE_RESTITUTION 0.5f


class Obstacles : public GameItem
{
private:

    int x;

    int y;

public:
    Obstacles(float x, float y, float width, float height, QPixmap pixmap, b2World *world);

    QPixmap get_pixmap();

    int get_x();

    int get_y();

    QSizeF get_size();

    b2Body* get_body();

};

#endif // OBSTACLES_H
