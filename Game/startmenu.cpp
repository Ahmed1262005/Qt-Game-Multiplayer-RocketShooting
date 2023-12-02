#include "startmenu.h"
#include "ui_startmenu.h"
#include "level.h"
#include "mainwindow.h"

StartMenu::StartMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);


}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_pushButtonlevel1_clicked()
{
    hide();

    Level* lvl1 = new Level;

    lvl1->AddTower(600.0f,-10.0f,200.0f,500.0f,1);

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

