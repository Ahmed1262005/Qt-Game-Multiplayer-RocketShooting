#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world) : gBody(NULL),world(world){
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

void GameItem::paint(){
    b2Vec2 pos = gBody->GetPosition();
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(gBody->GetAngle()*180/3.14159));
}
