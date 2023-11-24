#include "mainwindow.h"
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setFixedSize(800, 600);

    initializeBox2D();
    showBackground();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWorld);
    timer->start(16); // Update every 16 milliseconds
    launcherPixmap.load("://Resources/Images/RocketLaunchersmfix.png"); // Replace with the actual path to your launcher image
    Tower1 = new Obstacles(700.0f,0.0f,200.0f,200.0f,timer,QPixmap("://Resources/Images/tower3(2).png"),world);




    // Initialize other variables
    drawPredictedCollision = true;
//    predictedCollisionPoint.SetZero();

}
void MainWindow::drawLauncher(QPainter &painter, const b2Vec2 &position, float angle)
{
    // Draw rotated launcher pixmap
    drawRotatedPixmap(painter, launcherPixmap, position, angle);
}

void MainWindow::drawRotatedPixmap(QPainter &painter, const QPixmap &pixmap, const b2Vec2 &position, float angle)
{
    angle -= 13.39;
    painter.save();
    painter.translate(position.x, height() - position.y);
    painter.rotate(-angle * 180 / M_PI);
    painter.scale(1, 1);  // Mirror the pixmap horizontally
    painter.drawPixmap(-pixmap.width()/2 , -pixmap.height()/2 , pixmap);
    painter.restore();
}

MainWindow::~MainWindow() {
    delete world;
}

void MainWindow::drawTrajectory(QPainter &painter) {

    painter.setPen(QPen(Qt::yellow, 1, Qt::SolidLine));

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    if (drawPredictedCollision) {

    TrajectoryRayCastClosestCallback raycastCallback;
    b2Vec2 lastTP = rocketPosition;
    b2Vec2 top;
    for (int i = 0; i < trajectoryPointsCount; ++i) {
        b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);
        // Adjust the y-coordinate to consider the vertical inversion
        QPointF point(trajectoryPosition.x, height() - trajectoryPosition.y);
        painter.drawPoint(point);
        if (i == trajectoryPointsCount/2-500) {
            top = trajectoryPosition;
        }
        if (i > 0) {
            // Perform a raycast check between successive points
            world->RayCast(&raycastCallback, lastTP, trajectoryPosition);
            if (raycastCallback.m_hit) {
                // Draw the predicted collision point only if drawPredictedCollision is true
                QPointF collisionPoint(lastTP.x, height() - lastTP.y);
                painter.setPen(QPen(Qt::red, 5, Qt::SolidLine));
                painter.drawPoint(collisionPoint);
                // Calculate the angle of the launcher based on the trajectory

                predictedCollisionPoint = raycastCallback.m_point;
                // Calculate the angle of the launcher based on the trajectory

                break;  // Exit the loop if a collision is detected
            }
        }

        lastTP = trajectoryPosition;
    }
    float angle = atan2(top.y,  top.x);
    drawLauncher(painter, b2Vec2(100.0f,100.0f), angle);

    // Draw the predicted collision point outside the loop
    if (drawPredictedCollision) {
        QPointF collisionPoint(lastTP.x, height() - lastTP.y);
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine));
        painter.drawPoint(collisionPoint);
    }

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
    createRocket(100.0f, 100.0f); // Set initial rocket position
    rocketVelocity.Set(300.0f, 0.0f); // Set initial rocket velocity

    // Initialize rocket-related variables
    rocketPosition.Set(100.f, 100.f);
    trajectoryPointsCount = 1200; // Adjust the count as needed
}

void MainWindow::createGround() {
    b2BodyDef groundBodyDef; // Ground 0
    groundBodyDef.position.Set(0.0f, -100.f); // Move the ground down

    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(800.0f, 199.0f);

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
    if (rocketBody) {
        b2Vec2 velocity = rocketBody->GetLinearVelocity();
        if (qAbs(velocity.x) < 0.1 && qAbs(velocity.y) < 0.1 && !drawPredictedCollision) {
            drawPredictedCollision = true;
            createRocket(100, 100);
        }
    }
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
        if(body->GetFixtureList()->GetDensity() == 1.0f)
            {
                // Adjust the rendering to consider the vertical inversion
                 painter.drawRect(QRectF(position.x - 0.5, height() - position.y - 0.5, 1, 1));
            }

        b2Vec2 towerposition = Tower1->get_body()->GetPosition();

            painter.drawPixmap(towerposition.x-Tower1->get_pixmap().width()/2 , height() - towerposition.y - Tower1->get_pixmap().height()/2, Tower1->get_pixmap());

    }

    // Draw the rocket trajectory
    drawTrajectory(painter);

    // Draw the rocket
    if (rocketBody && !rocketPixmap.isNull() && !drawPredictedCollision) {
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine));

        b2Vec2 rocketPosition = rocketBody->GetPosition();
        // Adjust the rendering to consider the vertical inversion
