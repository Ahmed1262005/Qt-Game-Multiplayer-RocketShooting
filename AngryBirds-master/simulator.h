#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "world.h"

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator(QGraphicsScene *scene, QObject *parent = 0);
	~Simulator();
    void simulate();
    void startStopSimulating();

signals:

public slots:
    void step();
public:
    World *_world;
private:

    QGraphicsScene *_scene;
    QTimer *timer;
    bool _running;
};

#endif // SIMULATOR_H
