#include "enemy.h"
#include <QPixmap>
#include <QDebug>


Enemy::Enemy(EnemyType type, b2World* world, const b2Vec2& position, QObject* parent)
        : GameItem(world),object(parent), enemyType(type), health(100), baseDamage(10)
{
    createEnemyBody(position);
    loadEnemyImage();

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Enemy::onTimerTimeout);
    updateTimer->start(16); // Update every 16 milliseconds
}

Enemy::~Enemy()
{
    world->DestroyBody(gBody);
}

void Enemy::createEnemyBody(const b2Vec2& position)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);

    gBody = world->CreateBody(&bodyDef);

    b2CircleShape enemyShape;
    enemyShape.m_radius = 1.0f; // Adjust the radius as needed

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &enemyShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    gBody->CreateFixture(&fixtureDef);
    gBody->SetUserData(this); // Set user data to access the enemy in collision callbacks
}

void Enemy::loadEnemyImage()
{
    // Load enemy image based on enemyType
    // You might want to use QPixmap or other methods
    // Replace the placeholder code with your actual image loading logic
    QString imagePath;

    switch (enemyType) {
        case BasicEnemy:
            imagePath = ":/images/basic_enemy.png";
            break;
            // Add cases for other enemy types

        default:
            imagePath = ":/images/default_enemy.png";
            break;
    }

    QPixmap pixmap(imagePath);
    // Use the pixmap as needed in your game
    qDebug() << "Enemy image loaded: " << imagePath;
}

void Enemy::setPosition(const b2Vec2& position)
{
    gBody->SetTransform(position, gBody->GetAngle());
}

b2Vec2 Enemy::getPosition() const
{
    return gBody->GetPosition();
}

void Enemy::setHealth(int h)
{
    health = h;
    if (health <= 0) {
        // Enemy destroyed
        emit enemyDestroyed();
    }
}

int Enemy::getHealth() const
{
    return health;
}

void Enemy::setBaseDamage(int damage)
{
    baseDamage = damage;
}

int Enemy::getBaseDamage() const
{
    return baseDamage;
}

void Enemy::setVelocity(const b2Vec2& velocity)
{
    gBody->SetLinearVelocity(velocity);
}

b2Vec2 Enemy::getVelocity() const
{
    return gBody->GetLinearVelocity();
}

void Enemy::setAngularVelocity(float angularVelocity)
{
    gBody->SetAngularVelocity(angularVelocity);
}

float Enemy::getAngularVelocity() const
{
    return gBody->GetAngularVelocity();
}

void Enemy::update()
{
    // Implement your update logic here
    // For example, you can move the enemy, check for collisions, etc.
}

void Enemy::onTimerTimeout()
{
    // Timer-based updates
    update();
}

void Enemy::handleCollision()
{
    // Implement your collision handling logic here
    // For example, reduce health on collision with a player or projectile
    qDebug() << "Enemy collided!";
}

void Enemy::applyDamage(int damage)
{
    // Apply damage to the enemy
    setHealth(health - damage);
}

