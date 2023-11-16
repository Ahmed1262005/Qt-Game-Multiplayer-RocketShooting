#include "simulator.h"
#include "physicitem.h"
#include <QList>
#include <QGraphicsItem>

static const int32 B2_VELOCITY_ITERATIONS = 8;//6
static const int32 B2_POSITION_ITERATIONS = 6;//2

static const float32 B2_TIMESTEP = 1.0f / 60.0f;


Simulator::Simulator(QGraphicsScene *scene, QObject *parent) :
    QObject(parent), _scene(scene)
{
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(step()));

    _world = new World();
    _running = false;
}

void Simulator::simulate()
{
    QList <QGraphicsItem *> items = _scene->items();

    for (int i = 0; i < items.size(); ++i)
    {
        PhysicItem *item = qgraphicsitem_cast<PhysicItem *>(items.at(i));
        if(!item->_simulated)
        {
            item->setWorld(_world->_world);
            item->simulating();
        }
    }
}

void Simulator::startStopSimulating()
{
    if(!_running)
    {
        _running = true;
        QList <QGraphicsItem *> items = _scene->items();
        timer->start();
        for (int i = 0; i < items.size(); ++i)
        {
            PhysicItem *item = qgraphicsitem_cast<PhysicItem *>(items.at(i));
            item->Simulationstaring();
        }

    }else
    {
        QList <QGraphicsItem *> items = _scene->items();
        timer->stop();
        for (int i = 0; i < items.size(); ++i)
        {
            PhysicItem *item = qgraphicsitem_cast<PhysicItem *>(items.at(i));
            item->simulationStoping();
        }
    }
}

void Simulator::step()
{
    _world->_world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);
    _scene->advance();
}

Simulator::~Simulator()
{
    delete timer;
}
