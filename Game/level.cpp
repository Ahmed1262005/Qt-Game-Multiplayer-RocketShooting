#include "level.h"
#include "rocket.h"
#include "enemy.h"
#include <iostream>
#include <QTimer>
#include "mainwindow.h"
#include "obstacles.h"

Level::Level(int difficulty)
{
    int numEnemies = difficulty * 10; // Adjust as needed
    float enemySpeed = difficulty * 1.0f; // Adjust as needed
    // Add the enemies to the level
//    for (int i = 0; i < numEnemies; ++i) {
//        AddEnemy(1100.f, -enemySpeed, 100.f, 100.f, BasicEnemy);
//    }
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

void Level::AddTower(qreal x, qreal y, qreal width, qreal height, int towertype, qreal density, qreal friction, qreal restitution)
{
    switch (towertype) {
    case 1 :

        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower1.png"), window->world, density, friction, restitution));

        break;

    case 2 :
    // Check if towertype is within the range 1 to 14
    if(towertype < 1 || towertype > 14) {
        std::cout << "Invalid tower type. It should be between 1 and 14." << std::endl;
        return;
    }

        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower2.png"), window->world, density, friction, restitution));
    // Construct the image path based on towertype
    QString towerTypeString = QString::number(towertype);
    QString image = ":/Resources/Images/tower" + towerTypeString + ".png";

        break;


    case 3 :

    Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower3.png"), window->world, density, friction, restitution));

    break;

    case 4 :

    Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower4.png"), window->world, density, friction, restitution));

    break;

    }
    Towers.push_back(new Obstacles(x, y, width, height, QPixmap(image), window->world));

    window->setTowers(Towers);
}

void Level::AddEnemy(qreal x, qreal y, qreal width, qreal height, int enemyType, qreal density = 10.0f, qreal friction = 0.2f, qreal restitution = 0.2f)
{
    switch (enemyType) {
    case 1 :

    Enemies.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/EvilGuy.png"), window->world, density, friction, restitution));
    Enemies.back()->get_body()->SetUserData((void*)"EvilGuy");

    break;

    case 2 :

    Enemies.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower2.png"), window->world, density, friction, restitution));
    Enemies.back()->get_body()->SetUserData((void*)"EvilGuy");

    break;

    }

    window->setEnemies(Enemies);

}
void Level::drawObstacles()
{

    //QPaintEvent* a = new QPaintEvent(QRect(0,0,1,1));

    //window->paintEvent(a , Towers);

    window->update();

}

QVector<Obstacles*> Level::get_towers()
{
    return Towers;
}
