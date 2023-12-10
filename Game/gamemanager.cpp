#include "gamemanager.h"
#include <QFile>
#include <QDir>
#include <Box2D/Box2D.h>
#include <QJsonDocument>
#include <QDebug>

GameManager::GameManager(QObject *parent)
        : QObject(parent), m_clientID(QString()), m_clientsInLobby(QStringList()), m_roomLobbyCode(QString()) {
    m_messageHandler = new MessageProcessHandler(this);
    connect(m_messageHandler, &MessageProcessHandler::uniqueIDRegistration, this, &GameManager::registerUniqueID);
    connect(m_messageHandler, &MessageProcessHandler::newLobby, this, &GameManager::lobbyJoined);
    connect(m_messageHandler, &MessageProcessHandler::lobbyListUpdated, this, &GameManager::setClientsInLobby);
    connect(m_messageHandler, &MessageProcessHandler::newLobbyMessage, this, &GameManager::newLobbyMessage);
}

GameManager::~GameManager() {
    m_messageHandler->deleteLater();
}

QString GameManager::roomLobbyCode() {
    return m_roomLobbyCode;
}

QStringList GameManager::clientsInLobby() {
    return m_clientsInLobby;
}

void GameManager::createGameRequest() {
    // Check if there are enough clients in the lobby before starting a game
    int clientsInLobby = 0;
    for (auto state: m_clientStates.values()) {
        if (state == ClientState::InLobby) {
            clientsInLobby++;
        }
    }

    if (clientsInLobby <= 2) {  // Adjust this value based on your game requirements
        emit newMessageReadyToSend("type:createGame;payLoad:0;sender:" + m_clientID);
    }
}

void GameManager::sendRocketLaunchMessage(const b2Vec2 &position, const b2Vec2 &direction) {
    // Convert the position and direction to a string format
    QString message = QString("type:rocketLaunch;position:%1,%2;direction:%3,%4;lobbyID:%5;sender:%6")
            .arg(position.x).arg(position.y).arg(direction.x).arg(direction.y).arg(m_roomLobbyCode).arg(m_clientID);

    // Send the message to the server
    emit newMessageReadyToSend(message);
}


void GameManager::joinLobbyRequest(QString lobbyID) {
    // Update the client's state to InLobby
    m_clientStates[m_clientID] = ClientState::InLobby;
    emit newMessageReadyToSend("type:joinGame;payLoad:" + lobbyID + ";sender:" + m_clientID);
}

void GameManager::sendMessageToLobby(QString message) {
    emit newMessageReadyToSend(
            "type:message;payLoad:" + message + ";lobbyID:" + m_roomLobbyCode + ";sender:" + m_clientID);
}

void GameManager::setRoomLobbyCode(QString lobbyCode) {
    if (m_roomLobbyCode != lobbyCode) {
        m_roomLobbyCode = lobbyCode;
        emit roomLobbyCodeChanged();
    }
}

void GameManager::setClientsInLobby(QStringList clients) {
    if (m_clientsInLobby != clients) {
        m_clientsInLobby = clients;
        emit clientsInLobbyChanged();
    }
}

void GameManager::processSocketMessage(QString message) {
    // Handle game-related messages based on the client's state
    if (m_clientStates[m_clientID] == ClientState::InGame) {
        // Handle game-related messages
    } else {
        m_messageHandler->processMessage(message);
    }
}

void GameManager::registerUniqueID(QString uniqueID) {
    m_clientID = uniqueID;
    m_clientStates[m_clientID] = ClientState::InLobby;
}

void GameManager::lobbyJoined(QString lobbyID, QStringList clients) {
    setRoomLobbyCode(lobbyID);
    setClientsInLobby(clients);
    emit inGameLobby();
}
