#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include "obstacles.h"
#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QPalette>
#include <QMediaPlayer>
#include <Box2D/Box2D.h>
#include <vector>

class Level; // Forward declaration of class Level

class PhysicsWorld : public QMainWindow, public b2ContactListener {
    Q_OBJECT

public:
    // Functions and variables related to creating and managing the game world
    void createRocket(float x, float y); // Creates a rocket at given coordinates
    // Variables for managing physics bodies and interactions
    b2Body *groundBody;
    b2MouseJoint* mouseJoint;
    b2Body* rocketBody;
    b2Vec2 dragStart;
    // Pixmaps for launcher and rocket graphics
    QPixmap launcherPixmap;
    QPixmap rocketPixmap;

    // Constructor and destructor
    PhysicsWorld(QWidget *parent = nullptr);
    ~PhysicsWorld();

    // Current level management
    int currentLevel; // Index of the current level
    int getCurrentLevel(); //Getter for the level
    void setCurrentLevel(int index); // Setter for the level

    // Timer and physics world for updating the game
    QTimer *timer;
    b2World *world;

    // Functions for painting the game's visual elements
    void paintEvent(QPaintEvent *event); // Paints the game elements
    QPainter* get_renderer() const; // Retrieves the painter object
    void setMusicPlayer(bool); // Sets the music player

    // Functions for gameplay and logic
    float calculateScore(); // Calculates the game score
    void setRocketCount(int); // Setting the rocket number for the level
    void setTowers(QVector<Obstacles*>); // Sets tower objects
    void setEnemies(QVector<Obstacles*>); // Sets enemy objects

protected:
    // Event handlers for keyboard and mouse interaction
    void keyPressEvent(QKeyEvent *event); // Handles key presses
    void mouseMoveEvent(QMouseEvent*); // Handles mouse movement

public slots:
    void updateWorld(); // Updates the game world

protected:
    // Methods for drawing and physics calculations
    void drawTrajectory(QPainter* painter); // Draws rocket trajectory
    b2Vec2 calculateRocketVelocityForHeight(float desiredHeight); // Calculates rocket velocity for a desired height
    void drawLauncher(QPainter* painter, const b2Vec2 &position, float angle); // Draws the launcher
    b2Vec2 towerPosition; // Position of towers
    b2Vec2 enemiesPosition; // Position of enemies

    // Audio-related variables
    QMediaPlayer* MusicPlayer; // Media player for game music
    QAudioOutput* Speaker; // Output device for audio

    // Variables for trajectory prediction
    bool drawPredictedCollision; // Flag for drawing predicted collision
    // Callback class for raycasting
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
    b2Vec2 getTrajectoryPoint(b2Vec2 &startingPosition, b2Vec2 &startingVelocity, float n); // Gets trajectory points
    b2Vec2 predictedCollisionPoint; // Predicted collision point

    // Variables for rocket position and velocity
    b2Vec2 rocketPosition;
    b2Vec2 rocketVelocity;

    // Mouse-related variables
    QVector2D mousePosition; // Current mouse position
    bool isMousePressed; // Flag indicating if mouse is pressed

    int trajectoryPointsCount; // Count of trajectory points

    // Methods for initializing the Box2D world and game elements
    void showBackground(); //Draws the background of the world
    void initializeBox2D(); // Initializes Box2D
    void createGround(); // Creates the ground
    void launchRocket(float desiredHeight); // Launches the rocket
    void updateRocketTrajectory(); // Updates rocket trajectory

    // Method for drawing rotated pixmaps
    void drawRotatedPixmap(QPainter* painter, const QPixmap &pixmap, const b2Vec2 &position, float angle);
    void BeginContact(b2Contact * contact); // Handles contact between bodies
    int enemyCounter; // Counter for enemies
    int counter; // General counter
    QVector<Obstacles*> towers; // Vector of tower objects
    QVector<Obstacles*> enemies; // Vector of enemy objects

    Level* lvl; // Pointer to the game level
};

// Class for querying fixtures in Box2D
class QueryCallback : public b2QueryCallback {
public:
    QueryCallback(const b2Vec2& point) : m_point(point), m_fixture(nullptr) {}

    bool ReportFixture(b2Fixture* fixture) override {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody && fixture->TestPoint(m_point)) {
            m_fixture = fixture;
            return false; // Stop the query after finding the first matching fixture
        }
        return true; // Continue the query
    }

    b2Vec2 m_point; // Query point
    b2Fixture* m_fixture; // Fixture found by query
};

#endif // PHYSICSWORLD_H
