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
//    winoffset = 1;

//    // Adjust the margin of the colored stars image based on the win offset value
//    if (winoffset == 0) {
//        ui->labelYouWin->setVisible(false);
//        ui->labelYouLose->setText("You Lose");
//        ui->pushButtonNextLevel->setVisible(false);
//        ui->labelColoredStars->setMargin(-200); // Set margin for winoffset = 0
//    } else if (winoffset == 1) {
//        // If the score is not 0, display "You Win"
//        ui->labelYouWin->setVisible(true);
//        // Set the text to "You Win"
//        ui->labelYouLose->setVisible(false);
//        ui->labelColoredStars->setMargin(-100); // Set margin for winoffset = 1
//    }
//    // Add handling for other winoffset values if needed
}


MidMenu::~MidMenu()
{
    delete ui; //Delete the window
}

Level* MidMenu::getNextLevel() {
    // Check if there is a next level available in the levels vector

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


    }
}


void MidMenu::get_window(PhysicsWorld* main) {
    // Store the pointer to the PhysicsWorld instance in the class member
    this->main = main;
}



void MidMenu::on_pushButtonretry_clicked() {
    // Hide the main window and this MidMenu window
    main->hide();
    hide();

    // Stop the music and set it to false
    main->setMusicPlayer(false);

    // Create a new StartMenu instance and navigate to level 1


}

void MidMenu::on_pushButtonNextLevel_clicked() {
    // Hide the main window and this MidMenu window
    main->hide();
    hide();

    // Stop the music and set it to false
    main->setMusicPlayer(false);

    // Create a new StartMenu instance and navigate to level 2

}

void MidMenu::get_startmenu(StartMenu* menu)
{
    start = menu;
}

void MidMenu::calculate_stars()
{
     ui->labelYouLose->setVisible(false);
     ui->labelYouWin->setVisible(true);
     float percentage = ((float)main->get_counter()/(float)main->get_winoffset()) * 100;
     if((percentage < 75) && (percentage > 25))
     {
        ui->labelColoredStars->setMargin(-100);
     }
     else if ((percentage <= 25) && (percentage > 0))
     {
        ui->labelColoredStars->setMargin(-200);
     }
     else if(percentage <=0)
     {
        ui->labelColoredStars->setMargin(-300);
        ui->labelYouWin->setVisible(false);
        ui->labelYouLose->setVisible(true);
     }
}
