#ifndef MIDMENU_H
#define MIDMENU_H

#include <QDialog>
#include "startmenu.h"
#include "level.h"

class MainWindow;

namespace Ui {
class MidMenu;
}

class MidMenu : public QDialog {
    Q_OBJECT

public:
    // Method to display the score
    void showScore();

    // Setter for setting the levels
    void setLevels(std::vector<Level*>& levels) { this->levels = levels; }

    // Public member variables
    float score;
    Level* level;
    int currentLevelIndex;

    // Constructors and destructor
    explicit MidMenu(QWidget *parent = nullptr);
    ~MidMenu();

    // Method to get the MainWindow pointer
    void get_window(MainWindow*);

    // Method to get the Level pointer
    void get_level(Level*);

    // Method to retrieve the next level
    Level* getNextLevel();

private slots:
    // Slots for button clicks
    void on_pushButtonexit_clicked();
    void on_pushButtonretry_clicked();
    void on_pushButtonNextLevel_clicked();

private:
    // Private members
    Ui::MidMenu *ui;
    StartMenu* start;
    std::vector<Level*> levels;
    MainWindow* main;
    int winoffset;
};

#endif // MIDMENU_H
