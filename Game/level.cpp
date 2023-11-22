#include "level.h"
#include "rocket.h"
#include "enemy.h"
#include <iostream>

Level::Level(int levelNumber, int difficulty, int initialRocketCount)
        : levelNumber(levelNumber), difficulty(difficulty), score(0),
          remainingRockets(initialRocketCount), maxRocketCount(initialRocketCount * 2),
          enemyHealth(50), gamePaused(false) {
    initializeLevel();
}

void Level::initializeLevel() {
    std::cout << "Initializing Level " << levelNumber << " with difficulty " << difficulty << std::endl;

    // Initialize rockets and enemies
//    createInitialRockets();
//    createInitialEnemies();
}
//
//void Level::createInitialRockets()
//{
//    // Adjust as needed based on the level and difficulty
//    for (int i = 0; i < remainingRockets; ++i) {
//        rockets.( Rocket(RocketType::BasicRocket, 10));
//    }
//}
//
//void Level::createInitialEnemies()
//{
//    // Adjust as needed based on the level and difficulty
//    for (int i = 0; i < difficulty; ++i) {
//        enemies.push_back(Enemy(Enemy::EnemyType::BasicEnemy, enemyHealth));
//    }
//}

void Level::update() {
    if (!gamePaused) {
        // Update rockets, enemies, check win/lose conditions, etc.
        // Placeholder code; update based on your game logic
        std::cout << "Updating Level " << levelNumber << std::endl;
    }
}

int Level::getScore() const {
    return score;
}

int Level::getRemainingRockets() const {
    return remainingRockets;
}

int Level::getRemainingEnemies() const {
    return static_cast<int>(enemies.size());
}

int Level::getCurrentDifficulty() const {
    return difficulty;
}

//void Level::launchRocket(RocketType rocketType) {
//    if (remainingRockets > 0 && rockets.size() < maxRocketCount) {
//        rockets.push_back(Rocket(rocketType, 10));
//        remainingRockets--;
//    }
//}

void Level::pauseGame() {
    gamePaused = true;
}

void Level::resumeGame() {
    gamePaused = false;
}

void Level::increaseDifficulty() {
    difficulty++;
//    createInitialEnemies();
}
