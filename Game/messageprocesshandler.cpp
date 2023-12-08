#include "messageprocesshandler.h"
#include <QDebug>
#include <qregularexpression.h>


MessageProcessHandler::MessageProcessHandler(QObject *parent) : QObject(parent) {

}

void MessageProcessHandler::processMessage(QString message) {
    //type:uniqueID;payLoad:5555
    //type:newLobbyCreated;payLoad:1111;clientList:1234,4444,5555
    //type:joinSuccess;payLoad:1111;clientList:1234,4444,5555
    //type:updatedClientList;payLoad:1234,4444,5555
    //type:lobbyMesssage;payLoad:" + message + ";sender:" + senderID
    //type:readyListChanged;payLoad:" + existingLobby->whoIsReady()
    //type:gameReadyToBegin;payLoad:0
    //type:drawingInstruction;payLoad:doodleData;instruction:dog
    //type:gameImages;payLoad:fileData1,fileData2,fileData3;clients:1111,2222,3333
    //type:winnerChosen;payLoad:winner
    QStringList separated = message.split(QRegularExpression(";"));
    if (separated.first() == "type:uniqueID") {
        qDebug() << "Client App: unique ID registration";
        //unique ID registration
        separated.pop_front();
        if (separated.first().contains("payLoad:")) {
            QString newClientID = separated.first();
            newClientID = newClientID.remove("payLoad:");
            emit uniqueIDRegistration(newClientID);
        }
    } else if (separated.first() == "type:newLobbyCreated" || separated.first() == "type:joinSuccess") {
        qDebug() << "Client App: Client joined lobby";
        separated.pop_front();
        QString newLobbyID = QString();
        QStringList lobbyClients = QStringList();
        if (separated.first().contains("payLoad:")) {
            newLobbyID = separated.first();
            newLobbyID = newLobbyID.remove("payLoad:");
        }
        separated.pop_front();
        if (separated.first().contains("clientList:")) {
            QString clients = separated.first();
            clients = clients.remove("clientList:");
            lobbyClients = clients.split(QRegularExpression(","));
        }
        qDebug() << "Client App: Clients in lobby: " << lobbyClients;

        if (newLobbyID != QString() && lobbyClients != QStringList())
                emit newLobby(newLobbyID, lobbyClients);
    } else if (separated.first() == "type:updatedClientList") {
        qDebug() << "Client App: Received updated client list";
        separated.pop_front();
        QString payLoad = separated.front();
        payLoad = payLoad.remove("payLoad:");
        emit lobbyListUpdated(payLoad.split(QRegularExpression(",")));
    } else if (separated.first() == "type:lobbyMessage") {
        //type:lobbyMesssage;payLoad:" + message + ";sender:" + senderID
        //senderID: message
        QString newMessage;
        QString senderID;
        separated.pop_front();
        if (separated.front().contains("payLoad:")) {
            newMessage = separated.front();
            newMessage = newMessage.remove("payLoad:");
        }
        separated.pop_front();
        if (separated.front().contains("sender:")) {
            senderID = separated.front();
            senderID = senderID.remove("sender:");
        }
        QString displayMessage(senderID + ": " + newMessage);
        emit newLobbyMessage(displayMessage);
    } else if (message.startsWith("type:rocketLaunch")) {
        // Parse the position and direction from the message
        QRegularExpression rx("position:(\\d+),(\\d+);direction:(\\d+),(\\d+)");
        QRegularExpressionMatch match = rx.match(message);
        if (match.hasMatch()) {
            b2Vec2 position(match.captured(1).toDouble(), match.captured(2).toDouble());
            b2Vec2 direction(match.captured(3).toDouble(), match.captured(4).toDouble());

            // Emit the rocketLaunchMessageReceived signal
            emit rocketLaunchMessageReceived(position, direction);
        }
    }

}
