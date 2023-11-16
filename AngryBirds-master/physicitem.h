#ifndef PHYSICITEM_H
#define PHYSICITEM_H

#include <QGraphicsItem>
#include <Box2D/Dynamics/b2Body.h>
#include "material.h"
#include "world.h"

class PhysicItem : public QGraphicsItem
{
public:
    enum flagMode{SimulateMode, EditMoade};
public:
	PhysicItem();
	virtual void updateShape();
    virtual void buildItem();
    virtual void reactionToClick();
    void simulating();
    void setMode(PhysicItem::flagMode mode);
    void advance(int phase);
    void setWorld(b2World *world);
    void Simulationstaring();
    void simulationStoping();
	~PhysicItem();

public:
	b2Body *_body;
	double _angle;
    b2World *_world;
    Material *_material;
    flagMode _mode;
    bool _simulated;
    bool _shooted;
protected:
  //  void mousePressEvent(QGraphicsSceneMouseEvent *event);
	
};

#endif // PHYSICITEM_H
