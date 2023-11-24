#ifndef OBSTACLES_
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
#include "mainwindow.h"

#define OBSTACLE_DENSITY 10.0f
#define OBSTACLE_FRICTION 0.2f
#define OBSTACLE_RESTITUTION 0.5f


class Obstacles : public GameItem
{
public:
    Obstacles(float x, float y, float width, float height, QTimer *timer, QPixmap pixmap, b2World *world, MainWindow*);

};

#endif // OBSTACLES_H
