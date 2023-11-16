#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logo.h"
#include "simulator.h"
#include "defs.h"
#include "fixtureitem.h"
#include "mycontactlistener.h"
#include "blocks.h"
#include "piggs.h"
#include "physicitem.h"
#include "redbird.h"
#include "material.h"
#include "terence.h"
#include "blue.h"
#include "chunck.h"
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QToolBar>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _bomb = 0;
    _mode = MainWindow::EDITMODE;
    _scene = new QGraphicsScene();
    _manager = new SceneManager(_scene, ui->graphicsView);
    _sceneIsEmpty = true;
    _simulated = false;

    logoitem = new logo();
    logoitem->setZValue(1);
    _scene->addItem(logoitem);
    logoitem->setPos(1000, 200);


    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scale(.75, .75);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(_scene);
    _scene->setSceneRect(0, 0, 10000, 950);

    create_gameMenu_tools();

    Blocks *strip = new Blocks(QPointF(0, 800), new Material("strip", 0.0f, 1.0f, .1f, QPixmap(":/fixture/fixture/strip.png")));
    _scene->addItem(strip);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_gameMenu_tools()
{
    QTreeWidgetItem *characters = new QTreeWidgetItem();
    characters->setText(0 ,"Characters");
    ui->treeWidget->addTopLevelItem(characters);

    QTreeWidgetItem *badPiggies = new QTreeWidgetItem();
    badPiggies->setText(0 ,"Bad Piggies");
    ui->treeWidget->addTopLevelItem(badPiggies);

    QTreeWidgetItem *fixture = new QTreeWidgetItem();
    fixture->setText(0 ,"Fixture");
    ui->treeWidget->addTopLevelItem(fixture);

    QTreeWidgetItem *blocks = new QTreeWidgetItem();
    blocks->setText(0, "Blocks");
    ui->treeWidget->addTopLevelItem(blocks);

    //add characters
    QTreeWidgetItem *red = new QTreeWidgetItem();
    red->setText(0,"Red Bird");
    red->setIcon(0,QIcon(QPixmap(":/actors/Characters/red.png")));
    characters->addChild(red);

    QTreeWidgetItem *blue = new QTreeWidgetItem();
    blue->setText(0,"Blue");
    blue->setIcon(0,QIcon(QPixmap(":/actors/Characters/blue.png")));
    characters->addChild(blue);

    QTreeWidgetItem *chunk = new QTreeWidgetItem();
    chunk->setText(0, "Chunk");
    chunk->setIcon(0, QIcon(QPixmap(":/actors/Characters/chunk.png")));
    characters->addChild(chunk);

    QTreeWidgetItem *hal = new QTreeWidgetItem();
    hal->setText(0,"Hal");
    hal->setIcon(0,QIcon(QPixmap(":/actors/Characters/hal.png")));
    characters->addChild(hal);

    QTreeWidgetItem *matida = new QTreeWidgetItem();
    matida->setText(0,"Matida");
    matida->setIcon(0,QIcon(QPixmap(":/actors/Characters/matida.png")));
    characters->addChild(matida);

    QTreeWidgetItem *bomb = new QTreeWidgetItem();
    bomb->setText(0,"Bomb");
    bomb->setIcon(0,QIcon(QPixmap(":/actors/Characters/Bomb.png")));
    characters->addChild(bomb);

    QTreeWidgetItem *terence = new QTreeWidgetItem();
    terence->setText(0,"Terence");
    terence->setIcon(0,QIcon(QPixmap(":/actors/Characters/terence.png")));
    characters->addChild(terence);

    //add piggs
    QTreeWidgetItem *king = new QTreeWidgetItem();
    king->setText(0, "King");
    king->setIcon(0, QIcon(QPixmap(":/piggs/piggs/king.png")));
    badPiggies->addChild(king);

    QTreeWidgetItem *foreman = new QTreeWidgetItem();
    foreman->setText(0, "Foreman");
    foreman->setIcon(0, QIcon(QPixmap(":/piggs/piggs/foreman.png")));
    badPiggies->addChild(foreman);

    QTreeWidgetItem *professor = new QTreeWidgetItem();
    professor->setText(0, "Professor");
    professor->setIcon(0, QIcon(QPixmap(":/piggs/piggs/professor.png")));
    badPiggies->addChild(professor);

    QTreeWidgetItem *fat_pig = new QTreeWidgetItem();
    fat_pig->setText(0, "Fat Pig");
    fat_pig->setIcon(0, QIcon(QPixmap(":/piggs/piggs/Fat_pig.png")));
    badPiggies->addChild(fat_pig);

    QTreeWidgetItem *corporal = new QTreeWidgetItem();
    corporal->setText(0, "Corporal Pig");
    corporal->setIcon(0, QIcon(QPixmap(":/piggs/piggs/corporal-pig.png")));
    badPiggies->addChild(corporal);

    QTreeWidgetItem *soldier = new QTreeWidgetItem();
    soldier->setText(0, "Soldier");
    soldier->setIcon(0, QIcon(QPixmap(":/piggs/piggs/sodier.png")));
    badPiggies->addChild(soldier);

    //add fixture
    QTreeWidgetItem *strip = new QTreeWidgetItem();
    strip->setText(0, "Strip");
    strip->setIcon(0, QIcon(QPixmap(":/fixture/fixture/strip.png")));
    fixture->addChild(strip);

    QTreeWidgetItem *ground1 = new QTreeWidgetItem();
    ground1->setText(0, "Ground1");
    ground1->setIcon(0, QIcon(QPixmap(":/fixture/fixture/ground1.png")));
    fixture->addChild(ground1);

    QTreeWidgetItem *ground2 = new QTreeWidgetItem();
    ground2->setText(0, "Ground2");
    ground2->setIcon(0, QIcon(QPixmap(":/fixture/fixture/ground2.png")));
    fixture->addChild(ground2);

    QTreeWidgetItem *ground3 = new QTreeWidgetItem();
    ground3->setText(0, "Ground3");
    ground3->setIcon(0, QIcon(QPixmap(":/fixture/fixture/ground3.png")));
    fixture->addChild(ground3);

    QTreeWidgetItem *sky1 = new QTreeWidgetItem();
    sky1->setText(0, "Sky");
    sky1->setIcon(0, QIcon(QPixmap(":/fixture/fixture/sky.png")));
    fixture->addChild(sky1);

    QTreeWidgetItem *sky2 = new QTreeWidgetItem();
    sky2->setText(0, "Dark Sky");
    sky2->setIcon(0, QIcon(QPixmap(":/fixture/fixture/sky3.png")));
    fixture->addChild(sky2);

    QTreeWidgetItem *sky3 = new QTreeWidgetItem();
    sky3->setText(0, "Red Sky");
    sky3->setIcon(0, QIcon(QPixmap(":/fixture/fixture/sky2.png")));
    fixture->addChild(sky3);

    QTreeWidgetItem *sky4 = new QTreeWidgetItem();
    sky4->setText(0, "Blue Sky");
    sky4->setIcon(0, QIcon(QPixmap(":/fixture/fixture/sky4.png")));
    fixture->addChild(sky4);

    QTreeWidgetItem *sun = new QTreeWidgetItem();
    sun->setText(0, "Sun");
    sun->setIcon(0, QIcon(QPixmap(":/fixture/fixture/sun.png")));
    fixture->addChild(sun);

    QTreeWidgetItem *cloud1 = new QTreeWidgetItem();
    cloud1->setText(0, "Cloud1");
    cloud1->setIcon(0, QIcon(QPixmap(":/fixture/fixture/cloude1.png")));
    fixture->addChild(cloud1);

    QTreeWidgetItem *cloud2 = new QTreeWidgetItem();
    cloud2->setText(0, "Cloud2");
    cloud2->setIcon(0, QIcon(QPixmap(":/fixture/fixture/cloude2.png")));
    fixture->addChild(cloud2);

    QTreeWidgetItem *Satellite = new QTreeWidgetItem();
    Satellite->setText(0, "Satellite");
    Satellite->setIcon(0, QIcon(QPixmap(":/fixture/fixture/satellite.png")));
    fixture->addChild(Satellite);

    QTreeWidgetItem *hill_b = new QTreeWidgetItem();
    hill_b->setText(0, "Hill");
    hill_b->setIcon(0, QIcon(QPixmap(":/fixture/fixture/hill_b_s.png")));
    fixture->addChild(hill_b);

    QTreeWidgetItem *grass = new QTreeWidgetItem();
    grass->setText(0, "Grass");
    grass->setIcon(0, QIcon(QPixmap(":/fixture/fixture/grass.png")));
    fixture->addChild(grass);

    QTreeWidgetItem *jungle = new QTreeWidgetItem();
    jungle->setText(0, "Jungle");
    jungle->setIcon(0, QIcon(QPixmap(":/fixture/fixture/jungle.png")));
    fixture->addChild(jungle);

    //add blocks
    QTreeWidgetItem *wood_tb = new QTreeWidgetItem();
    wood_tb->setText(0, "Wood Table");
    wood_tb->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_table.png")));
    blocks->addChild(wood_tb);

    QTreeWidgetItem *wood_rec = new QTreeWidgetItem();
    wood_rec->setText(0, "Wood Box");
    wood_rec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_rec.png")));
    blocks->addChild(wood_rec);

    QTreeWidgetItem *wood_vrec = new QTreeWidgetItem();
    wood_vrec->setText(0, "Wood VBox");
    wood_vrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_vrec.png")));
    blocks->addChild(wood_vrec);

    QTreeWidgetItem *wood_hrec = new QTreeWidgetItem();
    wood_hrec->setText(0, "Wood HBox");
    wood_hrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_hrec.png")));
    blocks->addChild(wood_hrec);

    QTreeWidgetItem *wood_triangle = new QTreeWidgetItem();
    wood_triangle->setText(0, "Wood Triangle");
    wood_triangle->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_triangle.png")));
    blocks->addChild(wood_triangle);

    QTreeWidgetItem *wood_triangle1 = new QTreeWidgetItem();
    wood_triangle1->setText(0, "Wood Triangle1");
    wood_triangle1->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/wood_triangle1.png")));
    blocks->addChild(wood_triangle1);

    QTreeWidgetItem *melon = new QTreeWidgetItem();
    melon->setText(0, "Melon");
    melon->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/melon.png")));
    blocks->addChild(melon);

    QTreeWidgetItem *ice_rec = new QTreeWidgetItem();
    ice_rec->setText(0, "Ice Box");
    ice_rec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/ice_rec.png")));
    blocks->addChild(ice_rec);

    QTreeWidgetItem *ice_vrec = new QTreeWidgetItem();
    ice_vrec->setText(0, "Ice VBox");
    ice_vrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/ice_vrec.png")));
    blocks->addChild(ice_vrec);

    QTreeWidgetItem *ice_hrec = new QTreeWidgetItem();
    ice_hrec->setText(0, "Ice HBox");
    ice_hrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/ice_hrec.png")));
    blocks->addChild(ice_hrec);

    QTreeWidgetItem *ice_triangle = new QTreeWidgetItem();
    ice_triangle->setText(0, "Ice Triangle");
    ice_triangle->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/ice_triangle.png")));
    blocks->addChild(ice_triangle);

    QTreeWidgetItem *stone_rec = new QTreeWidgetItem();
    stone_rec->setText(0, "Stone Box");
    stone_rec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/stone_rec.png")));
    blocks->addChild(stone_rec);

    QTreeWidgetItem *stone_vrec = new QTreeWidgetItem();
    stone_vrec->setText(0, "Stone VBox");
    stone_vrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/stone_vrec.png")));
    blocks->addChild(stone_vrec);

    QTreeWidgetItem *stone_hrec = new QTreeWidgetItem();
    stone_hrec->setText(0, "Stone HBox");
    stone_hrec->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/stone_hrec.png")));
    blocks->addChild(stone_hrec);

    QTreeWidgetItem *stone_triangle = new QTreeWidgetItem();
    stone_triangle->setText(0, "Stone Triangle");
    stone_triangle->setIcon(0, QIcon(QPixmap(":/blocks/Blocks/stone_triangle.png")));
    blocks->addChild(stone_triangle);


}

