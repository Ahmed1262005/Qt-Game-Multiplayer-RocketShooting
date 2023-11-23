#include "rocket.h"

Rocket::Rocket(RocketType type, b2World* World, const b2Vec2& position)
        : GameItem(World),rocketType(type), currentFrameIndex(0)
{
    createRocketBody(position);
    loadExplosionFrames();

    // Setup animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Rocket::updateAnimation);
}

Rocket::~Rocket()
{
    world->DestroyBody(gBody);
}

void Rocket::createRocketBody(const b2Vec2& position)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;

    gBody = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Adjust the size based on your requirements

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    gBody->CreateFixture(&fixtureDef);
}

void Rocket::launch(const b2Vec2& velocity)
{
    gBody->ApplyLinearImpulse(gBody->GetMass() * velocity, gBody->GetWorldCenter(), true);
    animationTimer->start(100); // Adjust the timer interval based on your animation frames
}

void Rocket::updateAnimation()
{
    if (currentFrameIndex < explosionFrames.size()) {
        // Update animation frame
        // Render the current frame based on your rendering logic
        // For simplicity, assuming explosionFrames is a QVector of QPixmap
        QPixmap currentFrame = explosionFrames[currentFrameIndex];

        // Emit signal to notify about the animation update
        // You might want to connect this signal to a slot in your UI for rendering
        emit rocketExploded();

        // Increment the frame index
        ++currentFrameIndex;
    } else {
        // Animation is complete
        animationTimer->stop();
        // Additional cleanup or signal emission can be done here
    }
}

void Rocket::loadExplosionFrames()
{
    // Load explosion frames into QVector<QPixmap>
    // Replace this with your actual loading logic
    // For simplicity, assuming explosionFrames is a QVector of QPixmap
    // You might want to use QImageReader or other methods to load GIF frames
    //explosionFrames.append(QPixmap(":/explosion_frame_1.png"));
    //explosionFrames.append(QPixmap(":/explosion_frame_2.png"));
    // Add more frames as needed
}

void Rocket::setPosition(const b2Vec2& position)
{
    gBody->SetTransform(position, gBody->GetAngle());
}

b2Vec2 Rocket::getPosition() const
{
    return gBody->GetPosition();
}

void Rocket::setVelocity(const b2Vec2& velocity)
{
    gBody->SetLinearVelocity(velocity);
}

b2Vec2 Rocket::getVelocity() const
{
    return gBody->GetLinearVelocity();
}

void Rocket::setAngularVelocity(float angularVelocity)
{
    gBody->SetAngularVelocity(angularVelocity);
}

float Rocket::getAngularVelocity() const
{
    return gBody->GetAngularVelocity();
}

void Rocket::explode()
{
    // Additional logic for rocket explosion, if needed
    // You can add sound effects, particle effects, etc.
}
