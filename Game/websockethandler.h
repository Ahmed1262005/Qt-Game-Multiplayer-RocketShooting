#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>

#include "messageprocesshandler.h"

class WebSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

    Q_INVOKABLE void connectToServer( QString hostAddress );

public slots:
    void onConnected();
    void onTextMessageReceived( QString message );
    void sendMessageToServer( QString message );

signals:
    void newMessageReadyForProcessing( QString message );

private:
    QWebSocket * m_webSocket;

};

#endif // WEBSOCKETHANDLER_H
