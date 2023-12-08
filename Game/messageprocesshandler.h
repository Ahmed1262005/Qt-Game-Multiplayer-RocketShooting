#ifndef MESSAGEPROCESSHANDLER_H
#define MESSAGEPROCESSHANDLER_H
#include <Box2D/Box2D.h>
#include <QObject>
#include <QRegularExpression> // Add this include

class MessageProcessHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessHandler(QObject *parent = nullptr);

    void processMessage( QString message );

signals:
    void uniqueIDRegistration( QString uniqueID );
    void newLobby( QString lobbyID, QStringList clients );
    void lobbyListUpdated( QStringList clients );
    void newLobbyMessage( QString message );
    void rocketLaunchMessageReceived(const b2Vec2 &position, const b2Vec2 &direction); // Add this signal

};

#endif // MESSAGEPROCESSHANDLER_H
