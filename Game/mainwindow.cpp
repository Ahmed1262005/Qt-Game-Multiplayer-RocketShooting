#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setFixedSize(800, 600);

    initializeBox2D();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWorld);
    timer->start(16); // Update every 16 milliseconds
}

MainWindow::~MainWindow() {
    delete world;
}

void MainWindow::drawTrajectory(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));

    TrajectoryRayCastClosestCallback raycastCallback;
    b2Vec2 lastTP = rocketPosition;

    for (int i = 0; i < trajectoryPointsCount; ++i) {
        b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);
        // Adjust the y-coordinate to consider the vertical inversion
        QPointF point(trajectoryPosition.x, height() - trajectoryPosition.y);
        painter.drawPoint(point);

        if (i > 0) {
            // Perform a raycast check between successive points
            world->RayCast(&raycastCallback, lastTP, trajectoryPosition);
            if (raycastCallback.m_hit) {
                predictedCollisionPoint = raycastCallback.m_point;
                drawPredictedCollision = true;
                break;  // Exit the loop if a collision is detected
            }
        }

        lastTP = trajectoryPosition;
    }

    // Draw the predicted collision point
    if (drawPredictedCollision) {
        QPointF collisionPoint(predictedCollisionPoint.x, height() - predictedCollisionPoint.y);
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine));
        painter.drawPoint(collisionPoint);
    }
}


// Implement the getTrajectoryPoint function
b2Vec2 MainWindow::getTrajectoryPoint(b2Vec2 &startingPosition, b2Vec2 &startingVelocity, float n) {
    // Velocity and gravity are given per second but we want time step values here
    float t = 1 / 60.0f; // seconds per time step (at 60fps)
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * world->GetGravity(); // m/s/s

    float x = startingPosition.x + n * stepVelocity.x + 0.5f * (n * n + n) * stepGravity.x;
    float y = startingPosition.y + n * stepVelocity.y + 0.5f * (n * n + n) * stepGravity.y;

    return b2Vec2(x, y);
}


void MainWindow::initializeBox2D() {
    b2Vec2 gravity(0.0f, -9.8f); // Earth gravity, 9.8 m/s^2 downward
    world = new b2World(gravity);

    // Move the ground down
    createGround();
    createDynamicBox(100, 100);
    createRocket(2.0f, 2.0f); // Set initial rocket position
    rocketVelocity.Set(300.0f, 50.0f); // Set initial rocket velocity

    // Initialize rocket-related variables
    rocketPosition.Set(1000.0f, 20.0f);
    trajectoryPointsCount = 180; // Adjust the count as needed
}
void MainWindow::createGround() {
    b2BodyDef groundBodyDef; // Ground 0
    groundBodyDef.position.Set(0.0f, -100.f); // Move the ground down

    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(100.0f, 100.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);
}


void MainWindow::createDynamicBox(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1000.0f, 1000.0f);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void MainWindow::updateWorld() {
    world->Step(1.0f / 60.0f, 6, 2);

    update(); // Schedule a repaint
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw Box2D objects here

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
        b2Vec2 position = body->GetPosition();
        // Adjust the rendering to consider the vertical inversion
        painter.drawRect(QRectF(position.x - 0.5, height() - position.y - 0.5, 1, 1));
    }

    // Draw the rocket trajectory
    drawTrajectory(painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        createDynamicBox(100, 0);
        rocketVelocity = { 450.0f, 90.0f };

        // Launch the rocket
        launchRocket();

        // Reset rocket position and trajectory
        rocketPosition.Set(2.0f, 2.0f);
        updateRocketTrajectory();
    }
}
void MainWindow::launchRocket()
{
    if (rocketBody)
    {
        // Apply impulse to the rocket body based on the velocity
        // Adjust the multiplier as needed
        b2Vec2 impulse = 100.0f * rocketVelocity;
        rocketBody->ApplyLinearImpulse(impulse, rocketBody->GetWorldCenter(), true);
    }
}

void MainWindow::updateRocketTrajectory()
{
    if (rocketBody)
    {
        // Get the mouse position and adjust the rocket position accordingly
        //

        // Update trajectory points based on the new rocket position and velocity
        for (int i = 0; i < trajectoryPointsCount; ++i)
        {
            b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);
            // Store the trajectory points in a container or draw them directly
            // (e.g., store in a QVector<b2Vec2> and draw in the paintEvent function)
        }
    }
}

void MainWindow::createRocket(float x, float y)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    rocketBody = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Rocket shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    rocketBody->CreateFixture(&fixtureDef);
}

void MainWindow::createTarget(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);

    b2Body *body = world->CreateBody(&bodyDef);

    b2CircleShape staticCircle;
    staticCircle.m_radius = 1.0f; // Target shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticCircle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void MainWindow::createThrowableObject(float x, float y) {
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

//void MainWindow::mousePressEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton) {
//        b2Vec2 mousePos(event->pos().x(), event->pos().y());
//
//        b2AABB aabb;
//        b2Vec2 d(0.001f, 0.001f);
//        aabb.lowerBound = mousePos - d;
//        aabb.upperBound = mousePos + d;
//
//        // Query the world to find the clicked object
//        QueryCallback callback(mousePos);
//        world->QueryAABB(&callback, aabb);
//
//        if (callback.m_fixture) {
//            b2Body *clickedBody = callback.m_fixture->GetBody();
//
//            if (clickedBody == throwableObject) {
//                b2MouseJointDef jointDef;
//                jointDef.bodyA = groundBody; // Assume we have a ground body
//                jointDef.bodyB = throwableObject;
//                jointDef.target = mousePos;
//                jointDef.maxForce = 1000.0f * throwableObject->GetMass();
//
//                mouseJoint = (b2MouseJoint *) world->CreateJoint(&jointDef);
//                throwableObject->SetAwake(true);
//
//                // Save the initial mouse position for dragging
//                dragStart = mousePos;
//            }
//        }
//    }
//}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        // Adjust the rocket's position and velocity based on the mouse position
        b2Vec2 mousePos(event->pos().x(), event->pos().y());
        rocketPosition.Set(mousePos.x, qBound(0.0f, mousePos.y, 200.0f)); // Adjust as needed
        rocketVelocity.Set(mousePos.x, qBound(0.0f, mousePos.y, 200.0f)); // Adjust as needed

        // You can print the rocket's position for debugging
        qDebug() << "Rocket Position: (" << rocketPosition.x << ", " << rocketPosition.y << ")";

        // Redraw the trajectory based on the updated rocket position and velocity
        updateRocketTrajectory();
    }
}

//void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
//    if (event->button() == Qt::LeftButton && mouseJoint) {
//        world->DestroyJoint(mouseJoint);
//        mouseJoint = nullptr;
//
//        // Calculate the impulse based on the drag distance
//        b2Vec2 dragEnd(event->pos().x(), event->pos().y());
//        b2Vec2 impulse = 10.0f * (dragEnd - dragStart); // Adjust the multiplier as needed
//
//        throwableObject->ApplyLinearImpulse(impulse, throwableObject->GetWorldCenter(), true);
//    }
//}


