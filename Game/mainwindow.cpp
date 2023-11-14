#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Box2D/Files/b2_shape.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

