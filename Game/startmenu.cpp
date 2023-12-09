#include "startmenu.h"
#include "ui_startmenu.h"
#include "level.h"
#include "mainwindow.h"

StartMenu::StartMenu(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::StartMenu) {
    ui->setupUi(this);
    QPixmap background(":/Resources/Images/StartMenuBackground.png");
    QPixmap lock("://Resources/Images/lock.png");
    //int w = ui->labelBackground->width();
    //int h = ui->labelBackground->height();
    ui->labellock_1->setPixmap(lock.scaled(ui->labellock_1->width(), ui->labellock_1->height()));
    ui->labellock_2->setPixmap(lock.scaled(ui->labellock_2->width(), ui->labellock_2->height()));
    ui->labellock_3->setPixmap(lock.scaled(ui->labellock_3->width(), ui->labellock_3->height()));
    ui->labellock_4->setPixmap(lock.scaled(ui->labellock_4->width(), ui->labellock_4->height()));
    ui->labellock_5->setPixmap(lock.scaled(ui->labellock_5->width(), ui->labellock_5->height()));
    ui->labellock_6->setPixmap(lock.scaled(ui->labellock_6->width(), ui->labellock_6->height()));
    ui->labellock_7->setPixmap(lock.scaled(ui->labellock_7->width(), ui->labellock_7->height()));
    ui->labellock_8->setPixmap(lock.scaled(ui->labellock_8->width(), ui->labellock_8->height()));
    ui->labellock_9->setPixmap(lock.scaled(ui->labellock_9->width(), ui->labellock_9->height()));
    ui->labellock_10->setPixmap(lock.scaled(ui->labellock_10->width(), ui->labellock_10->height()));
    ui->labelBackground->setPixmap(background.scaled(1920, 1080));

    ui->labelTitle->setPixmap(QPixmap(":/Resources/Images/Title.png").scaled(600,100,Qt::KeepAspectRatio));
    generateLevels();
//    setWindowFlags(Qt::Window
//                   | Qt::WindowMinimizeButtonHint
//                   | Qt::WindowMaximizeButtonHint);
}
void StartMenu::generateLevels() {
    for (int i = 1; i <= 10; ++i) {
        Level* level = new Level(i);
        switch (i) {
            case 1:
                // Configuration for level 1
                level->AddTower(600.0f,-10.0f,200.0f,500.0f,2);
                level->AddEnemy(1100.f, -10.f,100.f,100.f,ArmoredEnemy);
                break;
            case 2:
                // Configuration for level 2
                level->AddTower(600.0f,-10.0f,200.0f,500.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 3:
                // Configuration for level 2
                level->AddTower(600.0f,-10.0f,200.0f,500.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 4:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,340.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 5:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,310.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 6:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 7:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,320.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 8:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,203.f,200.f,ArmoredEnemy);
                break;
            case 9:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,354.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,200.f,200.f,ArmoredEnemy);
                break;
            case 10:
                // Configuration for level 2
                level->AddTower(700.0f,-20.0f,300.0f,600.0f,2);
                level->AddEnemy(1200.f, -20.f,220.f,200.f,ArmoredEnemy);
                break;
            default:
                // Default configuration for levels without a specific case
                level->AddTower(600.0f * i,-10.0f * i,200.0f * i,500.0f * i,1);
                level->AddEnemy(1100.f * i, -10.f * i,100.f * i,100.f * i,BasicEnemy);
                break;
        }
        levels.push_back(level);
    }

    levels[0]->set_unlocked(1);

    ui->labellock_1->setVisible(0);

    if(levels[1]->get_unlocked())
        ui->labellock_2->setVisible(0);
    if(levels[2]->get_unlocked())
        ui->labellock_3->setVisible(0);
    if(levels[3]->get_unlocked())
        ui->labellock_4->setVisible(0);
    if(levels[4]->get_unlocked())
        ui->labellock_5->setVisible(0);
    if(levels[5]->get_unlocked())
        ui->labellock_6->setVisible(0);
    if(levels[6]->get_unlocked())
        ui->labellock_7->setVisible(0);
    if(levels[7]->get_unlocked())
        ui->labellock_8->setVisible(0);
    if(levels[8]->get_unlocked())
        ui->labellock_9->setVisible(0);
    if(levels[9]->get_unlocked())
        ui->labellock_10->setVisible(0);
}
StartMenu::~StartMenu() {
    delete ui;
}

