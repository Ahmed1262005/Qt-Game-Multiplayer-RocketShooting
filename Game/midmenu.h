#ifndef MIDMENU_H
#define MIDMENU_H

#include <QDialog>
#include "startmenu.h"
#include "level.h"

class PhysicsWorld;

namespace Ui {
class MidMenu;
}

class MidMenu : public QDialog {
    Q_OBJECT

public:
    // Method to display the score
    void showScore();

    // Setter for setting the levels
    //void setLevels(std::vector<Level*>& levels) { this->levels = levels; }

    // Public member variables
    float score;
    Level* level;
    int currentLevelIndex;

    // Constructors and destructor
    explicit MidMenu(QWidget *parent=nullptr);
    ~MidMenu();

    // Method to get the PhysicsWorld pointer
    void get_window(PhysicsWorld*);

    // Method to get the Level pointer
    // Method to retrieve the next level
    Level* getNextLevel();

    void get_startmenu(StartMenu*);

    void calculate_stars();


private slots:
    // Slots for button clicks
    void on_pushButtonexit_clicked();
    void on_pushButtonretry_clicked();
    void on_pushButtonNextLevel_clicked();

private:
    // Private members
    Ui::MidMenu *ui;
    StartMenu* start;
    PhysicsWorld* main;

};

#endif // MIDMENU_H
