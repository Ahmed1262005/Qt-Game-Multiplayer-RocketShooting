// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <Box2D.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private slots:
            void updateWorld();

private:
    void initializeBox2D();
    void createGround();
    void createDynamicBox(float x, float y);
    void createThrowableObject(float x, float y);
    b2Body *groundBody;
    b2Body* throwableObject;
    b2MouseJoint* mouseJoint;


    b2Vec2 dragStart;

    QTimer *timer;
    b2World *world;
};

class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback(const b2Vec2& point) : m_point(point), m_fixture(nullptr) {}

    bool ReportFixture(b2Fixture* fixture) override
    {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody && fixture->TestPoint(m_point))
        {
            m_fixture = fixture;
            return false; // Stop the query after finding the first matching fixture
        }
        return true; // Continue the query
    }

    b2Vec2 m_point;
    b2Fixture* m_fixture;
};
#endif // MAINWINDOW_H