Level *StartMenu::getCurrentLevel() {
    return levels[currentLevel];
}

void StartMenu::on_pushButtonlevel1_clicked() {

    currentLevel = 0;
    Level *lvl1 = getCurrentLevel();
    hide();

    lvl1->drawObstacles();
    lvl1->window->setCurrentLevel(currentLevel);
    lvl1->window->showFullScreen();


}

void StartMenu::on_pushButtonlevel2_clicked() {
    if(levels[1]->get_unlocked())
    {


        hide();

        currentLevel = 1;
        Level *lvl2 = getCurrentLevel();

        lvl2->drawObstacles();
        lvl2->window->setCurrentLevel(currentLevel);
        lvl2->window->showFullScreen();
    }
}


// Repeat for the other levels
void StartMenu::on_pushButtonlevel3_clicked() {

    if(levels[2]->get_unlocked())
    {
        hide();

        currentLevel = 2;
        Level *lvl3 = getCurrentLevel();

        lvl3->drawObstacles();
        lvl3->window->setCurrentLevel(currentLevel);
        lvl3->window->showFullScreen();
    }

}

void StartMenu::on_pushButtonlevel4_clicked() {

    if(levels[3]->get_unlocked())
    {
        hide();

        currentLevel = 3;
        Level *lvl4 = getCurrentLevel();

        lvl4->drawObstacles();
        lvl4->window->setCurrentLevel(currentLevel);
        lvl4->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel5_clicked() {

    if(levels[4]->get_unlocked())
    {
    hide();
    currentLevel = 4; // Pass the difficulty as a parameter
    Level *lvl5 = getCurrentLevel();

    lvl5->drawObstacles();
    lvl5->window->setCurrentLevel(currentLevel);
    lvl5->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel6_clicked() {

    if(levels[5]->get_unlocked())
    {
    hide();
    currentLevel = 5; // Pass the difficulty as a parameter
    Level *lvl6 = getCurrentLevel();

    lvl6->drawObstacles();
    lvl6->window->setCurrentLevel(currentLevel);
    lvl6->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel7_clicked() {
    if(levels[6]->get_unlocked())
    {
    hide();
    currentLevel = 6; // Pass the difficulty as a parameter
    Level *lvl7 = getCurrentLevel();

    lvl7->drawObstacles();
    lvl7->window->setCurrentLevel(currentLevel);
    lvl7->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel8_clicked() {
    if(levels[7]->get_unlocked())
    {
    hide();
    currentLevel = 7; // Pass the difficulty as a parameter
    Level *lvl8 = getCurrentLevel();

    lvl8->drawObstacles();
    lvl8->window->setCurrentLevel(currentLevel);
    lvl8->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel9_clicked() {
    if(levels[8]->get_unlocked())
    {
    hide();
    currentLevel = 8; // Pass the difficulty as a parameter
    Level *lvl9 = getCurrentLevel();

    lvl9->drawObstacles();
    lvl9->window->setCurrentLevel(currentLevel);
    lvl9->window->showFullScreen();
    }
}

void StartMenu::on_pushButtonlevel10_clicked() {
    if(levels[9]->get_unlocked())
    {
    hide();
    currentLevel = 9; // Pass the difficulty as a parameter
    Level *lvl10 = getCurrentLevel();

    lvl10->drawObstacles();
    lvl10->window->setCurrentLevel(currentLevel);
    lvl10->window->showFullScreen();
    }
}


void StartMenu::on_pushButtonQuit_clicked()
{
    exit(1);
}

