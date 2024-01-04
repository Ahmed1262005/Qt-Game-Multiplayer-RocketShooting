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
    this->setWindowTitle("Game Lobby");
    setWindowIcon(QIcon(":/Resources/Images/Title.ico"));


    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStart->setStyleSheet("QPushButton:disabled{ background: transparent; }");

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
    QString usersText = "";

    const QStringList &Clients = m_gameManager->clientsInLobby();
    QList<QString> clients = Clients;
    if (!clients.isEmpty()) {
        for (const QString &id: clients) {
            usersText += "ID: " + id + "\n";
        }
    }
    ui->users->setText(usersText); // Set the users label to the list of users in the lobby from gameManager
    if (Clients.size() > 1) {
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonStart->setStyleSheet("");
    } else {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStart->setStyleSheet("QPushButton:disabled{ background: transparent; }");
    }
}

void ChatLobbyWindow::dataRecieved() {

}


void ChatLobbyWindow::on_pushButtonStart_clicked() {
    MultiplayerMainWindow *multiplayerWindow = new MultiplayerMainWindow(m_gameManager,this);
    multiplayerWindow->showFullScreen();
    this->hide(); // Optionally, hide the current window
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
void ChatLobbyWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    QApplication::quit();
}
