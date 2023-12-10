#include "chatlobbywindow.h"
#include "ui_chatlobbywindow.h"
#include <QString>
#include <QList>
#include "multiplayermainwindow.h"

ChatLobbyWindow::ChatLobbyWindow(GameManager *gameManager, QWidget *parent)
        : QDialog(parent), ui(new Ui::ChatLobbyWindow), m_gameManager(gameManager),
          m_messageHandler(new MessageProcessHandler(this)) {
    ui->setupUi(this); // Uncomment this line
//    ui->lobbyId->setText(
    ui->lobbyId->setText(
            m_gameManager->roomLobbyCode()); // Set the lobbyId label to the current lobbyId from gameManager
    QString usersText = "";
    QList<QString> clients = m_gameManager->clientsInLobby();
    if (!clients.isEmpty()) {
        for (const QString &id: clients) {
            usersText += "ID: " + id + "\n";
        }
    }
    ui->users->setText(usersText); // Set the users label to the list of users in the lobby from gameManager
//
//    // Connect the newLobbyMessage signal from the message handler to the onNewMessageReadyForProcessing slot
    connect(m_gameManager, &GameManager::newLobbyMessage, this,
            &ChatLobbyWindow::onNewMessageReadyForProcessing);
    connect(m_gameManager, &GameManager::clientsInLobbyChanged, this, &ChatLobbyWindow::updateStartButton);
}

ChatLobbyWindow::~ChatLobbyWindow() {
    delete ui;
}

void ChatLobbyWindow::updateStartButton() {
    if (m_gameManager->clientsInLobby().size() > 1) {
        ui->pushButtonStart->setEnabled(true);
    } else {
        ui->pushButtonStart->setEnabled(false);
    }
}
void ChatLobbyWindow::dataRecieved() {

}


void ChatLobbyWindow::on_pushButtonStart_clicked() {
//    MultiplayerMainWindow *multiplayerWindow = new MultiplayerMainWindow(this);
//    multiplayerWindow->show();
//    this->hide(); // Optionally, hide the current window
}

void ChatLobbyWindow::on_pushButtonSendMessage_clicked() {
    if (ui->lineEdit) {
        QString message = ui->lineEdit->text();
        m_gameManager->sendMessageToLobby(message);
        ui->lineEdit->setText("");
    }
}

void ChatLobbyWindow::onNewMessageReadyForProcessing(QString message) {
    if (ui && ui->messages) {
        QString currentText = ui->messages->text();
        currentText += message + "\n";
        ui->messages->setText(currentText);
    }
}
