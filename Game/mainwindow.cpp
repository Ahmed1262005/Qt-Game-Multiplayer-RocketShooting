#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    setFixedSize(800, 600);

    initializeBox2D();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWorld);
    timer->start(16); // Update every 16 milliseconds
}

MainWindow::~MainWindow()
{
    delete world;
}

void MainWindow::initializeBox2D()
{
    b2Vec2 gravity(0.0f, -9.8f); // Earth gravity, 9.8 m/s^2 downward
    world = new b2World(gravity);

    createGround();
    createDynamicBox(0, 5);
}

void MainWindow::createGround()
{
    b2BodyDef groundBodyDef; // Ground 0
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body *groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);
}

void MainWindow::createDynamicBox(float x, float y)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void MainWindow::updateWorld()
{
    world->Step(1.0f / 60.0f, 6, 2);

    update(); // Schedule a repaint
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw Box2D objects here

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext())
    {
        b2Vec2 position = body->GetPosition();
        painter.drawRect(QRectF(position.x - 0.5, position.y - 0.5, 1.0, 1.0));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        createDynamicBox(0, 5);
    }
}
void MainWindow::createThrowableObject(float x, float y)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    throwableObject = world->CreateBody(&bodyDef);

    b2CircleShape throwableShape;
    throwableShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &throwableShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    throwableObject->CreateFixture(&fixtureDef);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        b2Vec2 mousePos(event->pos().x(), event->pos().y());

        b2AABB aabb;
        b2Vec2 d(0.001f, 0.001f);
        aabb.lowerBound = mousePos - d;
        aabb.upperBound = mousePos + d;

        // Query the world to find the clicked object
        b2QueryCallback callback(mousePos);
        world->QueryAABB(&callback, aabb);

        if (callback.fixture)
        {
            b2Body* clickedBody = callback.fixture->GetBody();

            if (clickedBody == throwableObject)
            {
                b2MouseJointDef jointDef;
                jointDef.bodyA = groundBody; // Assume we have a ground body
                jointDef.bodyB = throwableObject;
                jointDef.target = mousePos;
                jointDef.maxForce = 1000.0f * throwableObject->GetMass();

                mouseJoint = (b2MouseJoint*)world->CreateJoint(&jointDef);
                throwableObject->SetAwake(true);

                // Save the initial mouse position for dragging
                dragStart = mousePos;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseJoint)
    {
        b2Vec2 mousePos(event->pos().x(), event->pos().y());
        mouseJoint->SetTarget(mousePos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && mouseJoint)
    {
        world->DestroyJoint(mouseJoint);
        mouseJoint = nullptr;

        // Calculate the impulse based on the drag distance
        b2Vec2 dragEnd(event->pos().x(), event->pos().y());
        b2Vec2 impulse = 10.0f * (dragEnd - dragStart); // Adjust the multiplier as needed

        throwableObject->ApplyLinearImpulse(impulse, throwableObject->GetWorldCenter(), true);
    }
}

