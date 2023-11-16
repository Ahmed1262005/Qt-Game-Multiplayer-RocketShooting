#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "simulator.h"

class SceneManager : public QObject
{
    Q_OBJECT
public:
    SceneManager(QGraphicsScene *scene, QGraphicsView *view, QObject *parent = 0);
    void addItem(QString obj, QGraphicsView *view, QPointF pos);
private:
    QGraphicsScene *_scene;
    QGraphicsView *_view;
public:
};

#endif // SCENEMANAGER_H
