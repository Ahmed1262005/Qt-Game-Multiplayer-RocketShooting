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
    initializeLevel();

    window = new MainWindow;

    window->setTowers(Towers);

    connect(window->timer,&QTimer::timeout,this, &Level::drawObstacles);

}

void Level::initializeLevel() {
}

void Level::update() {
    if (!gamePaused) {
        std::cout << "Updating Level " << levelNumber << std::endl;
    }
}

int Level::getScore() const {
    return score;
}

int Level::getRemainingRockets() const {
    return remainingRockets;
}
void Level::increaseDifficulty() {
    difficulty++;
}

void Level::AddTower(qreal x, qreal y, qreal width, qreal height, int towertype, qreal density, qreal friction, qreal restitution)
{
    QString towerTypeString = QString::number(towertype);
    QString image = ":/Resources/Images/tower" + towerTypeString + ".png";
    switch (towertype) {
    case 1 :
        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower1.png"), window->world, density, friction, restitution));
        break;
    case 2 :
        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower2.png"), window->world, density, friction, restitution));
        break;
    case 3 :
        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower3.png"), window->world, density, friction, restitution));
        break;
    case 4 :
        Towers.push_back(new Obstacles(x,y,width,height, QPixmap(":/Resources/Images/tower4.png"), window->world, density, friction, restitution));
        break;
    }
    window->setTowers(Towers);
}

void Level::AddEnemy(qreal x, qreal y, qreal width, qreal height, int enemyType, qreal density, qreal friction, qreal restitution)
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
    window->update();
}

QVector<Obstacles*> Level::get_towers()
{
    return Towers;
}

int Level::getWinOffset() const
{
     return winOffset;
}

void Level::set_unlocked(bool unlock)
{
     unlocked = unlock;
}

bool Level::get_unlocked()
{
     return unlocked;
}

Level::~Level()
{
     for(int i=0;i<Towers.size();i++)
     {
        delete Towers[i];
     }
     for(int i=0;i<Enemies.size();i++)
     {
        delete Enemies[i];
     }
}
