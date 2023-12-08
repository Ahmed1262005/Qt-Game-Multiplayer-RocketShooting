#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "messageprocesshandler.h"

class GameManager : public QObject
{
Q_OBJECT
    Q_PROPERTY(QString roomLobbyCode READ roomLobbyCode WRITE setRoomLobbyCode NOTIFY roomLobbyCodeChanged)
    Q_PROPERTY(QStringList clientsInLobby READ clientsInLobby WRITE setClientsInLobby NOTIFY clientsInLobbyChanged)

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    QString roomLobbyCode();
    QStringList clientsInLobby();

    enum class ClientState { InLobby, InGame };

    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinLobbyRequest( QString lobbyID );
    Q_INVOKABLE void sendMessageToLobby( QString message );

public slots:
    void setRoomLobbyCode( QString lobbyCode );
    void setClientsInLobby( QStringList clientList );

    void processSocketMessage( QString message);
    void registerUniqueID( QString uniqueID );

    void lobbyJoined( QString lobbyID, QStringList clients );

signals:
    void roomLobbyCodeChanged();
    void clientsInLobbyChanged();
    void newMessageReadyToSend( QString message );
    void inGameLobby();
    void newLobbyMessage( QString message );

private:
    QString m_clientID;
    QStringList m_clientsInLobby;
    QString m_roomLobbyCode;
    QMap<QString, ClientState> m_clientStates;
    MessageProcessHandler * m_messageHandler;
};

#endif // GAMEMANAGER_H