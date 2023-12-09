#include "multiplayermainwindow.h"

MultiplayerMainWindow::MultiplayerMainWindow(QWidget *parent)
        : PhysicsWorld(parent)
{
    gameManager = new GameManager(parent);
    // Connect signals and slots between gameManager and this
    connect(gameManager, &GameManager::rocketLaunchMessageReceived, this, &MultiplayerMainWindow::launchOpponentRocket);
}

MultiplayerMainWindow::~MultiplayerMainWindow()
{
    delete gameManager;
}

void MultiplayerMainWindow::createMultiplayerGame()
{
    gameManager->createGameRequest();
}

void MultiplayerMainWindow::launchOpponentRocket(const b2Vec2 &position, const b2Vec2 &direction) {
    // Create a new rocket at a negative x-coordinate
    createRocket(width() - 100.0f, 100.0f); // Adjust the y-coordinate as needed

    // Apply an impulse to the rocket to launch it towards the positive side of the screen

    // Apply a mirrored impulse to the rocket to launch it towards the left side of the screen
    b2Vec2 mirroredDirection = b2Vec2(-direction.x, direction.y);
    rocketBody->ApplyLinearImpulse(mirroredDirection, rocketBody->GetWorldCenter(), true);
}

void MultiplayerMainWindow::joinMultiplayerGame(QString gameID)
{
    gameManager->joinLobbyRequest(gameID);
}

void MultiplayerMainWindow::sendMultiplayerMessage(QString message)
{
    gameManager->sendMessageToLobby(message);
}

void MultiplayerMainWindow::updateWorld() {
    // Implement the game logic for the multiplayer game

    // Call the base class's updateWorld function if needed
    PhysicsWorld::updateWorld();
}
