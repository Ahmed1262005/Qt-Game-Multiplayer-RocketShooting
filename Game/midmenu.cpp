#include "midmenu.h"
#include "ui_midmenu.h"
#include "PhysicsWorld.h"
#include "startmenu.h"

MidMenu::MidMenu(QWidget *parent):
    QDialog(parent),
    ui(new Ui::MidMenu)
{
    ui->setupUi(this);

    // Set background image for the menu
    ui->labelBackground->setPixmap(QPixmap(":/Resources/Images/lobbyBackground2jpg.jpg"));

    // Set window flags for the dialog
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // Set black stars image on the menu
    ui->labelBlackStars->setPixmap(QPixmap(":/Resources/Images/blackStars.png").scaled(300, 100));

    // Set colored stars image on the menu
    ui->labelColoredStars->setPixmap(QPixmap(":/Resources/Images/coloredStars.png").scaled(300, 100));

    // Set the win offset to a default value (1 in this case)
    winoffset = 1;

    // Adjust the margin of the colored stars image based on the win offset value
    if (winoffset == 0) {
        ui->labelYouWin->setVisible(false);
        ui->labelYouLose->setText("You Lose");
        ui->pushButtonNextLevel->setVisible(false);
        ui->labelColoredStars->setMargin(-200); // Set margin for winoffset = 0
    } else if (winoffset == 1) {
        // If the score is not 0, display "You Win"
        ui->labelYouWin->setVisible(true);
        // Set the text to "You Win"
        ui->labelYouLose->setVisible(false);
        ui->labelColoredStars->setMargin(-100); // Set margin for winoffset = 1
    }
    // Add handling for other winoffset values if needed
}


MidMenu::~MidMenu()
{
    delete ui; //Delete the window
}

Level* MidMenu::getNextLevel() {
    // Check if there is a next level available in the levels vector
    if (currentLevelIndex + 1 < levels.size()) {
        // If yes, increment the current level index and return the next level
        return levels[++currentLevelIndex];
    }
    // If no next level is available, return nullptr (or handle the case based on your application's logic)
    return nullptr;
}

void MidMenu::on_pushButtonexit_clicked()
{
    // Hide the main window and the current dialog window
    main->hide();
    hide();

    // Stop the music player associated with the main window
    main->setMusicPlayer(false);

    // Create a new instance of the StartMenu and display it in full screen
    start = new StartMenu;
    start->showFullScreen();
}

void MidMenu::showScore() {
    if (score == 0) {
        // If the score is 0, display "You Lose" and hide the Next Level button
        ui->labelYouWin->setVisible(false);
        ui->labelYouLose->setText("You Lose");
        ui->pushButtonNextLevel->setVisible(false);
    } else {
        // If the score is not 0, display "You Win"
         ui->labelYouWin->setVisible(true);
        // Set the text to "You Win"
        ui->labelYouLose->setVisible(false);

//        // Calculate the width of the stars image based on the score
//        int totalWidth = ui->labelBlackStars->width();
//        int starsWidth = static_cast<int>(score / 100.0 * totalWidth); // Calculate the width of stars based on the score

//        // Clip the colored stars image based on the calculated width
//        QPixmap coloredStarsPixmap(":/Resources/Images/coloredStars.png");
//        QPixmap clippedPixmap = coloredStarsPixmap.copy(0, 0, starsWidth, coloredStarsPixmap.height());

//        // Set the clipped image to the label for colored stars
//        ui->labelColoredStars->setPixmap(clippedPixmap);
    }
}


void MidMenu::get_window(PhysicsWorld* main) {
    // Store the pointer to the PhysicsWorld instance in the class member
    this->main = main;
}

void MidMenu::get_level(Level* level) {
    // Store the pointer to the Level instance in the class member
    this->level = level;
}

void MidMenu::on_pushButtonretry_clicked() {
    // Hide the main window and this MidMenu window
    main->hide();
    hide();

    // Stop the music and set it to false
    main->setMusicPlayer(false);

    // Create a new StartMenu instance and navigate to level 1
    StartMenu start;
    start.on_pushButtonlevel1_clicked();
}

void MidMenu::on_pushButtonNextLevel_clicked() {
    // Hide the main window and this MidMenu window
    main->hide();
    hide();

    // Stop the music and set it to false
    main->setMusicPlayer(false);

    // Create a new StartMenu instance and navigate to level 2
    StartMenu start;
    start.on_pushButtonlevel2_clicked();
}