//        painter.drawRect(QRectF(rocketPosition.x - 0.5, height() - rocketPosition.y - 0.5, 1, 2));
        painter.drawPixmap(rocketPosition.x - rocketPixmap.width() / 2, height() - rocketPosition.y - rocketPixmap.height() / 2, rocketPixmap);

    }


}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
//        createDynamicBox(100, 100);

        // Launch the rocket
        launchRocket(900.0f);
//        setMouseTracking(false);

        // Reset rocket position and trajectory
        //rocketPosition.Set(100.0f, 100.0f);
        //updateRocketTrajectory();
    }
}

void MainWindow::launchRocket(float desiredHeight) {
    if (rocketBody) {
        // Calculate initial velocity based on the desired height
//        rocketVelocity = calculateRocketVelocityForHeight(desiredHeight);

        // Set the rocket's position at the launch point
//        rocketBody->SetTransform(rocketPosition, 0);

        // Apply impulse to the rocket body based on the new velocity
        b2Vec2 impulse = rocketVelocity;

//        rocketBody->SetAngularVelocity(rocketVelocity);
        rocketBody->SetAwake(true);
        rocketBody->SetGravityScale(1);
        rocketBody->SetAngularVelocity(0);
        b2Vec2 Velocity = calculateRocketVelocityForHeight(desiredHeight);

        rocketBody->ApplyLinearImpulse(impulse, rocketBody->GetWorldCenter(), true);
        rocketBody->SetLinearVelocity( rocketBody->GetWorldVector( b2Vec2(rocketVelocity) ) );

        qDebug() << "Rocket Initial Velocity: (" << rocketVelocity.x << ", " << rocketVelocity.y << ")";
        qDebug() << "Applied Impulse: (" << impulse.x << ", " << impulse.y << ")";

        // Update the rocket trajectory after launching
        drawPredictedCollision = false;  // Set drawPredictedCollision to false before updating trajectory
        updateRocketTrajectory();
    }
}

// Function to calculate the rocket's initial velocity for a desired height
b2Vec2 MainWindow::calculateRocketVelocityForHeight(float desiredHeight) {
    if (desiredHeight <= 0)
        return b2Vec2_zero; // Rocket shouldn't go down

    // Gravity is given per second, but we want time step values here
    float t = 1 / 60.0f;
    b2Vec2 stepGravity = t * t * world->GetGravity(); // m/s/s

    // Quadratic equation setup (ax² + bx + c = 0)
    float a = 0.5f / stepGravity.y;
    float b = 0.5f;
    float c = desiredHeight;

    // Check both possible solutions
    float quadraticSolution1 = (-b - b2Sqrt(b * b - 4 * a * c)) / (2 * a);
    float quadraticSolution2 = (-b + b2Sqrt(b * b - 4 * a * c)) / (2 * a);

    // Use the one which is positive
    float v = quadraticSolution1;
    if (v < 0)
        v = quadraticSolution2;

    // Convert answer back to seconds
    v *= 60.0f;

    return b2Vec2(v, 0.0f); // Initial velocity in the x-direction (y-direction is 0)
}


void MainWindow::updateRocketTrajectory() {
    if (rocketBody) {
        // Get the mouse position and adjust the rocket position accordingly
        //

        // Update trajectory points based on the new rocket position and velocity
        for (int i = 0; i < trajectoryPointsCount; ++i) {
            b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);
            // Store the trajectory points in a container or draw them directly
            // (e.g., store in a QVector<b2Vec2> and draw in the paintEvent function)
        }
    }
}

void MainWindow::createRocket(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    rocketBody = world->CreateBody(&bodyDef);
    // Use an image for the rocket
    QPixmap rocketixmap(":/Resources/Images/AdvancedRocketWithoutFire.png");
    rocketPixmap = rocketixmap.scaled(30, 60); // Adjust the size as needed

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Rocket shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 4.0f;
    fixtureDef.friction = 100.3f;

    rocketBody->CreateFixture(&fixtureDef);

    // Set the rocket's initial position and velocity
    rocketPosition = rocketBody->GetPosition();
    rocketVelocity.Set(0.0f, 0.0f); // Set initial rocket velocity (adjust values as needed)
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mouseJoint) {
        // Adjust the rocket's position and velocity based on the mouse position
//        setMouseTracking(true);
        b2Vec2 mousePos(event->pos().x(), event->pos().y());
        rocketPosition.Set(qBound(100.f, mousePos.x, 100.f), qBound(100.0f, mousePos.y, 100.0f)); // Adjust as needed
        rocketVelocity.Set(mousePos.x, qBound(0.0f, height() - mousePos.y, 100.0f)); // Adjust as needed

        // You can print the rocket's position for debugging
        qDebug() << "Rocket Position: (" << rocketPosition.x << ", " << rocketPosition.y << ")";

        // Redraw the trajectory based on the updated rocket position and velocity
        updateRocketTrajectory();
    }
}

void MainWindow:: showBackground()
{
    QPixmap background("://Resources/Images/Level1.webp");
    background =background.scaled(1920,1080, Qt::IgnoreAspectRatio);
    QPalette pal;
    pal.setBrush(QPalette::Window, background);
    this->setPalette(pal);
}
