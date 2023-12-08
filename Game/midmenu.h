#ifndef MIDMENU_H
#define MIDMENU_H

#include <QDialog>
#include "startmenu.h"
#include "level.h"

class MainWindow;


namespace Ui {
class MidMenu;
}

class MidMenu : public QDialog
{
    Q_OBJECT

public:
    void showScore(); // Add this method

    void setLevels(std::vector<Level*>& levels) { this->levels = levels; }
    float score;
    void setCurrentLevelIndex(int index) { this->currentLevelIndex = index; }
    Level* getNextLevel();

    explicit MidMenu(QWidget *parent = nullptr);
    ~MidMenu();
    void get_window(MainWindow*);

    void get_level(Level*);
    Level* level;
    int currentLevelIndex;



private slots:
    void on_pushButtonexit_clicked();

    void on_pushButtonretry_clicked();

    void on_pushButtonNextLevel_clicked();

private:
    Ui::MidMenu *ui;

    StartMenu* start;
    std::vector<Level*> levels;

    MainWindow* main;

};

#endif // MIDMENU_H
