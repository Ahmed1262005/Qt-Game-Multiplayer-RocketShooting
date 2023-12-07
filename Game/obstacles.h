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

enum EnemyType {
    BasicEnemy,
    ArmoredEnemy
    // Add more enemy types as needed
};
class Obstacles : public GameItem
{
private:

    int x;

    int y;

    int health;
signals:
    //void enemyDestroyed(); // Signal emitted when the enemy is destroyed

public:
    Obstacles(float x, float y, float width, float height, QPixmap pixmap, b2World *world, qreal density, qreal friction, qreal restitution);



    QPixmap get_pixmap();

    void applyDamage(int damage);

    void setHealth(int health);

    int getHealth() const;

    int get_x();

    int get_y();

    QSizeF get_size();

    b2Body* get_body();

};

#endif // OBSTACLES_H
