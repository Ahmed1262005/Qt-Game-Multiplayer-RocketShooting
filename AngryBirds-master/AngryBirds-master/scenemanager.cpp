#include "scenemanager.h"
#include "material.h"
#include "fixtureitem.h"
#include "terence.h"
#include "redbird.h"
#include "Blocks.h"
#include "piggs.h"
#include <QObject>
#include <QDebug>
#include <QGraphicsPixmapItem>

SceneManager::SceneManager(QGraphicsScene *scene, QGraphicsView *view, QObject *parent)
    :QObject(parent), _scene(scene), _view(view)
{
}

void SceneManager::addItem(QString obj, QGraphicsView *view, QPointF pos)
{

    if(obj == "King")
    {
		Material *material = Material::fromName(obj);
		Piggs *king = new Piggs(pos, material);
		_scene->addItem(king);
		king->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);


    }

    if(obj == "Foreman")
    {
		Material *material = Material::fromName(obj);
		Piggs *foreman = new Piggs(pos, material);
		_scene->addItem(foreman);
		foreman->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

    }

    if(obj == "Professor")
    {
		Material *material = Material::fromName(obj);
		Piggs *professor = new Piggs(pos, material);
		_scene->addItem(professor);
		professor->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

	}

    if(obj == "Fat Pig")
    {
		Material *material = Material::fromName(obj);
		Piggs *fatPig = new Piggs(pos, material);
		_scene->addItem(fatPig);
		fatPig->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

    }

    if(obj == "Corporal Pig")
    {
		Material *material = Material::fromName(obj);
		Piggs *corporal = new Piggs(pos, material);
		_scene->addItem(corporal);
		corporal->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Soldier")
    {
		Material *material = Material::fromName(obj);
		Piggs *soldier = new Piggs(pos, material);
		_scene->addItem(soldier);
		soldier->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

    }

    if(obj == "Strip")
    {
		Material *material = Material::fromName(obj);
		qDebug() << material->name;
        Blocks *strip = new Blocks(pos, material);
		_scene->addItem(strip);
		strip->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }


    if(obj == "Ground1")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *ground1 = new FixtureItem(pos, material);
        _scene->addItem(ground1);
        ground1->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ground2")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *ground2 = new FixtureItem(pos, material);
        _scene->addItem(ground2);
        ground2->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ground3")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *ground3 = new FixtureItem(pos, material);
        _scene->addItem(ground3);
        ground3->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Sky")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *sky = new FixtureItem(pos, material);
        _scene->addItem(sky);
        sky->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Dark Sky")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *darksky = new FixtureItem(pos, material);
        _scene->addItem(darksky);
        darksky->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Red Sky")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *redsky = new FixtureItem(pos, material);
        _scene->addItem(redsky);
        redsky->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Blue Sky")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *bsky = new FixtureItem(pos, material);
        _scene->addItem(bsky);
        bsky->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Cloud1")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *cloud1 = new FixtureItem(pos, material);
        _scene->addItem(cloud1);
        cloud1->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Cloud2")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *cloud2 = new FixtureItem(pos, material);
        _scene->addItem(cloud2);
        cloud2->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Sun")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *sun = new FixtureItem(pos, material);
        _scene->addItem(sun);
        sun->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Satellite")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *satellite =new FixtureItem(pos, material);
        _scene->addItem(satellite);
        satellite->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Hill")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *hill = new FixtureItem(pos, material);
        _scene->addItem(hill);
        hill->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Jungle")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *jungle = new FixtureItem(pos, material);
        _scene->addItem(jungle);
        jungle->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Grass")
    {
        Material *material = Material::fromName(obj);
        FixtureItem *grass = new FixtureItem(pos, material);
        _scene->addItem(grass);
        grass->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Wood Table")
    {
        Material *material = Material::fromName(obj);
        Blocks *woodTable = new Blocks(pos, material);
        _scene->addItem(woodTable);
        woodTable->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Wood Box")
    {
		Material *material = Material::fromName(obj);
        Blocks *woodBox = new Blocks(pos, material);
		_scene->addItem(woodBox);
		woodBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

	}
    if(obj == "Wood VBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *woodVBox = new Blocks(pos, material);
        _scene->addItem(woodVBox);
        woodVBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }


    if(obj == "Wood HBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *woodHBox = new Blocks(pos, material);
        _scene->addItem(woodHBox);
        woodHBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Wood Triangle")
    {
        Material *material = Material::fromName(obj);
        Blocks *woodtriangle = new Blocks(pos, material);
        _scene->addItem(woodtriangle);
        woodtriangle->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Wood Triangle1")
    {
        Material *material = Material::fromName(obj);
        Blocks *woodtriangle1 = new Blocks(pos, material);
        _scene->addItem(woodtriangle1);
        woodtriangle1->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);

    }

    if(obj == "Melon")
    {
        Material *material = Material::fromName(obj);
        Piggs *melon = new Piggs(pos, material);
        _scene->addItem(melon);
        melon->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ice Box")
    {
        Material *material = Material::fromName(obj);
        Blocks *iceBox = new Blocks(pos, material);
        _scene->addItem(iceBox);
        iceBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ice VBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *iceVBox = new Blocks(pos, material);
        _scene->addItem(iceVBox);
        iceVBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ice HBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *iceHBox = new Blocks(pos, material);
        _scene->addItem(iceHBox);
        iceHBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Ice Triangle")
    {
        Material *material = Material::fromName(obj);
        Blocks *icetriangle = new Blocks(pos, material);
        _scene->addItem(icetriangle);
        icetriangle->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Stone Box")
    {
        Material *material = Material::fromName(obj);
        Blocks *stoneBox = new Blocks(pos, material);
        _scene->addItem(stoneBox);
        stoneBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Stone VBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *stoneVBox = new Blocks(pos, material);
        _scene->addItem(stoneVBox);
        stoneVBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }

    if(obj == "Stone HBox")
    {
        Material *material = Material::fromName(obj);
        Blocks *stoneHBox = new Blocks(pos, material);
        _scene->addItem(stoneHBox);
        stoneHBox->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }
    if(obj == "Stone Triangle")
    {
        Material *material = Material::fromName(obj);
        Blocks *stonetriangle = new Blocks(pos, material);
        _scene->addItem(stonetriangle);
        stonetriangle->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable);
    }


}
