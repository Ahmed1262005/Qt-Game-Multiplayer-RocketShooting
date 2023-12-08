#ifndef MULTIPLAYERMAINWINDOW_H
#define MULTIPLAYERMAINWINDOW_H
#include "mainwindow.h"
#include "gamemanager.h"
#include <QWidget>

namespace Ui {
class MultiplayerMainWindow;
}
class MultiplayerMainWindow : public MainWindow
{
Q_OBJECT

public:
    MultiplayerMainWindow(QWidget *parent = nullptr);
    ~MultiplayerMainWindow();

    // Add functions for the multiplayer game
    void createMultiplayerGame();
    void joinMultiplayerGame(QString gameID);
    void sendMultiplayerMessage(QString message);

private:
    GameManager *gameManager; // Add a GameManager instance for handling multiplayer game logic
};
#endif // MULTIPLAYERMAINWINDOW_H
