#include "physicitem.h"
#include "defs.h"
#include <QPointF>
#include <QDebug>

PhysicItem::PhysicItem()
{

}

PhysicItem::~PhysicItem()
{

}

//void PhysicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(_mode == PhysicItem::SimulateMode && !_simulated)
//    {
//        _simulated = true;
//    }

//}

void PhysicItem::updateShape()
{

}

void PhysicItem::buildItem()
{

}

void PhysicItem::reactionToClick()
{

}

void PhysicItem::simulating()
{
    buildItem();

}

void PhysicItem::setMode(PhysicItem::flagMode mode)
{
    _mode = mode;
}

void PhysicItem::advance( int phase )
{
    if (!phase) return;
    if(_simulated)
    {
        if(_material->name == "strip" || _material->name == "king"
                || _material->name == "foreman" || _material->name == "professor"
                || _material->name == "fat pig" || _material->name == "corporal pig"
                || _material->name == "soldier" || _material->name == "wood table"
                || _material->name == "wood hbox" || _material->name == "ice hbox"
                || _material->name == "stone hbox" || _material->name == "wood box"
                || _material->name == "stone box" || _material->name == "ice box"
                || _material->name == "wood vbox" || _material->name == "ice vbox"
                || _material->name == "stone vbox"|| _material->name == "melon")


        {
            b2Vec2 p = _body->GetPosition();
            _angle = _body->GetAngle();
            setPos(p.x*RATIO-boundingRect().width()/2.0, -(p.y*RATIO+boundingRect().height()/2.0));
            setRotation(-(_angle * 360.0) / (2 * PI));
        }

        if(_material->name == "wood triangle" )
        {
            b2Vec2 p = _body->GetPosition();
            _angle = _body->GetAngle();
            setPos(p.x*RATIO, -(p.y*RATIO));
            setRotation(-(_angle * 360.0) / (2 * PI));
        }

        if(_material->name == "wood triangle_1" || _material->name == "ice triangle" || _material->name == "stone triangle")
        {
            b2Vec2 p = _body->GetPosition();
            _angle = _body->GetAngle();
            setPos(p.x*RATIO, -(p.y*RATIO));
            setRotation(-(_angle * 360.0) / (2 * PI));

        }
    }
}

void PhysicItem::setWorld(b2World *world)
{
    _world = world;
}

void PhysicItem::Simulationstaring()
{
    _simulated = true;

}

void PhysicItem::simulationStoping()
{
    _simulated = false;

}


