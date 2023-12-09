// #include "chatlobbywindow.h"
// #include "ui_chatlobbywindow.h"

// #include <QTime>

// ChatLobbyWindow::ChatLobbyWindow(QWidget *parent)
//     : QWidget(parent)
//     , ui(new Ui::ChatLobbyWindow)
// {
//     ui->setupUi(this);
// }

// ChatLobbyWindow::~ChatLobbyWindow()
// {
//     delete ui;
// }

// void ChatLobbyWindow::setMessage(QString message, bool isMyMessage)
// {
//     if(isMyMessage)
//         ui->lineEditMessage->setAlignment(Qt::AlignRight);

//     ui->lineEditMessage->setText(message);
//     ui->lineEditMessage->setText(QTime::currentTime().toString("HH:mm"));
// }