void MainWindow::createActor(QPointF pos, QString obj)
{

    if(obj == "Red Bird")
    {
        Material *material = Material::fromName(obj);
        RedBird *red = new RedBird(pos, material);
        red->setWorld(_simulator->_world->_world);
        red->buildItem();
        _actors.push_back(red);
        _scene->addItem(red);
    }
    if(obj == "Chunk")
    {
        Material *material = Material::fromName(obj);
        Chunck *chunk = new Chunck(pos, material);
        chunk->setWorld(_simulator->_world->_world);
        chunk->buildItem();
        _actors.push_back(chunk);
        _scene->addItem(chunk);
    }

    if(obj == "Blue")
    {
        Material *material = Material::fromName(obj);
        Blue *blue = new Blue(pos, material);
        blue->setWorld(_simulator->_world->_world);
        blue->buildItem();
        _actors.push_back(blue);
        blue->setScene(_scene);
        _scene->addItem(blue);
    }

    if(obj == "Hal")
    {
        QGraphicsPixmapItem *Hal = _scene->addPixmap(QPixmap(":/actors/Characters/hal.png"));
        Hal->setPos(pos);
        Hal->setFlag(QGraphicsItem::ItemIsMovable);
        Hal->setFlag(QGraphicsItem::ItemIsSelectable);
        Hal->setAcceptedMouseButtons(Qt::LeftButton);

    }

    if(obj == "Matida")
    {
        QGraphicsPixmapItem *Matida = _scene->addPixmap(QPixmap(":/actors/Characters/matida.png"));
        Matida->setPos(pos);
        Matida->setFlag(QGraphicsItem::ItemIsMovable);
        Matida->setFlag(QGraphicsItem::ItemIsSelectable);
        Matida->setAcceptedMouseButtons(Qt::LeftButton);
    }

    if(obj == "Bomb")
    {
        Material *material = Material::fromName(obj);
        Bomb *_bomb = new Bomb(pos, material);
        _bomb->setWorld(_simulator->_world->_world);
        _bomb->buildItem();
        _actors.push_back(_bomb);
        _scene->addItem(_bomb);
    }

    if(obj == "Terence")
    {
        Material *material = Material::fromName(obj);
        Terence *terence = new Terence(pos, material);
        terence->setWorld(_simulator->_world->_world);
        terence->buildItem();
        _actors.push_back(terence);
        _scene->addItem(terence);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(_mode == MainWindow::SHOOTMODE)
    {
        for (int i = 0; i < _actors.size(); i++)
            if(_actors[i]->_shooted == true)
            {
                _actors[i]->reactionToClick();
                _actors[i]->_shooted = false;
            }
    }
    else
    {
        QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->mapFrom(this, event->pos()));
        QString obj = this->ui->treeWidget->currentItem()->text(0);

        qDebug() << event;
        qDebug() << "position:" << pos ;
        qDebug() << "obj" << obj;
        if(_simulated && (obj == "Red Bird" || obj == "Terence" || obj == "Bomb" || obj == "Matida" || obj == "Chunk" || obj == "Hal"|| obj == "Blue"))
            createActor(pos, obj);
        else
            if(!_simulated)
                _manager->addItem(obj, ui->graphicsView, pos);
    }
    if(_sceneIsEmpty)
    {
        _sceneIsEmpty = false;
    }

}

