#include "mycontactlistener.h"
#include "piggs.h"

MyContactListener::MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact *contact)
{
    void *userData = contact->GetFixtureA()->GetBody()->GetUserData();
    if(userData)
        static_cast<Piggs *> (userData)->startContact();
    userData = contact->GetFixtureB()->GetBody()->GetUserData();
    if(userData)
        static_cast<Piggs *> (userData)->startContact();


}

void MyContactListener::EndContact(b2Contact *contact)
{
    void *userData = contact->GetFixtureA()->GetBody()->GetUserData();
    if(userData)
        static_cast<Piggs *> (userData)->endContact();
    userData = contact->GetFixtureB()->GetBody()->GetUserData();
    if(userData)
        static_cast<Piggs *> (userData)->endContact();

}

