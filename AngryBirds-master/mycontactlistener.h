#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D/include/box2d/box2d.h>

class MyContactListener : public b2ContactListener
{
public:
    MyContactListener();
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

#endif // MYCONTACTLISTENER_H
