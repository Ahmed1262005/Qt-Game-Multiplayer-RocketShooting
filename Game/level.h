#ifndef LEVEL_H
#define LEVEL_H

#include "rocket.h"
#include "enemy.h"
#include <vector>
#include "obstacles.h"

class MainWindow;

class Level : public QObject {
public:
    enum RocketType {
        Qassam1,
        BasicRocket
        // Add more enemy types as needed
    };

    // Constructor for Level class
    Level(int difficulty);

    // Initialize the level with enemies, rockets, etc.
    void initializeLevel();

    // Update the level (e.g., check for win/lose conditions)
    void update();

    // Getters for various attributes

    // Get the current score of the level
    int getScore() const;

    // Get the number of remaining rockets
    int getRemainingRockets() const;

    // Get the number of remaining enemies
    int getRemainingEnemies() const;

    // Get the current difficulty level
    int getDifficulty() {
        return difficulty;
    };

    // Check if the level is unlocked
    bool get_unlocked();

    // Get the win offset for the level
    int getWinOffset() const;

    // Get a vector containing tower objects in the level
    QVector<Obstacles *> get_towers();

    // Functions for user actions during gameplay

    // Increase the difficulty level
    void increaseDifficulty();

    // Add a tower to the level
    void AddTower(qreal, qreal, qreal, qreal, int, qreal density = 10.0f, qreal friction = 0.2f, qreal restitution = 0.2f);

    // Add an enemy to the level
    void AddEnemy(qreal x, qreal y, qreal width, qreal height, int enemyType, qreal density = 10.0f, qreal friction = 0.2f,
                  qreal restitution = 0.2f);

    // Draw obstacles/entities in the level
    void drawObstacles();

    // Pointer to MainWindow for interaction
    MainWindow *window;

    // Set the unlock status
    void set_unlocked(bool unlock);

    ~Level();

private:
    int levelNumber;      // The level number
    int difficulty;       // The current difficulty level
    int score;            // The current score
    int remainingRockets; // Number of remaining rockets
    int maxRocketCount;   // Maximum count of rockets
    b2Vec2 towerPosition; // Position of a tower
    int enemyHealth;      // Health/damage threshold for enemies in this level
    bool gamePaused;      // Flag indicating if the game is paused
    int winOffset;        // Win offset for the level
    bool unlocked=true;        // Flag indicating if the level is unlocked

    QVector<Rocket> rockets;     // Vector of rockets in the level
    QVector<Obstacles *> Towers; // Vector of tower objects in the level
    QVector<Obstacles *> Enemies; // Vector of enemy objects in the level

    // Helper functions for level initialization, scoring, etc.

    // Create initial rockets for the level
    void createInitialRockets();

    // Create initial enemies for the level
    void createInitialEnemies();

    // Update the score based on points earned
    void updateScore(int points);

    // Check if the win condition is met
    void checkWinCondition();

    // Check if the lose condition is met
    void checkLoseCondition();
};

#endif // LEVEL_H
