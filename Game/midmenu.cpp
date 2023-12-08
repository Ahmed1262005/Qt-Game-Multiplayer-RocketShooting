#include "midmenu.h"
#include "ui_midmenu.h"
#include "mainwindow.h"
#include "startmenu.h"

MidMenu::MidMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MidMenu)
{
    ui->setupUi(this);
    ui->labelBackground->setPixmap(QPixmap(":/Resources/Images/Level3.png"));
    ui->labelBlackStars->setPixmap(QPixmap(":/Resources/Images/blackStars.png"));
    ui->labelColoredStars->setPixmap(QPixmap(":/Resources/Images/coloredStars.png"));


    setWindowFlags(Qt::Window
                   | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);
}

MidMenu::~MidMenu()
{
    delete ui;
}

void MidMenu::on_pushButtonexit_clicked()
{
    main ->hide();

    hide();

    main->setMusicPlayer(false);

    start = new StartMenu;

    start->showFullScreen();

}

void MidMenu::get_window(MainWindow* main)
{
    this->main = main;
}

void MidMenu::on_pushButtonretry_clicked()
{
    main->hide();

    hide();

    main->setMusicPlayer(false);

    StartMenu start;

    start.on_pushButtonlevel1_clicked();
}

void MidMenu::get_level(Level* level)
{
    this->level = level;
}

void MidMenu::on_pushButtonNextLevel_clicked()
{
    main->hide();

    main->setMusicPlayer(false);

    hide();

    StartMenu start;

    start.on_pushButtonlevel2_clicked();
}

