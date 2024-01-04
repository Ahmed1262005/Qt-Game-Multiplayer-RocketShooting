#include "multiplayermainwindow.h"

MultiplayerMainWindow::MultiplayerMainWindow(GameManager *gameManager,QWidget *parent)
        : PhysicsWorld(parent),gameManager(gameManager)
{
    // Connect signals and slots between gameManager and this
    connect(gameManager, &GameManager::rocketLaunchMessageReceived, this, &MultiplayerMainWindow::launchOpponentRocket);
    // Create an instance of Level
    QVector<Obstacles *> Towers; // Vector of tower objects in the level
    QVector<Obstacles *> Enemies; // Vector of enemy objects in the level
    Towers.push_back(new Obstacles(540.0f,-10.0f,150.0f,400.0f, QPixmap(":/Resources/Images/tower1.png"), world, 10.0f, 0.2f, 0.2f));
//    Towers.back()->get_body()->SetUserData((void*)"enemy tower");
    Towers.push_back(new Obstacles(1040.0f,-10.0f,150.0f,400.0f, QPixmap(":/Resources/Images/tower1.png"), world, 10.0f, 0.2f, 0.2f));
    Enemies.push_back(new Obstacles(340.0f, -20.f,150.f,150.f, QPixmap(":/Resources/Images/EvilGuy.png"), world, 10.0f, 0.2f, 0.2f));
    Enemies.back()->get_body()->SetUserData((void*)"EvilGuy");
    Enemies.push_back(new Obstacles(1240.0f, -20.f,150.f,150.f, QPixmap(":/Resources/Images/EvilGuy.png"), world, 10.0f, 0.2f, 0.2f));
    Enemies.back()->get_body()->SetUserData((void*)"EvilGuy");
    setEnemies(Enemies);
    setTowers(Towers);
}

MultiplayerMainWindow::~MultiplayerMainWindow()
{
    delete gameManager;
}

void MultiplayerMainWindow::createMultiplayerGame()
{
    gameManager->createGameRequest();
}
void MultiplayerMainWindow::launchRocket(float desiredHeight) {
    // Call the base class's launchRocket function
    PhysicsWorld::launchRocket(desiredHeight);

    // After launching the rocket, send the rocket's position and direction to the game manager
    if (rocketBody) {
        b2Vec2 position = rocketBody->GetPosition();
        b2Vec2 direction = rocketVelocity;
        gameManager->sendRocketLaunchMessage(position, direction);
    }
}
void MultiplayerMainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter *renderer = new QPainter(this);
    renderer->setRenderHint(QPainter::Antialiasing, true);
//    renderer->drawPixmap(towerPosition.x - crackPixmap.width() / 2,
//                         height() - towerPosition.y - crackPixmap.height() / 2, crackPixmap)
    // Draw Box2D objects

    renderer->save(); // Save the current state of the QPainter
    renderer->translate(width()-100.0f, height() - 100.0f); // Translate to the position (adjusting for screen coordinate system)
    renderer->drawPixmap(-launcherPixmap.width() / 2, -launcherPixmap.height() / 2, launcherPixmap);

    renderer->scale(.3, .3);  // Mirror the pixmap horizontally (if needed)

    renderer->restore(); // Restore the saved state of the QPainter to previous settings

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
        // Check if the body is flagged for deletion and destroy it
        char *userData = static_cast<char *>(body->GetUserData());
        b2Vec2 velocity = body->GetLinearVelocity();

        // Check the user data and render the body accordingly
        if (userData) {
            if (strcmp(userData, "Rocket") == 0 && !rocketPixmap.isNull() && qAbs(velocity.x) > 0.1 && qAbs(velocity.y) > 0.1) {
                // Render the rocket
                b2Vec2 rocketPosition = body->GetPosition();
                renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));

                renderer->drawPixmap(rocketPosition.x - rocketPixmap.width() / 2,
                                     height() - rocketPosition.y - rocketPixmap.height() / 2, rocketPixmap);
            }
            else if(strcmp(userData, "TO_DELETE") == 0){
                world->DestroyBody(body);
                continue;
            }
        }
