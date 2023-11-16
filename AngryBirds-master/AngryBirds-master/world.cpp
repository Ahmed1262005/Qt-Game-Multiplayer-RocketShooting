#include "world.h"

World::World()
{
    b2Vec2 gravity(0.0f, -10.0f);
    _world = new b2World(gravity);
}
