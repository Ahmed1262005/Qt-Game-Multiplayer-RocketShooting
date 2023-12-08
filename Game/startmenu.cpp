#include "startmenu.h"
#include "ui_startmenu.h"
#include "level.h"
#include "mainwindow.h"

StartMenu::StartMenu(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::StartMenu) {
    ui->setupUi(this);
    QPixmap background(":/Resources/Images/StartMenuBackground.png");
    //int w = ui->labelBackground->width();
    //int h = ui->labelBackground->height();
    ui->labelBackground->setPixmap(background.scaled(1920, 1080));
    generateLevels();
//    setWindowFlags(Qt::Window
//                   | Qt::WindowMinimizeButtonHint
//                   | Qt::WindowMaximizeButtonHint);
}
void StartMenu::generateLevels() {
    for (int i = 1; i <= 10; ++i) {
        Level* level = new Level(i);
        switch(i) {
            case 1:
                // Configuration for level 1
                level->AddTower(600.0f,-10.0f,200.0f,500.0f,1);
                level->AddEnemy(1100.f, -10.f,100.f,100.f,BasicEnemy);
                break;
            case 2:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 3:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 4:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 5:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 6:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 7:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 8:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 9:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 10:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            default:
                // Default configuration for levels without a specific case
                level->AddTower(600.0f * i,-10.0f * i,200.0f * i,500.0f * i,1);
                level->AddEnemy(1100.f * i, -10.f * i,100.f * i,100.f * i,BasicEnemy);
                break;
        }
        levels.push_back(level);
    }
}
StartMenu::~StartMenu() {
    delete ui;
}

Level *StartMenu::getCurrentLevel() {
    return levels[currentLevel];
}

void StartMenu::on_pushButtonlevel1_clicked() {
    hide();

    currentLevel = 0;
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();


}

void StartMenu::on_pushButtonlevel2_clicked() {
    hide();

    currentLevel = 1;
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}


// Repeat for the other levels
void StartMenu::on_pushButtonlevel3_clicked() {
    hide();

    currentLevel = 2;
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();

}

void StartMenu::on_pushButtonlevel4_clicked() {
    hide();

    currentLevel = 3;
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel5_clicked() {
    hide();
    currentLevel = 4; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel6_clicked() {
    hide();
    currentLevel = 5; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel7_clicked() {
    hide();
    currentLevel = 6; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel8_clicked() {
    hide();
    currentLevel = 7; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel9_clicked() {
    hide();
    currentLevel = 8; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

void StartMenu::on_pushButtonlevel10_clicked() {
    hide();
    currentLevel = 9; // Pass the difficulty as a parameter
    Level *lvl1 = getCurrentLevel();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();
}

