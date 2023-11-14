#ifndef MYQUERYCALLBACK_H
#define MYQUERYCALLBACK_H

#include <Box2D/include/box2d/box2d.h>
#include <QVector>

class MyQueryCallBack : public b2QueryCallback
{
public:
    MyQueryCallBack();
    bool ReportFixture(b2Fixture *fixture);
public:
   QVector <b2Body *> foundBodies;
};

#endif // MYQUERYCALLBACK_H
