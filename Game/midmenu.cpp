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

    showScore();
    setWindowFlags(Qt::Window
                   | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);
}

MidMenu::~MidMenu()
{
    delete ui;
}

Level* MidMenu::getNextLevel() {
    if (currentLevelIndex + 1 < levels.size()) {
        return levels[++currentLevelIndex];
    }
    return nullptr; // or handle this case as you see fit
}
void MidMenu::on_pushButtonexit_clicked()
{
    main ->hide();

    hide();

    main->setMusicPlayer(false);

    start = new StartMenu;

    start->showFullScreen();

}
void MidMenu::showScore() {
    if (score == 0) {
        ui->labelYouLose->setText("You Lose");
        ui->pushButtonNextLevel->setVisible(false);
    } else {
        ui->labelYouLose->setText("You Win");
//        ui->pushButtonretry->setVisible(false);

        // Set the width of the stars image to the score


        // Calculate the width of the stars image based on the score
        int totalWidth = ui->labelBlackStars->width();
        int starsWidth = static_cast<int>(score / 100.0 * totalWidth); // Adjust this calculation as needed

        // Clip the colored stars image
        QPixmap coloredStarsPixmap(":/Resources/Images/coloredStars.png");
        QPixmap clippedPixmap = coloredStarsPixmap.copy(0, 0, starsWidth, coloredStarsPixmap.height());

        // Set the clipped image to the label
        ui->labelColoredStars->setPixmap(clippedPixmap);
    }
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

