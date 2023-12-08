#include "mainwindow.h"
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include "level.h"
#include "startmenu.h"
#include <midmenu.h>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setFixedSize(800, 600);

    initializeBox2D();
    showBackground();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWorld);
    timer->start(3); // Update every 16 milliseconds
    launcherPixmap.load("://Resources/Images/RocketLaunchersmfix.png");
    // Replace with the actual path to your launcher image
    //evilGuy = new Obstacles(775.0f,-10.0f,100.0f,100.0f,timer,QPixmap("://Resources/Images/EvilGuy.png"),world);
    //evilGuy->get_body()->SetUserData((void*)"EvilGuy");
    // Initialize other variables and stuff
    drawPredictedCollision = true;
    /*
    for(auto i = enemies.begin(); i != enemies.end(); i++){
        enemyCounter++;
        (*i)->get_body()->SetUserData((void*)"EvilGuy");

    }
*/
//    predictedCollisionPoint.SetZero();
    timer->singleShot(1000, [this]() { world->SetContactListener(this); });


}

void MainWindow::drawLauncher(QPainter *renderer, const b2Vec2 &position, float angle) {
    // Draw rotated launcher pixmap
    drawRotatedPixmap(renderer, launcherPixmap, position, angle);
}

void MainWindow::drawRotatedPixmap(QPainter *renderer, const QPixmap &pixmap, const b2Vec2 &position, float angle) {
    angle -= 13.39;
    renderer->save();
    renderer->translate(position.x, height() - position.y);
    renderer->rotate(-angle * 180 / M_PI);
    renderer->scale(1, 1);  // Mirror the pixmap horizontally
    renderer->drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2, pixmap);
    renderer->restore();
}

MainWindow::~MainWindow() {
    delete world;
}

void MainWindow::drawTrajectory(QPainter *renderer) {

    renderer->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    if (drawPredictedCollision) {

        TrajectoryRayCastClosestCallback raycastCallback;
        b2Vec2 lastTP = rocketPosition;
        b2Vec2 top;
        for (int i = 0; i < trajectoryPointsCount; ++i) {
            b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);
            // Adjust the y-coordinate to consider the vertical inversion
            QPointF point(trajectoryPosition.x, height() - trajectoryPosition.y);
            renderer->drawPoint(point);
            if (i == trajectoryPointsCount / 2 - 700) {
                top = trajectoryPosition;
            }
            if (i > 0) {
                // Perform a raycast check between successive points
                world->RayCast(&raycastCallback, lastTP, trajectoryPosition);
                if (raycastCallback.m_hit) {
                    // Draw the predicted collision point only if drawPredictedCollision is true
                    QPointF collisionPoint(lastTP.x, height() - lastTP.y);
                    renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));
                    renderer->drawPoint(collisionPoint);
                    // Calculate the angle of the launcher based on the trajectory

                    predictedCollisionPoint = raycastCallback.m_point;
                    // Calculate the angle of the launcher based on the trajectory

                    break;  // Exit the loop if a collision is detected
                }
            }

            lastTP = trajectoryPosition;
        }
        float angle = atan2(top.y, top.x);
        drawLauncher(renderer, b2Vec2(100.0f, 100.0f), angle);

        // Draw the predicted collision point outside the loop
        if (drawPredictedCollision) {
            QPointF collisionPoint(lastTP.x, height() - lastTP.y);
            renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));
            renderer->drawPoint(collisionPoint);
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
    trajectoryPointsCount = 2000; // Adjust the count as needed
}

void MainWindow::createGround() {
    b2BodyDef groundBodyDef; // Ground 0
    groundBodyDef.position.Set(0.0f, -100.f); // Move the ground down

    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(8000.0f, 199.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);
}

// delete this useless function
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
float MainWindow::calculateScore() {
    float totalRockets = (float)lvl->getWinOffset() + (float)lvl->getDifficulty(); // total rockets is win offset plus remaining rockets
    float rocketsUsed = totalRockets - (float)counter; // rockets used is total rockets minus remaining rockets
    float score = ((totalRockets - rocketsUsed + (float)lvl->getWinOffset()) ) / totalRockets * 100;
    if (score > 100) {
        score = 100; // Ensure score doesn't exceed 100
    }
    return score;
}

