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
    explicit MidMenu(QWidget *parent = nullptr);
    ~MidMenu();
    void get_window(MainWindow*);

    void get_level(Level*);

private slots:
    void on_pushButtonexit_clicked();

    void on_pushButtonretry_clicked();

private:
    Ui::MidMenu *ui;

    StartMenu* start;

    MainWindow* main;

    Level* level;
};

#endif // MIDMENU_H
