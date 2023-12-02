#include "level.h"
#include "rocket.h"
#include "enemy.h"
#include <iostream>
#include <QTimer>

Level::Level()
{
    initializeLevel();

    window = new MainWindow;

    window->setTowers(Towers);

    connect(window->timer,&QTimer::timeout,this, &Level::drawObstacles);

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

/*void Level::createInitialEnemies()
{
    // Adjust as needed based on the level and difficulty
    for (int i = 0; i < difficulty; ++i) {
        enemies.push_back(Enemy(Enemy::EnemyType::BasicEnemy, enemyHealth));
    }
}
*/

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

//int Level::getRemainingEnemies() const {
    //return static_cast<int>(enemies.size());
//}

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

void Level::AddTower(qreal x, qreal y, qreal width, qreal height, int towertype)
{
    switch (towertype) {
    case 1 :

        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower1.png"), window->world));

        break;

    case 2 :

        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower2.png"), window->world));

        break;


    case 3 :

    Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower3.png"), window->world));

    break;

    case 4 :

    Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower4.png"), window->world));

    break;

    }

    window->setTowers(Towers);

}

void Level::drawObstacles()
{

    //QPaintEvent* a = new QPaintEvent(QRect(0,0,1,1));

    //window->paintEvent(a , Towers);

    window->update();

}