void MainWindow::updateWorld() {


    world->Step(1.0f / 60.0f, 6, 2);
    if (rocketBody) {
        b2Vec2 velocity = rocketBody->GetLinearVelocity();
        if (qAbs(velocity.x) < 0.1 && qAbs(velocity.y) < 0.1 && !drawPredictedCollision) {
            drawPredictedCollision = true;
            //counter ++ lose at 3
            createRocket(100, 100);

        }

    }

    if (counter == 2) {

        MidMenu *midmenu = new MidMenu;
        StartMenu *start = new StartMenu;
        std::vector<Level *> levels = start->getLevels();
        midmenu->setLevels(levels);

        midmenu->get_window(this);

        //MusicPlayer->stop();
        midmenu->level = levels[currentLevel];
        midmenu->currentLevelIndex = currentLevel;

        float totalRockets = (float)midmenu->level->getWinOffset() + (float)midmenu->level->getDifficulty(); // total rockets is win offset plus remaining rockets
        float rocketsUsed = totalRockets - (float)counter; // rockets used is total rockets minus remaining rockets
        float score = ((totalRockets - rocketsUsed + (float)midmenu->level->getWinOffset()) ) / totalRockets;
        if (score > 100) {
            score = 100; // Ensure score doesn't exceed 100
        }
        midmenu->score= score;

        lvl = midmenu->level;

        midmenu->get_level(midmenu->getNextLevel());

        midmenu->show();

        timer->start(500000);

    }


    update(); // Schedule a repaint
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter *renderer = new QPainter(this);
    renderer->setRenderHint(QPainter::Antialiasing, true);

    // Draw Box2D objects here

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
        b2Vec2 position = body->GetPosition();
        if (body->GetFixtureList()->GetDensity() == 1.0f) {
            // Adjust the rendering to consider the vertical inversion
            renderer->drawRect(QRectF(position.x - 0.5, height() - position.y - 0.5, 1, 1));
        }
    }

    // Draw the rocket trajectory
    drawTrajectory(renderer);

    renderer->drawText(100, 100, "Cannon Amunition:" + QString::number(counter));

    // Draw the rocket
    if (rocketBody && !rocketPixmap.isNull() && !drawPredictedCollision) {
        renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));

        b2Vec2 rocketPosition = rocketBody->GetPosition();
        // Adjust the rendering to consider the vertical inversion
//        painter.drawRect(QRectF(rocketPosition.x - 0.5, height() - rocketPosition.y - 0.5, 1, 2));
        renderer->drawPixmap(rocketPosition.x - rocketPixmap.width() / 2,
                             height() - rocketPosition.y - rocketPixmap.height() / 2, rocketPixmap);

    }
    enemyCounter = 0;

    for (auto i = towers.begin(); i != towers.end(); i++) {
        if ((*i)->getHealth() < 20) { // If health is below 20
            QPixmap crackPixmap("://Resources/Images/crack.png"); // Load the crack image
            // Draw the crack image on top of the obstacle
            renderer->drawPixmap(towerPosition.x - crackPixmap.width() / 2,
                                 height() - towerPosition.y - crackPixmap.height() / 2, crackPixmap);
        }

        towerPosition = (*i)->get_body()->GetPosition();

        renderer->drawPixmap(towerPosition.x - (*i)->get_pixmap().width() / 2,
                             height() - towerPosition.y - (*i)->get_pixmap().height() / 2, (*i)->get_pixmap());
    }
    for (auto i = enemies.begin(); i != enemies.end(); i++) {
        //enemyCounter++;
        //(*i)->get_body()->SetUserData((void*)"EvilGuy");
        enemiesPosition = (*i)->get_body()->GetPosition();

        renderer->drawPixmap(enemiesPosition.x - (*i)->get_pixmap().width() / 2,
                             height() - enemiesPosition.y - (*i)->get_pixmap().height() / 2, (*i)->get_pixmap());
    }


    renderer->end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && drawPredictedCollision) {
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
        rocketBody->SetLinearVelocity(rocketBody->GetWorldVector(b2Vec2(rocketVelocity)));

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
    counter--;

    rocketBody = world->CreateBody(&bodyDef);
    // Use an image for the rocket
    QPixmap rocketixmap("://Resources/Images/RoundShot.png");
    rocketPixmap = rocketixmap.scaled(30, 30); // Adjust the size as needed

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Rocket shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 3.0f;
    fixtureDef.friction = 100.3f;

    rocketBody->CreateFixture(&fixtureDef);

    // Set the rocket's initial position and velocity
    rocketPosition = rocketBody->GetPosition();
    rocketVelocity.Set(0.0f, 0.0f); // Set initial rocket velocity (adjust values as needed)
    rocketBody->SetUserData((void *) "Rocket");
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
    // Adjust the rocket's position and velocity based on the mouse position
//        setMouseTracking(true);
    b2Vec2 mousePos(event->pos().x(), event->pos().y());
    rocketPosition.Set(qBound(100.f, mousePos.x, 100.f), qBound(100.0f, mousePos.y, 100.0f)); // Adjust as needed
    rocketVelocity.Set(mousePos.x, qBound(0.0f, height() - mousePos.y, 110.0f)); // Adjust as needed

    // You can print the rocket's position for debugging
    qDebug() << "Rocket Position: (" << rocketPosition.x << ", " << rocketPosition.y << ")";

    // Redraw the trajectory based on the updated rocket position and velocity
    updateRocketTrajectory();
}

