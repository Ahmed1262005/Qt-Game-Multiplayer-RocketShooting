#include "startmenu.h"
#include "ui_startmenu.h"
#include "level.h"
#include "mainwindow.h"
#include "level.h"

StartMenu::StartMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    QPixmap background(":/Resources/Images/StartMenuBackground.png");
    //int w = ui->labelBackground->width();
    //int h = ui->labelBackground->height();
    ui-> labelBackground -> setPixmap(background.scaled(1920, 1080));
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_pushButtonlevel1_clicked()
{
    hide();

    Level* lvl1 = new Level;

    lvl1->window->setMusicPlayer(true);

    lvl1->AddTower(1300.0f,-10.0f,200.0f,500.0f,1,1.0f,0.2f,50.0f);

    lvl1->AddEnemy(1100.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl1->drawObstacles();

    lvl1->window->showFullScreen();


}


void StartMenu::on_pushButtonlevel2_clicked()
{
    hide();

    Level* lvl2 = new Level;

    lvl2->AddTower(600.0f,-10.0f,200.0f,500.0f,1,1.0f,0.2f,50.0f);

    lvl2->AddTower(1300.0f,-10.0f,200.0f,500.0f,1,1.0f,0.2f,50.0f);

    lvl2->AddEnemy(1100.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl2->drawObstacles();

    lvl2->window->setMusicPlayer(true);

    lvl2->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel3_clicked()
{
    hide();

    Level* lvl3 = new Level;

    lvl3->AddTower(1600.0f,-10.0f,200.0f,400.0f,2,10.0f,10.f,0.2f);

    lvl3->AddTower(700.0f,-10.0f,200.0f,400.0f,1,10.0f,10.0f,0.2f);

    lvl3->AddTower(1300.0f,-10.0f,200.0f,400.0f,2,10.0f,10.0f,0.2f);

    lvl3->AddEnemy(1400.f, -10.f,100.f,100.f,1, 10.0f,10.0f,0.2f);

    lvl3->drawObstacles();

    lvl3->window->setMusicPlayer(true);

    lvl3->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel4_clicked()
{
    hide();

    Level* lvl4 = new Level;

    lvl4->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl4->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl4->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl4->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl4->drawObstacles();

    lvl4->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel5_clicked()
{
    hide();

    Level* lvl5 = new Level;

    lvl5->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl5->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl5->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl5->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl5->drawObstacles();

    lvl5->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel6_clicked()
{
    hide();

    Level* lvl6 = new Level;

    lvl6->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl6->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl6->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl6->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl6->drawObstacles();

    lvl6->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel7_clicked()
{
    hide();

    Level* lvl7 = new Level;

    lvl7->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl7->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl7->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl7->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl7->drawObstacles();

    lvl7->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel8_clicked()
{
    hide();

    Level* lvl8 = new Level;

    lvl8->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl8->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl8->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl8->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl8->drawObstacles();

    lvl8->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel9_clicked()
{
    hide();

    Level* lvl9 = new Level;

    lvl9->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl9->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl9->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl9->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl9->drawObstacles();

    lvl9->window->showFullScreen();
}


void StartMenu::on_pushButtonlevel10_clicked()
{
    hide();

    Level* lvl10 = new Level;

    lvl10->AddTower(400.0f,-10.0f,200.0f,400.0f,1,1.0f,0.2f,50.0f);

    lvl10->AddEnemy(850.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl10->AddTower(1300.0f,-10.0f,200.0f,300.0f,1,1.0f,0.2f,50.0f);

    lvl10->AddEnemy(1000.f, -10.f,100.f,100.f,1, 1.0f,0.2f,50.0f);

    lvl10->drawObstacles();

    lvl10->window->showFullScreen();
}
