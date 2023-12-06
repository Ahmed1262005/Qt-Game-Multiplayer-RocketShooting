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

    lvl1->AddTower(600.0f,-10.0f,200.0f,500.0f,1,1.0f,1.0f,10.0f,10.0f,0.2f,0.2f);

    lvl1->AddTower(1300.0f,-10.0f,200.0f,500.0f,1,10.0f,0.2f,0.2f);

    lvl1->AddEnemy(1100.f, -10.f,100.f,100.f,BasicEnemy);

    lvl1->drawObstacles();

    lvl1->window->showFullScreen();


}


void StartMenu::on_pushButtonlevel2_clicked()
{

}


void StartMenu::on_pushButtonlevel3_clicked()
{

}


void StartMenu::on_pushButtonlevel4_clicked()
{

}


void StartMenu::on_pushButtonlevel5_clicked()
{

}


void StartMenu::on_pushButtonlevel6_clicked()
{

}


void StartMenu::on_pushButtonlevel7_clicked()
{

}


void StartMenu::on_pushButtonlevel8_clicked()
{

}


void StartMenu::on_pushButtonlevel9_clicked()
{

}


void StartMenu::on_pushButtonlevel10_clicked()
{

}
