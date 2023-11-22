#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QVector2D>
#include <Box2D/Box2D.h>

class Rocket : public QObject
{
Q_OBJECT

public:
    enum RocketType {
        BasicRocket,
        AdvancedRocket,
        SuperAdvancedRocket
        // Add more rocket types as needed
    };

    Rocket(RocketType type, b2World* world, const b2Vec2& position);
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

signals:
    void rocketExploded();

private slots:
    void updateAnimation();

private:
    b2World* world;
    b2Body* rocketBody;
    RocketType rocketType;
    QTimer* animationTimer;
    QVector<QPixmap> explosionFrames;
    int currentFrameIndex;

    // Other attributes as needed

    void createRocketBody(const b2Vec2& position);
    void loadExplosionFrames();
    void explode();
};

#endif // ROCKET_H
