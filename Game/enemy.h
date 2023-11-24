#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include "gameitem.h"
#include <Box2D/Box2D.h>

class Enemy : public GameItem
{
Q_OBJECT
public:
    enum EnemyType {
        BasicEnemy,
        ArmoredEnemy
        // Add more enemy types as needed
    };

    Enemy(EnemyType type, b2World* world, const b2Vec2& position, QObject* parent, MainWindow* W);
    ~Enemy();

    void setPosition(const b2Vec2& position);
    b2Vec2 getPosition() const;

    void setHealth(int health);
    int getHealth() const;

    void setBaseDamage(int damage);
    void applyDamage(int damage);
    int getBaseDamage() const;

    void setVelocity(const b2Vec2& velocity);
    b2Vec2 getVelocity() const;

    void setAngularVelocity(float angularVelocity);
    float getAngularVelocity() const;

    void update(); // Implement your update logic here

signals:
    void enemyDestroyed(); // Signal emitted when the enemy is destroyed

private:
    QObject object;
    EnemyType enemyType;
    int health;
    int baseDamage;
    QTimer* updateTimer;

    void createEnemyBody(const b2Vec2& position);
    void loadEnemyImage();
    void handleCollision(); // Implement your collision handling logic here

private slots:
    void onTimerTimeout();
};

#endif // ENEMY_H
