#ifndef MULTIPLAYERMAINWINDOW_H
#define MULTIPLAYERMAINWINDOW_H
#include "PhysicsWorld.h"
#include "gamemanager.h"
#include <QWidget>

namespace Ui {
class MultiplayerMainWindow;
}
class MultiplayerMainWindow : public PhysicsWorld
{
Q_OBJECT

public:
    MultiplayerMainWindow(QWidget *parent = nullptr);
    ~MultiplayerMainWindow();

    // Add functions for the multiplayer game
    void createMultiplayerGame();
    void joinMultiplayerGame(QString gameID);
    void sendMultiplayerMessage(QString message);
    void launchOpponentRocket(const b2Vec2 &position, const b2Vec2 &direction); // Add this method


protected:
    void updateWorld() ; // Override the updateWorld
private:
    GameManager *gameManager; // Add a GameManager instance for handling multiplayer game logic
};
#endif // MULTIPLAYERMAINWINDOW_H