void MainWindow::setMusicPlayer(bool music) {
    MusicPlayer = new QMediaPlayer;

    Speaker = new QAudioOutput;

    MusicPlayer->setSource(QUrl("qrc:/Resources/Audio/Leyndell, Royal Capital.mp3"));

    MusicPlayer->setAudioOutput(Speaker);

    Speaker->setVolume(20);

    MusicPlayer->setLoops(-1);


    if (music) {
        MusicPlayer->play();
    } else {
        MusicPlayer->stop();
    }
}

void MainWindow::showBackground() {
    QPixmap background("://Resources/Images/Level1.webp");
    background = background.scaled(1920, 1080, Qt::IgnoreAspectRatio);
    QPalette pal;
    pal.setBrush(QPalette::Window, background);
    this->setPalette(pal);

}

void MainWindow::setTowers(QVector<Obstacles *> Towers) {
    towers = Towers;
}

void MainWindow::setEnemies(QVector<Obstacles *> e) {
    enemies = e;
}

void MainWindow::BeginContact(
        b2Contact *contactPoint) //cp will tell you which fixtures collided, now we look at which body they are attached to, now which particles are assosiated with these bodies?
{//SetUserData and GetUserData are in body class:
    //we set a name to a body

    b2Fixture *EvilGuyF = contactPoint->GetFixtureA();
    b2Fixture *RocketF = contactPoint->GetFixtureB();

    b2Body *EvilGuy = EvilGuyF->GetBody();
    b2Body *Rocket = RocketF->GetBody();
    if (EvilGuy->GetUserData() && Rocket->GetUserData()) {

        qDebug() << "Collision detected!";
    }
    bool isRocketEvilGuyCollision =
            ((EvilGuy->GetUserData() == (void *) "Rocket" && Rocket->GetUserData() == (void *) "EvilGuy") ||
             (EvilGuy->GetUserData() == (void *) "EvilGuy" && Rocket->GetUserData() == (void *) "Rocket"));

    qDebug() << (EvilGuy->GetUserData() == (void *) "EvilGuy");
    // Check if either fixture is associated with the EvilGuy
    //    bool EvilGuy = (EvilGuyF->GetBody()->GetUserData() == (void*)"EvilGuy");
    //    bool Rocket = (RocketF->GetBody()->GetUserData() == (void*)"Rocket");

    // Check if the contact involves EvilGuy

    b2Body *evilGuyBody = (EvilGuy->GetUserData() == (void *) "EvilGuy") ? EvilGuy : Rocket;
    if (isRocketEvilGuyCollision) {
        qDebug() << "Collision detected inside!";
        contactPoint->SetEnabled(false);

        b2World *world = evilGuyBody->GetWorld();

        timer->start(500000);

        hide();

        QGraphicsScene *scene = new QGraphicsScene;

        QGraphicsView *view = new QGraphicsView;

        scene->setSceneRect(0, 0, 700, 600);

        view->setFixedSize(700, 600);

        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        view->setScene(scene);

        scene->setBackgroundBrush(QBrush(QPixmap("://Resources/Images/victory.jpg").scaled(700, 600)));

        view->show();

    }
    b2Fixture *fixtureA = contactPoint->GetFixtureA();
    b2Fixture *fixtureB = contactPoint->GetFixtureB();

    // Check if either fixture is associated with a tower
    bool isTowerA = (fixtureA->GetBody()->GetUserData() == (void*)"Tower");
    bool isTowerB = (fixtureB->GetBody()->GetUserData() == (void*)"Tower");

    // Check if the contact involves a tower
    if (isTowerA || isTowerB) {
        // Get the tower body
        b2Body *towerBody = isTowerA ? fixtureA->GetBody() : fixtureB->GetBody();

        // Find the corresponding tower object in the towers vector
        for (auto it = towers.begin(); it != towers.end(); ++it) {
            if ((*it)->get_body() == towerBody) {
                // Decrease the health of the tower
                (*it)->applyDamage(80); // Adjust the damage value as needed

                if ((*it)->getHealth() <= 0) {
                    // If the tower's health is zero or less, remove it from the towers vector
                    towers.erase(it);
                }

                break;
            }
        }


    if (evilGuyBody) {

        return;

    }


}
}
