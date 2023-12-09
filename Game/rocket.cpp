#include "rocket.h"

Rocket::Rocket(RocketType type, b2World* World, const b2Vec2& position)
        : GameItem(World),rocketType(type)
{
    createRocketBody(position);
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
    bodyDef.angularDamping=-100.f;
    bodyDef.linearDamping=-100.f;

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
