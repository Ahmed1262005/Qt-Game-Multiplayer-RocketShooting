#include "gameitem.h"
#include "mainwindow.h"
#include "obstacles.h"

#include <iostream>

GameItem::GameItem(b2World *world, MainWindow* W) : gBody(NULL),world(world)
{
    window = W;
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

    QPainter painter(window);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw Box2D objects here

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
        b2Vec2 position = body->GetPosition();
        if(body->GetFixtureList()->GetDensity() == OBSTACLE_DENSITY)
        {
            // Adjust the rendering to consider the vertical inversion
            painter.drawPixmap(200,200,QPixmap(":/Resources/Images/tower.png"));
        }
    }

}
