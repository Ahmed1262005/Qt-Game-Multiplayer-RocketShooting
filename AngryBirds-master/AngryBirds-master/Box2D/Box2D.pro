QT -= core \
      gui \
	  webkit

TEMPLATE = lib

CONFIG += debug staticlib warn_on
#CONFIG += release staticlib warn_off
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O3 -march=native -mtune=native -fomit-frame-pointer

DESTDIR = lib
MOC_DIR = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += ..

HEADERS += Box2D.h \
	Collision/b2BroadPhase.h \
	Collision/b2Collision.h \
	Collision/b2Distance.h \
	Collision/b2DynamicTree.h \
	Collision/b2TimeOfImpact.h \
	Collision/Shapes/b2CircleShape.h \
	Collision/Shapes/b2EdgeShape.h \
	Collision/Shapes/b2ChainShape.h \
	Collision/Shapes/b2PolygonShape.h \
	Collision/Shapes/b2Shape.h \
	Common/b2BlockAllocator.h \
	Common/b2Draw.h \
	Common/b2GrowableStack.h \
	Common/b2Math.h \
	Common/b2Settings.h \
	Common/b2StackAllocator.h \
	Common/b2Timer.h \
	Dynamics/b2Body.h \
	Dynamics/b2ContactManager.h \
	Dynamics/b2Fixture.h \
	Dynamics/b2Island.h \
	Dynamics/b2TimeStep.h \
	Dynamics/b2World.h \
	Dynamics/b2WorldCallbacks.h \
	Dynamics/Contacts/b2CircleContact.h \
	Dynamics/Contacts/b2Contact.h \
	Dynamics/Contacts/b2ContactSolver.h \
	Dynamics/Contacts/b2PolygonAndCircleContact.h \
	Dynamics/Contacts/b2EdgeAndCircleContact.h \
	Dynamics/Contacts/b2EdgeAndPolygonContact.h \
	Dynamics/Contacts/b2ChainAndCircleContact.h \
	Dynamics/Contacts/b2ChainAndPolygonContact.h \
	Dynamics/Contacts/b2PolygonContact.h \
	Dynamics/Joints/b2DistanceJoint.h \
	Dynamics/Joints/b2FrictionJoint.h \
	Dynamics/Joints/b2GearJoint.h \
	Dynamics/Joints/b2Joint.h \
	Dynamics/Joints/b2MouseJoint.h \
	Dynamics/Joints/b2PrismaticJoint.h \
	Dynamics/Joints/b2PulleyJoint.h \
	Dynamics/Joints/b2RevoluteJoint.h \
	Dynamics/Joints/b2RopeJoint.h \
	Dynamics/Joints/b2WeldJoint.h \
	Dynamics/Joints/b2WheelJoint.h \
	Dynamics/Joints/b2MotorJoint.h \
	Rope/b2Rope.h


SOURCES += Collision/b2BroadPhase.cpp \
	Collision/b2CollideCircle.cpp \
	Collision/b2CollideEdge.cpp \
	Collision/b2CollidePolygon.cpp \
	Collision/b2Collision.cpp \
	Collision/b2Distance.cpp \
	Collision/b2DynamicTree.cpp \
	Collision/b2TimeOfImpact.cpp \
	Collision/Shapes/b2CircleShape.cpp \
	Collision/Shapes/b2EdgeShape.cpp \
	Collision/Shapes/b2ChainShape.cpp \
	Collision/Shapes/b2PolygonShape.cpp \
	Common/b2BlockAllocator.cpp \
	Common/b2Draw.cpp \
	Common/b2Math.cpp \
	Common/b2Settings.cpp \
	Common/b2StackAllocator.cpp \
	Common/b2Timer.cpp \
	Dynamics/b2Body.cpp \
	Dynamics/b2ContactManager.cpp \
	Dynamics/b2Fixture.cpp \
	Dynamics/b2Island.cpp \
	Dynamics/b2World.cpp \
	Dynamics/b2WorldCallbacks.cpp \
	Dynamics/Contacts/b2CircleContact.cpp \
	Dynamics/Contacts/b2Contact.cpp \
	Dynamics/Contacts/b2ContactSolver.cpp \
	Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
	Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
	Dynamics/Contacts/b2ChainAndCircleContact.cpp \
	Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
	Dynamics/Contacts/b2PolygonContact.cpp \
	Dynamics/Joints/b2DistanceJoint.cpp \
	Dynamics/Joints/b2FrictionJoint.cpp \
	Dynamics/Joints/b2GearJoint.cpp \
	Dynamics/Joints/b2Joint.cpp \
	Dynamics/Joints/b2MouseJoint.cpp \
	Dynamics/Joints/b2PrismaticJoint.cpp \
	Dynamics/Joints/b2PulleyJoint.cpp \
	Dynamics/Joints/b2RevoluteJoint.cpp \
	Dynamics/Joints/b2RopeJoint.cpp \
	Dynamics/Joints/b2WeldJoint.cpp \
	Dynamics/Joints/b2WheelJoint.cpp \
	Dynamics/Joints/b2MotorJoint.cpp \
	Rope/b2Rope.cpp
