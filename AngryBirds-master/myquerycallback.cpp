#include "myquerycallback.h"
#include <QDebug>

MyQueryCallBack::MyQueryCallBack()
{
}

bool MyQueryCallBack::ReportFixture(b2Fixture *fixture)
{
    b2Body *body = fixture->GetBody();
    foundBodies.push_back(body);

    return true;
}