void MainWindow::on_actionSimulate_All_triggered()
{
    if(logoitem)
    {
        _scene->removeItem(logoitem);
        delete logoitem;
    }
    if(!_simulated)
    {
        _simulator = new Simulator(_scene);
        _simulator->simulate();
        _simulated = true;
    }

}

void MainWindow::on_actionStopStartSimulating_triggered()
{
    if(_simulated)
    {
        _simulator->startStopSimulating();
        _simulator->_world->_world->SetContactListener(&myContactListener);
    }

}

void MainWindow::on_actionEdit_Mode_triggered()
{

}

void MainWindow::on_actionSimulate_Mode_triggered()
{
    QList <QGraphicsItem *> items = _scene->items();
    for (int i = 0; i < items.size(); ++i)
    {
        PhysicItem *item = qgraphicsitem_cast<PhysicItem *>(items.at(i));
        item->setMode(PhysicItem::SimulateMode);

    }
    ui->actionEdit_Mode->setEnabled(false);
}

void MainWindow::on_actionShoot_Mode_triggered()
{
    if(_mode == MainWindow::EDITMODE)
    {
        _mode = MainWindow::SHOOTMODE;
        ui->actionShoot_Mode->setText("Edit Mode");
    }
    else
    {
        _mode = MainWindow::EDITMODE;
        ui->actionShoot_Mode->setText("Shoot Mode");
    }

}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->graphicsView->scale(1.1, 1.1);

}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->graphicsView->scale(0.9, 0.9);

}




