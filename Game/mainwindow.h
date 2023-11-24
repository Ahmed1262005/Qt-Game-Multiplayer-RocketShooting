// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QPalette>
#include <Box2D/Box2D.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showBackground();

    ~MainWindow();
    QTimer *timer;
    b2World *world;
    void paintEvent(QPaintEvent *event);
protected:

    void keyPressEvent(QKeyEvent *event);
    //void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    //void mouseReleaseEvent(QMouseEvent*);


private slots:
        void updateWorld();

private:
    void drawTrajectory(QPainter &painter);
    b2Vec2 calculateRocketVelocityForHeight(float desiredHeight);

    bool drawPredictedCollision;
    class TrajectoryRayCastClosestCallback : public b2RayCastCallback {
    public:
        TrajectoryRayCastClosestCallback() : m_hit(false) {}

        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                              const b2Vec2& normal, float32 fraction) override {
            m_hit = true;
            m_point = point;
            return fraction;
        }

        bool m_hit;
        b2Vec2 m_point;
    };
    b2Vec2 getTrajectoryPoint(b2Vec2 &startingPosition, b2Vec2 &startingVelocity, float n);
    b2Vec2 predictedCollisionPoint;

    b2Vec2 rocketPosition;
    b2Vec2 rocketVelocity;

    QVector2D mousePosition;
    bool isMousePressed;

    int trajectoryPointsCount;

    void initializeBox2D();
    void createGround();
    void launchRocket(float desiredHeight);
    void updateRocketTrajectory();
    void createRocket(float x, float y);
    void createTarget(float x, float y);
    void createDynamicBox(float x, float y);
    void createThrowableObject(float x, float y);
    b2Body *groundBody;
    b2Body* throwableObject;
    b2MouseJoint* mouseJoint;
    b2Body* rocketBody;


    b2Vec2 dragStart;


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

enum {
    BallObject,
    WallObject,
};

struct Object
{
    int type;
    b2Body *body;
    b2Fixture *fixture;
};

class World : public QWidget {
public:
    World()
        : _timerId(0)
    {
        b2Vec2 gravity(0.0f, -10.0f);
        bool doSleep(true);
        _world = new b2World(gravity);

        for(int i=0; i<30; i++) {
            int dx = 18 - rand() % 36;
            int dy = rand() % 2;
            _objects.append(createBall(b2Vec2(18.0f+dx, 62.0f-dy), 1.0f));
        }

        _transform.scale(10.0f, -10.0f);
        _transform.translate(0.0f, -64.0f);
        _objects.append(createWall(0.0f, 0.0f, 36.0f, 1.0f));
        _objects.append(createWall(0.0f, 0.0f, 1.0f, 64.0f));
        _objects.append(createWall(35.0f, 0.0f, 1.0f, 64.0f));
        _objects.append(createWall(14.0f, 32.0f, 8.0f, 1.0f, 0.0f*b2_pi));
        _objects.append(createWall(4.0f, 48.0f, 8.0f, 1.0f, 0.25f*b2_pi));
        _objects.append(createWall(24.0f, 48.0f, 8.0f, 1.0f, -0.25f*b2_pi));

    }

    Object createWall(float32 x, float32 y, float32 w, float32 h, float32 angle=0) {
        Object o;
        // body
        b2BodyDef bd;
        bd.type = b2_staticBody;
        bd.position = b2Vec2(x+w/2.0f, y+h/2.0f);
        bd.angle = angle * b2_pi;
        o.body = _world->CreateBody(&bd);
        // shape
        b2PolygonShape shape;
        shape.SetAsBox(w/2.0f, h/2.0f);
        // fixture
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 0.1f;
        fd.friction = 0.3f;
        o.fixture = o.body->CreateFixture(&fd);
        o.type = WallObject;
        return o;
    }

    Object createBall(const b2Vec2& pos, float32 radius) {
        Object o;
        // body
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = pos;
        o.body = _world->CreateBody(&bd);
        // shape
        b2CircleShape shape;
        shape.m_radius = radius;
        // fixture
        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;
        fd.friction = 1.0f;
        fd.restitution = 0.6f;
        o.fixture = o.body->CreateFixture(&fd);
        o.type = BallObject;
        return o;
    }

    void paintEvent(QPaintEvent *) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setTransform(_transform);
        foreach(const Object& o, _objects) {
            switch(o.type) {
            case BallObject:
                drawEllipse(&p, o);
                break;
            case WallObject:
                drawWall(&p, o);

            }

        }
    }

    void drawWall(QPainter *p, const Object& o) {
        float32 x = o.body->GetPosition().x;
        float32 y = o.body->GetPosition().y;
        float32 angle = o.body->GetAngle();
        const b2PolygonShape *shape = dynamic_cast<b2PolygonShape*>(o.fixture->GetShape());
        float32 hx = shape->GetVertex(1).x;
        float32 hy = shape->GetVertex(2).y;
        QRectF r(x-hx, y-hy, 2*hx, 2*hy);
        p->save();
        p->translate(r.center());
        p->rotate(angle*180/b2_pi);
        p->translate(-r.center());
        p->drawRect(r);
        p->restore();
    }

    void drawEllipse(QPainter *p, const Object& o) {
        float32 x = o.body->GetPosition().x;
        float32 y = o.body->GetPosition().y;
        float32 r = o.fixture->GetShape()->m_radius;
        p->drawEllipse(QPointF(x, y), r, r);
    }

    void start() {
        if(!_timerId) {
            _timerId = startTimer(1000/60); // 60fps
        }
    }
    void timerEvent(QTimerEvent *event) {
        if(event->timerId() == _timerId) {
            _world->Step(1.0f/60.0f, 8, 3);
            update();
        }
    }

private:
    b2World *_world;
    int _timerId;
    QTransform _transform;
    QVector<Object> _objects;
};

#endif // MAINWINDOW_H
