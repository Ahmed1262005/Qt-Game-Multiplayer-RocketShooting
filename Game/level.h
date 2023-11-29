#ifndef LEVEL_H
#define LEVEL_H

#include "rocket.h"
#include "enemy.h"
#include <vector>
#include <mainwindow.h>
#include "obstacles.h"

class Level
{
public:
    Level(int levelNumber, int difficulty, int initialRocketCount);

    void initializeLevel(); // Initialize the level with enemies, rockets, etc.
    void update(); // Update the level (e.g., check for win/lose conditions)

    // Getters for various attributes
    int getScore() const;
    int getRemainingRockets() const;
    int getRemainingEnemies() const;
    int getCurrentDifficulty() const;
    enum RocketType {
        Qassam1,
        BasicRocket
        // Add more enemy types as needed
    };

    // Functions for user actions during gameplay
    void launchRocket(RocketType rocketType);
    void pauseGame();
    void resumeGame();
    void increaseDifficulty();

private:
    int levelNumber;
    int difficulty;
    int score;
    int remainingRockets;
    int maxRocketCount;

    QVector<Rocket> rockets;
    QVector<Rocket> enemies;

    int enemyHealth; // Health/damage threshold for enemies in this level
    bool gamePaused;

    // Helper functions for level initialization, scoring, etc.
    void createInitialRockets();
    void createInitialEnemies();
    void updateScore(int points);
    void checkWinCondition();
    void checkLoseCondition();
    void drawObstacles(QPainter*);
    void AddTower(qreal, qreal, qreal, qreal, QPixmap, b2World, int);
    void AddEnemy(qreal, qreal, qreal, qreal, QPixmap, b2World, int);
    MainWindow* window;
    QVector<Obstacles*> Towers;
    QVector<Obstacles*> Enemies;
};

#endif // LEVEL_H
