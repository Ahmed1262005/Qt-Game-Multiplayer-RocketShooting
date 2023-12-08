#include "multiplayermainwindow.h"

MultiplayerMainWindow::MultiplayerMainWindow(QWidget *parent)
        : MainWindow(parent)
{
    gameManager = new GameManager(this);
    // Connect signals and slots between gameManager and this
}

MultiplayerMainWindow::~MultiplayerMainWindow()
{
    delete gameManager;
}

void MultiplayerMainWindow::createMultiplayerGame()
{
    gameManager->createGameRequest();
}

void MultiplayerMainWindow::joinMultiplayerGame(QString gameID)
{
    gameManager->joinLobbyRequest(gameID);
}

void MultiplayerMainWindow::sendMultiplayerMessage(QString message)
{
    gameManager->sendMessageToLobby(message);
}