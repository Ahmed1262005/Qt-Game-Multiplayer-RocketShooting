/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSimulate_All;
    QAction *actionStopStartSimulating;
    QAction *actionEdit_Mode;
    QAction *actionSimulate_Mode;
    QAction *actionShoot_Mode;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuMode;
    QMenu *menuSimulating;
    QMenu *menuGame_Test;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        actionSimulate_All = new QAction(MainWindow);
        actionSimulate_All->setObjectName("actionSimulate_All");
        actionStopStartSimulating = new QAction(MainWindow);
        actionStopStartSimulating->setObjectName("actionStopStartSimulating");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/zoom/icon/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStopStartSimulating->setIcon(icon);
        actionEdit_Mode = new QAction(MainWindow);
        actionEdit_Mode->setObjectName("actionEdit_Mode");
        actionSimulate_Mode = new QAction(MainWindow);
        actionSimulate_Mode->setObjectName("actionSimulate_Mode");
        actionShoot_Mode = new QAction(MainWindow);
        actionShoot_Mode->setObjectName("actionShoot_Mode");
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName("actionZoom_in");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/zoom/icon/zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon1);
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName("actionZoom_out");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/zoom/icon/zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setMinimumSize(QSize(40, 40));
        treeWidget->setIconSize(QSize(40, 40));
        splitter->addWidget(treeWidget);
        graphicsView = new QGraphicsView(splitter);
        graphicsView->setObjectName("graphicsView");
        splitter->addWidget(graphicsView);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName("menuMode");
        menuSimulating = new QMenu(menuBar);
        menuSimulating->setObjectName("menuSimulating");
        menuGame_Test = new QMenu(menuBar);
        menuGame_Test->setObjectName("menuGame_Test");
        menuView = new QMenu(menuBar);
        menuView->setObjectName("menuView");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMode->menuAction());
        menuBar->addAction(menuSimulating->menuAction());
        menuBar->addAction(menuGame_Test->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuMode->addAction(actionEdit_Mode);
        menuMode->addAction(actionSimulate_Mode);
        menuSimulating->addAction(actionSimulate_All);
        menuSimulating->addAction(actionStopStartSimulating);
        menuGame_Test->addAction(actionShoot_Mode);
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        mainToolBar->addAction(actionStopStartSimulating);
        mainToolBar->addAction(actionZoom_in);
        mainToolBar->addAction(actionZoom_out);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSimulate_All->setText(QCoreApplication::translate("MainWindow", "Simulate All", nullptr));
        actionStopStartSimulating->setText(QCoreApplication::translate("MainWindow", "StopStartSimulating", nullptr));
        actionEdit_Mode->setText(QCoreApplication::translate("MainWindow", "Edit Mode", nullptr));
#if QT_CONFIG(shortcut)
        actionEdit_Mode->setShortcut(QCoreApplication::translate("MainWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSimulate_Mode->setText(QCoreApplication::translate("MainWindow", "Simulate Mode", nullptr));
        actionShoot_Mode->setText(QCoreApplication::translate("MainWindow", "Shoot Mode", nullptr));
#if QT_CONFIG(shortcut)
        actionShoot_Mode->setShortcut(QCoreApplication::translate("MainWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_in->setText(QCoreApplication::translate("MainWindow", "Zoom in", nullptr));
        actionZoom_out->setText(QCoreApplication::translate("MainWindow", "Zoom out", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Objects", nullptr));
        menuMode->setTitle(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        menuSimulating->setTitle(QCoreApplication::translate("MainWindow", "Simulating", nullptr));
        menuGame_Test->setTitle(QCoreApplication::translate("MainWindow", "Game Test", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
