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

#define OBSTACLE_DENSITY 0.1f
#define OBSTACLE_FRICTION 0.1f
#define OBSTACLE_RESTITUTION 50.0f

// Enum to represent different types of enemies
enum EnemyType {
    BasicEnemy,
    ArmoredEnemy
};

class Obstacles : public GameItem {
private:
    int x;      // X-coordinate of the obstacle
    int y;      // Y-coordinate of the obstacle
    int health; // Health of the obstacle

public:
    // Constructor for Obstacles class
    Obstacles(float x, float y, float width, float height, QPixmap pixmap, b2World *world, qreal density, qreal friction, qreal restitution);

    // Get the QPixmap of the obstacle
    QPixmap get_pixmap();

    // Apply damage to the obstacle
    void applyDamage(int damage);

    // Set the health of the obstacle
    void setHealth(int health);

    // Get the health of the obstacle
    int getHealth() const;

    // Get the X-coordinate of the obstacle
    int get_x();

    // Get the Y-coordinate of the obstacle
    int get_y();

    // Get the size of the obstacle
    QSizeF get_size();

    // Get the Box2D body of the obstacle
    b2Body* get_body();
};

#endif // OBSTACLES_H