//            if (body->GetUserData() == (void*)"TO_DELETE")
        b2Vec2 position = body->GetPosition();
        if (body->GetFixtureList()->GetDensity() == 1.0f) {
            // Render dynamic boxes (adjusting for vertical inversion)
            renderer->drawRect(QRectF(position.x - 0.5, height() - position.y - 0.5, 1, 1));
        }
    }

    // Draw the rocket trajectory
    drawTrajectory(renderer);


    for (auto i = towers.begin(); i != towers.end(); i++) {
        if ((*i)->getHealth() > 0) {

            towerPosition = (*i)->get_body()->GetPosition();

            if((*i)->get_body() == rocketBody)
            {
                continue;
            }

            // Render tower pixmap
            renderer->drawPixmap(towerPosition.x - (*i)->get_pixmap().width() / 2,
                                 height() - towerPosition.y - (*i)->get_pixmap().height() / 2, (*i)->get_pixmap());
            if ((*i)->getHealth() <= 20) {
                towerPosition = (*i)->get_body()->GetPosition();
                // Load and render crack image if tower health is low
                QPixmap crackPixmap("://Resources/Images/cracks.png");
                renderer->drawPixmap(towerPosition.x - crackPixmap.width() / 2,
                                     height() - towerPosition.y - crackPixmap.height() / 2, crackPixmap);
            }
        }
    }

    // Draw the rocket if it exists and predicted collision is not happening
//    if (rocketBody && !rocketPixmap.isNull() && !drawPredictedCollision) {
//        renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));
//
//        b2Vec2 rocketPosition = rocketBody->GetPosition();
//        // Render the rocket's pixmap
//        renderer->drawPixmap(rocketPosition.x - rocketPixmap.width() / 2,
//                             height() - rocketPosition.y - rocketPixmap.height() / 2, rocketPixmap);
//    }

    // Reset enemy counter
    enemyCounter = 0;

    // Iterate through towers and render them


    // Iterate through enemies and render them
    for (auto i = enemies.begin(); i != enemies.end(); i++) {
        if ((*i)->getHealth() > 0) {
            enemiesPosition = (*i)->get_body()->GetPosition();
            if ((*i)->getHealth() <= 20) {
                // Load and render crack image if tower health is low
                enemiesPosition = (*i)->get_body()->GetPosition();
                QPixmap bloodPixmap("://Resources/Images/blood.png");
                renderer->drawPixmap(enemiesPosition.x - bloodPixmap.width() / 2,
                                     height() - enemiesPosition.y - bloodPixmap.height() / 2, bloodPixmap);
            }
            // Render enemy pixmap
            renderer->drawPixmap(enemiesPosition.x - (*i)->get_pixmap().width() / 2,
                                 height() - enemiesPosition.y - (*i)->get_pixmap().height() / 2, (*i)->get_pixmap());
        }
    }

    renderer->end();
}

void MultiplayerMainWindow::launchOpponentRocket(const b2Vec2 &position, const b2Vec2 &direction) {
    // Create a new rocket at a negative x-coordinate for the opponent
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(width() - 100.0f, position.y); // Adjust the y-coordinate as needed
    b2Body* opponentRocketBody = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Rocket shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 100.3f;

    opponentRocketBody->CreateFixture(&fixtureDef);
    opponentRocketBody->SetUserData((void *) "Rocket");

    // Calculate the angle of the original direction
    float angle = atan2(direction.y, direction.x);

    // Add PI to the angle to mirror it
    float mirroredAngle = M_PI-  angle;
    // Convert the mirrored angle back to a vector
    b2Vec2 mirroredDirection(cos(mirroredAngle), sin(mirroredAngle));
    mirroredDirection *= direction.Length();

    // Apply the mirrored impulse to the opponent's rocket to launch it towards the left side of the screen
    opponentRocketBody->ApplyLinearImpulse(mirroredDirection, opponentRocketBody->GetWorldCenter(), true);

    // Set the linear velocity of the opponent's rocket body
    opponentRocketBody->SetLinearVelocity(opponentRocketBody->GetWorldVector(b2Vec2(mirroredDirection)));
//    drawPredictedCollision = true;  // Disable displaying predicted collision after launch
}

void MultiplayerMainWindow::joinMultiplayerGame(QString gameID)
{
    gameManager->joinLobbyRequest(gameID);
}

void MultiplayerMainWindow::sendMultiplayerMessage(QString message)
{
    gameManager->sendMessageToLobby(message);
}

void MultiplayerMainWindow::updateWorld() {
    // Implement the game logic for the multiplayer game

    // Call the base class's updateWorld function if needed
    PhysicsWorld::updateWorld();
}
