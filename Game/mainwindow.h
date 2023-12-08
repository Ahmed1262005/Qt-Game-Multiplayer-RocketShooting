// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "level.h"
#include "obstacles.h"
#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QPalette>
#include <QMediaPlayer>
#include <Box2D/Box2D.h>
#include <vector>
//#include <level.h>

class Level;

class MainWindow : public QMainWindow , public b2ContactListener
{
    Q_OBJECT

public:
    void createRocket(float x, float y);
    b2Body *groundBody;
    b2Body* throwableObject;
    b2MouseJoint* mouseJoint;
    b2Body* rocketBody;
    b2Vec2 dragStart;
    QPixmap launcherPixmap;
    QPixmap rocketPixmap;
    MainWindow(QWidget *parent = nullptr);
    void showBackground();
    ~MainWindow();

    int currentLevel;
    void setCurrentLevel(int index) { currentLevel = index; } // Add this method
//    void nextLevel() {
//        if (currentLevel) {
//            delete currentLevel;
//        }
//        currentLevel = new Level(currentLevel->getDifficulty() + 1);
//    }
    QTimer *timer;
    b2World *world;
    void paintEvent(QPaintEvent *event);
    QPainter* get_renderer() const;
    void setMusicPlayer(bool);

    float calculateScore();
    void setTowers(QVector<Obstacles*>);
    void setEnemies(QVector<Obstacles*>);

protected:

    void keyPressEvent(QKeyEvent *event);
    //void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    //void mouseReleaseEvent(QMouseEvent*);


public slots:
        void updateWorld();

protected:
    void drawTrajectory(QPainter* painter);
    b2Vec2 calculateRocketVelocityForHeight(float desiredHeight);
    void drawLauncher(QPainter* painter, const b2Vec2 &position, float angle);
    b2Vec2 towerPosition;
    b2Vec2 enemiesPosition;

    QMediaPlayer* MusicPlayer;
    QAudioOutput* Speaker;

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
    void createTarget(float x, float y);
    void createDynamicBox(float x, float y);
    void createThrowableObject(float x, float y);

    void drawRotatedPixmap(QPainter* painter, const QPixmap &pixmap, const b2Vec2 &position, float angle);
    Obstacles* evilGuy;
    void BeginContact(b2Contact * contact);
    int enemyCounter;
    int counter = 4;
    bool win = false;
    QVector<Obstacles*> towers;
    QVector<Obstacles*> enemies;

    Level* lvl;
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

#endif // MAINWINDOW_H
