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

    main->hide();
    hide();

    // Stop the music player associated with the main window
    main->setMusicPlayer(false);
    start->showFullScreen();
    if(ui->labelYouWin->isVisible() == false)

    {
    // Hide the main window and the current dialog window


    // Create a new instance of the StartMenu and display it in full screen
    int counter = main->get_currentlevelindex();
    for(int i = 0; i < counter+1; i++)
    {
        start->getLevels()[i]->set_unlocked(true);
        start->renderer_stars();
    }


    for(int i = 0; i < counter+2; i++)
    {
        start->getLevels()[i]->set_unlocked(true);

    }

    start->renderer_unlocked();


    }
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

    StartMenu* menu2 = new StartMenu;
    if (main->get_currentlevelindex() == 0) {
        menu2->on_pushButtonlevel1_clicked();
    } else if (main->get_currentlevelindex() == 1) {
        menu2->on_pushButtonlevel2_clicked();
    } else if (main->get_currentlevelindex() == 2) {
        menu2->on_pushButtonlevel3_clicked();
    } else if (main->get_currentlevelindex() == 3) {
        menu2->on_pushButtonlevel4_clicked();
    } else if (main->get_currentlevelindex() == 4) {
        menu2->on_pushButtonlevel5_clicked();
    } else if (main->get_currentlevelindex() == 5) {
        menu2->on_pushButtonlevel6_clicked();
    } else if (main->get_currentlevelindex() == 6) {
        menu2->on_pushButtonlevel7_clicked();
    } else if (main->get_currentlevelindex() == 7) {
        menu2->on_pushButtonlevel8_clicked();
    } else if (main->get_currentlevelindex() == 8) {
        menu2->on_pushButtonlevel9_clicked();
    } else if (main->get_currentlevelindex() == 9) {
        menu2->on_pushButtonlevel10_clicked();}
    // Create a new StartMenu instance and navigate to level 1


}

void MidMenu::on_pushButtonNextLevel_clicked() {
    // Hide the main window and this MidMenu window
    main->hide();
    hide();

    // Stop the music and set it to false
    main->setMusicPlayer(false);

    if(ui->labelYouWin->isVisible() == false)

    {
        // Hide the main window and the current dialog window


        // Create a new instance of the StartMenu and display it in full screen
        int counter = main->get_currentlevelindex();



        for(int i = 0; i < counter+2; i++)
        {
        start->getLevels()[i]->set_unlocked(true);
        }

        start->renderer_unlocked();

        if (main->get_currentlevelindex() == 0) {
        start->on_pushButtonlevel2_clicked();
        } else if (main->get_currentlevelindex() == 1) {
        start->on_pushButtonlevel3_clicked();
        } else if (main->get_currentlevelindex() == 2) {
        start->on_pushButtonlevel4_clicked();
        } else if (main->get_currentlevelindex() == 3) {
        start->on_pushButtonlevel5_clicked();
        } else if (main->get_currentlevelindex() == 4) {
        start->on_pushButtonlevel6_clicked();
        } else if (main->get_currentlevelindex() == 5) {
        start->on_pushButtonlevel7_clicked();
        } else if (main->get_currentlevelindex() == 6) {
        start->on_pushButtonlevel8_clicked();
        } else if (main->get_currentlevelindex() == 7) {
        start->on_pushButtonlevel9_clicked();
        } else if (main->get_currentlevelindex() == 8) {
        start->on_pushButtonlevel10_clicked();
        }


    }


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
     if((percentage <= 80) && (percentage > 25))
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
