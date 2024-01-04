#ifndef CHATLOBBYWINDOW_H
#define CHATLOBBYWINDOW_H

#include <QDialog>
#include <QWidget>
#include "gamemanager.h"
#include "messageprocesshandler.h"

namespace Ui {
    class ChatLobbyWindow;
}

class ChatLobbyWindow : public QDialog
        {
Q_OBJECT

public:
    explicit ChatLobbyWindow(GameManager *gameManager, QWidget *parent = nullptr);
    ~ChatLobbyWindow();

    void setMessage(QString message, bool isMyMessage = false);
    void updateStartButton();

private slots:
    void dataRecieved();
    void on_pushButtonStart_clicked();
    void on_pushButtonSendMessage_clicked();
    void onNewMessageReadyForProcessing(QString message);

private:
    Ui::ChatLobbyWindow *ui;
    GameManager *m_gameManager;
    MessageProcessHandler *m_messageHandler;
protected:
    void closeEvent(QCloseEvent *event) override; // Add this line
};
#endif // CHATLOBBYWINDOW_H