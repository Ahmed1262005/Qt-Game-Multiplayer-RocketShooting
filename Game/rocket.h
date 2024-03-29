#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QVector2D>
#include "gameitem.h"
#include <Box2D/Box2D.h>

class Rocket : public GameItem
{
Q_OBJECT

public:
    enum RocketType {
        BasicRocket,
        AdvancedRocket,
        SuperAdvancedRocket
        // Add more rocket types as needed
    };

    Rocket(RocketType type, b2World* World, const b2Vec2& position);
    //Rocket(RocketType type, b2World* world, const b2Vec2& position);
    ~Rocket();

    void launch(const b2Vec2& velocity);

    // Setters and getters for various attributes
    void setPosition(const b2Vec2& position);
    b2Vec2 getPosition() const;

    void setVelocity(const b2Vec2& velocity);
    b2Vec2 getVelocity() const;

    void setAngularVelocity(float angularVelocity);
    float getAngularVelocity() const;

    // Other functions as needed for animation, rendering, etc.
private:
    RocketType rocketType;
    QTimer* animationTimer;


    void createRocketBody(const b2Vec2& position);

};

#endif // ROCKET_H
