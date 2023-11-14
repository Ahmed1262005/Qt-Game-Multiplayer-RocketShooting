#ifndef MYQUERYCALLBACK_H
#define MYQUERYCALLBACK_H

#include <Box2D/Box2D.h>
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
