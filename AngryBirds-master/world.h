#ifndef WORLD_H
#define WORLD_H

#include <Box2D/include/box2d/box2d.h>

class World
{
public:
    World();
public:
    b2World *_world;
};

#endif // WORLD_H
