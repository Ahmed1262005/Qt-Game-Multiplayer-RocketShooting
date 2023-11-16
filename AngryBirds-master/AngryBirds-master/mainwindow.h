#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QVector>
#include "scenemanager.h"
#include "mycontactlistener.h"
#include "myquerycallback.h"
#include "simulator.h"
#include "bomb.h"
#include "logo.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum ENMode {SHOOTMODE, EDITMODE};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);


private:
   Ui::MainWindow *ui;
   QVector <PhysicItem *> _actors;
   SceneManager *_manager;
   QGraphicsScene *_scene;
   Bomb *_bomb;
   Simulator *_simulator;
   logo *logoitem;
   MyQueryCallBack queryCallBack;
   MyContactListener myContactListener;
   bool _sceneIsEmpty;
   bool _simulated;
   ENMode _mode;
private:
   void create_gameMenu_tools();
   void createActor(QPointF pos, QString obj);


private slots:
    void on_actionSimulate_All_triggered();

    void on_actionStopStartSimulating_triggered();

    void on_actionEdit_Mode_triggered();

    void on_actionSimulate_Mode_triggered();

    void on_actionShoot_Mode_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

};

#endif // MAINWINDOW_H
