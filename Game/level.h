#ifndef LEVEL_H
#define LEVEL_H

#include "rocket.h"
#include "enemy.h"
#include <vector>
#include "obstacles.h"

class MainWindow;

class Level : public QObject {
public:
    Level(int difficulty);

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

    int getDifficulty() {
        return difficulty;
    };

    int getWinOffset() const { return winOffset; }

    int winOffset;

    void increaseDifficulty();

    void AddTower(qreal, qreal, qreal, qreal, int, qreal a = 10.0f, qreal b = 10.0f, qreal c = 10.0f);

    void AddEnemy(qreal, qreal, qreal, qreal, int, qreal a = 10.0f, qreal b = 10.0f, qreal c = 10.0f);

    void drawObstacles();

    MainWindow *window;

    QVector<Obstacles *> get_towers();

private:
    int levelNumber;
    int difficulty;
    int score;
    int remainingRockets;
    int maxRocketCount;
    b2Vec2 towerPosition;

    QVector<Rocket> rockets;

    int enemyHealth; // Health/damage threshold for enemies in this level
    bool gamePaused;

    // Helper functions for level initialization, scoring, etc.
    void createInitialRockets();

    void createInitialEnemies();

    void updateScore(int points);

    void checkWinCondition();

    void checkLoseCondition();


    QVector<Obstacles *> Towers;
    QVector<Obstacles *> Enemies;
};

#endif // LEVEL_H
