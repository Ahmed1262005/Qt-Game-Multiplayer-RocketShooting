#include "gameitem.h"
#include "mainwindow.h"


#include <iostream>

GameItem::GameItem(b2World *world) : gBody(NULL),world(world)
{

}

GameItem::~GameItem(){
    world->DestroyBody(gBody);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize){
    worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::paint()
{




}
