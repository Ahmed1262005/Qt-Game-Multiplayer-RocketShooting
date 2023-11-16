// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "Box2D/Files/box2d.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
            void updateWorld();

private:
    void initializeBox2D();
    void createGround();
    void createDynamicBox(float x, float y);
    void createThrowableObject(float x, float y);

    b2Body* throwableObject;
    b2MouseJoint* mouseJoint;

    b2Vec2 dragStart;

    QTimer *timer;
    b2World *world;
};

#endif // MAINWINDOW_H
