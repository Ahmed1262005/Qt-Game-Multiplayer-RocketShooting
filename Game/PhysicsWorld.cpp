#include "PhysicsWorld.h"
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


PhysicsWorld::PhysicsWorld(QWidget *parent)
    : QMainWindow(parent) {
    setFixedSize(800, 600); // Set the fixed size for the main window

    initializeBox2D(); // Initialize the Box2D physics engine
    showBackground(); // Display the background image or scene

    timer = new QTimer(this); // Create a QTimer object for updating the world
    connect(timer, &QTimer::timeout, this, &PhysicsWorld::updateWorld); // Connect the timer's timeout signal to the updateWorld slot
    timer->start(3); // Start the timer to trigger updates every 3 milliseconds

    launcherPixmap.load(":/Resources/Images/canon.png"); // Load the launcher pixmap image

    // Initialize variables and flags
    drawPredictedCollision = true;

    // Use a QTimer singleShot to set the contact listener for the Box2D world after a delay
    timer->singleShot(1000, [this]() { world->SetContactListener(this); });
}

void PhysicsWorld::setRocketCount(int count)
{
    counter=count;
}

void PhysicsWorld::drawLauncher(QPainter *renderer, const b2Vec2 &position, float angle) {
    // Draw rotated launcher pixmap
    drawRotatedPixmap(renderer, launcherPixmap, position, angle);
}

void PhysicsWorld::drawRotatedPixmap(QPainter *renderer, const QPixmap &pixmap, const b2Vec2 &position, float angle) {
    angle -= 13.39; // Adjust the angle (offset) for rendering purposes

    renderer->save(); // Save the current state of the QPainter
    renderer->translate(position.x, height() - position.y); // Translate to the position (adjusting for screen coordinate system)

    renderer->rotate(-angle * 180 / M_PI -40); // Rotate the pixmap with the given angle (converted to degrees)
    renderer->scale(.3, .3);  // Mirror the pixmap horizontally (if needed)

    // Draw the rotated pixmap at the specified position with the adjusted angle
    renderer->drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2, pixmap);

    renderer->restore(); // Restore the saved state of the QPainter to previous settings
}


PhysicsWorld::~PhysicsWorld() {
    delete world; // Delete the physics world
    delete MusicPlayer;
    delete Speaker;
}

void PhysicsWorld::drawTrajectory(QPainter *renderer) {

    renderer->setPen(QPen(Qt::black, 1, Qt::SolidLine));  // Set pen properties for drawing the trajectory

    if (drawPredictedCollision) {
        // Initialize variables for trajectory analysis
        TrajectoryRayCastClosestCallback raycastCallback; // Raycast callback for collision detection
        b2Vec2 lastTP = rocketPosition; // Store the last tracked trajectory point
        b2Vec2 top; // Variable to track a specific point in the trajectory

        // Iterate through the trajectory points to visualize the rocket's path
        for (int i = 0; i < trajectoryPointsCount; ++i) {
            // Calculate the trajectory position at a given time step
            b2Vec2 trajectoryPosition = getTrajectoryPoint(rocketPosition, rocketVelocity, i);

            // Adjust the y-coordinate to match the display (considering vertical inversion)
            QPointF point(trajectoryPosition.x, height() - trajectoryPosition.y);

            // Draw the trajectory point on the canvas
            renderer->drawPoint(point);

            // Store a specific point in the trajectory (for later use)
            if (i == trajectoryPointsCount / 2 - 900) {
                top = trajectoryPosition;
            }

            // Check for collision using raycasting between successive points
            if (i > 0) {
                world->RayCast(&raycastCallback, lastTP, trajectoryPosition);

                // If a collision is detected, draw the predicted collision point
                if (raycastCallback.m_hit) {
                    QPointF collisionPoint(lastTP.x, height() - lastTP.y);
                    renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));
                    renderer->drawPoint(collisionPoint);

                    // Store the collision point and exit the loop
                    predictedCollisionPoint = raycastCallback.m_point;
                    break;
                }
            }

            // Update the last tracked trajectory point
            lastTP = trajectoryPosition;
        }

        // Calculate the angle of the launcher based on the trajectory and draw it
        float angle = atan2(top.y, top.x);
        drawLauncher(renderer, b2Vec2(100.0f, 100.0f), angle);

        // Draw the predicted collision point outside the loop if necessary
        if (drawPredictedCollision) {
            QPointF collisionPoint(lastTP.x, height() - lastTP.y);
            renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));
            renderer->drawPoint(collisionPoint);
        }
    }


}


// Implement the getTrajectoryPoint function
b2Vec2 PhysicsWorld::getTrajectoryPoint(b2Vec2 &startingPosition, b2Vec2 &startingVelocity, float n) {
    // Velocity and gravity are given per second but we want time step values here
    float t = 1 / 60.0f; // seconds per time step (at 60fps)
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * world->GetGravity(); // m/s/s

    float x = startingPosition.x + n * stepVelocity.x + 0.5f * (n * n + n) * stepGravity.x;
    float y = startingPosition.y + n * stepVelocity.y + 0.5f * (n * n + n) * stepGravity.y;

    return b2Vec2(x, y);
}


void PhysicsWorld::initializeBox2D() {
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

void PhysicsWorld::createGround() {
    // Define the body for the ground
    b2BodyDef groundBodyDef; // Define a body definition for the ground
    groundBodyDef.position.Set(0.0f, -100.f); // Set the position of the ground (moving it down)

    // Create the ground body in the Box2D world
    groundBody = world->CreateBody(&groundBodyDef);

    // Define the shape of the ground (a large box)
    b2PolygonShape groundBox;
    groundBox.SetAsBox(8000.0f, 199.0f); // Set the ground shape as a box

    // Create a fixture (physical properties like shape and density) for the ground body
    groundBody->CreateFixture(&groundBox, 0.0f); // Attach the shape (fixture) to the ground body

    // Set user data to mark this body as "Ground" (for collision identification)
    groundBody->SetUserData((void *) "Ground");
}


float PhysicsWorld::calculateScore() {
    // Calculate the total number of rockets available (win offset + difficulty)
    float totalRockets = (float) lvl->getWinOffset() + (float) lvl->getDifficulty();

    // Calculate the number of rockets used (total rockets - remaining rockets)
    float rocketsUsed = totalRockets - (float) counter;

    // Calculate the score based on the rockets used and total rockets, capped at 100%
    float score = ((totalRockets - rocketsUsed + (float) lvl->getWinOffset())) / totalRockets * 100;

    // Ensure the score doesn't exceed 100
    if (score > 100) {
        score = 100;
    }

    return score; // Return the calculated score
}


void PhysicsWorld::updateWorld() {
    // Update the Box2D world simulation
    world->Step(1.0f / 60.0f, 6, 2);

    // Check if the rocket exists
    if (rocketBody) {
        // Get the velocity of the rocket
        b2Vec2 velocity = rocketBody->GetLinearVelocity();

        // Check if the rocket's velocity is nearly zero and predicted collision is not drawn
        if (qAbs(velocity.x) < 0.1 && qAbs(velocity.y) < 0.1 && !drawPredictedCollision) {
            // Set drawPredictedCollision to true to indicate a predicted collision
            drawPredictedCollision = true;

            // If conditions met, recreate the rocket at a specific position
            createRocket(100, 100);
        }
    }

    // Check if the rocket count is 0
    if (counter == 0) {
        // Create MidMenu and StartMenu instances and retrieve levels
        MidMenu *midmenu = new MidMenu;

        Menu->setMusicPlayer(false);
        std::vector<Level *> levels = Menu->getLevels();

        // Set levels for the MidMenu
        //midmenu->setLevels(levels);

        // Configure MidMenu and set the current level information
        midmenu->get_window(this);
        midmenu->level = levels[currentLevel];
        midmenu->currentLevelIndex = currentLevel;

        // Calculate score and display it in the MidMenu
        float totalRockets = (float) midmenu->level->getWinOffset() + (float) midmenu->level->getDifficulty();
        float rocketsUsed = totalRockets - (float) counter;
        float score = ((totalRockets - rocketsUsed + (float) midmenu->level->getWinOffset())) / totalRockets;

        // Ensure the score doesn't exceed 100%
        if (score > 100) {
            score = 100;
        }

        // Set the calculated score in the MidMenu
        midmenu->score = score;

        // Set the current level in the game to the MidMenu
        lvl = midmenu->level;
        //midmenu->get_level(midmenu->getNextLevel());

        // Show the MidMenu and start the timer
        midmenu->show();
        timer->start(500000); // Adjust the timer interval as needed
    }

    // Schedule a repaint for the PhysicsWorld
    update();
}

void PhysicsWorld::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter *renderer = new QPainter(this);
    renderer->setRenderHint(QPainter::Antialiasing, true);

    // Draw Box2D objects

    // Example: Draw dynamic boxes
    for (b2Body *body = world->GetBodyList(); body; body = body->GetNext()) {
        // Check if the body is flagged for deletion and destroy it
        if (body->GetUserData() == (void*)"TO_DELETE") {
            world->DestroyBody(body);
            continue;
        }
        b2Vec2 position = body->GetPosition();
        if (body->GetFixtureList()->GetDensity() == 1.0f) {
            // Render dynamic boxes (adjusting for vertical inversion)
            renderer->drawRect(QRectF(position.x - 0.5, height() - position.y - 0.5, 1, 1));
        }
    }

    // Draw the rocket trajectory
    drawTrajectory(renderer);

    // Render text displaying cannon ammunition count
    renderer->setFont(QFont("times",22));
    renderer->drawText(50, 50, "Cannon Ammunition: " + QString::number(counter));

    // Render text displaying the current level
    renderer->setFont(QFont("times",22));
    renderer->drawText(500, 50, "Current Level: " + QString::number(getCurrentLevel()+1));

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
    if (rocketBody && !rocketPixmap.isNull() && !drawPredictedCollision) {
        renderer->setPen(QPen(Qt::red, 5, Qt::SolidLine));

        b2Vec2 rocketPosition = rocketBody->GetPosition();
        // Render the rocket's pixmap
        renderer->drawPixmap(rocketPosition.x - rocketPixmap.width() / 2,
                             height() - rocketPosition.y - rocketPixmap.height() / 2, rocketPixmap);
    }

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

void PhysicsWorld::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space && drawPredictedCollision) {
        // If Space key is pressed and predicted collision is enabled
        // Instantiate a QMediaPlayer for music playback
        QMediaPlayer* newMusicPlayer = new QMediaPlayer;

        // Instantiate a QAudioOutput for sound output
        QAudioOutput* newSpeaker = new QAudioOutput;

        // Set the source URL for the music (adjust the path as needed)
        newMusicPlayer->setSource(QUrl("qrc:/Resources/Audio/Small Bomb Explosion Sound Effect.mp3"));

        // Set the audio output for the music player
        newMusicPlayer->setAudioOutput(newSpeaker);

        // Set the volume level for the music (adjust as needed)
        newSpeaker->setVolume(20);

        //Play the effect
        newMusicPlayer->play();

        // Launch the rocket
        launchRocket(900.0f);
    }
}


void PhysicsWorld::launchRocket(float desiredHeight) {
    if (rocketBody) {
        // Calculate initial velocity based on the desired height
        // rocketVelocity = calculateRocketVelocityForHeight(desiredHeight);

        // Set various rocket parameters before launch
        rocketBody->SetAwake(true);            // Ensure the rocket body is awake
        rocketBody->SetGravityScale(1);        // Apply regular gravity to the rocket
        rocketBody->SetAngularVelocity(0);     // Set angular velocity to zero

        // Calculate and apply impulse to the rocket body based on the desired launch height
        b2Vec2 impulse = rocketVelocity;  // Storing the current rocket's velocity

        // Apply linear impulse to the rocket body
        rocketBody->ApplyLinearImpulse(impulse, rocketBody->GetWorldCenter(), true);

        // Set the linear velocity of the rocket body
        rocketBody->SetLinearVelocity(rocketBody->GetWorldVector(b2Vec2(rocketVelocity)));

        // Output debugging information for initial velocity and applied impulse
        qDebug() << "Rocket Initial Velocity: (" << rocketVelocity.x << ", " << rocketVelocity.y << ")";
        qDebug() << "Applied Impulse: (" << impulse.x << ", " << impulse.y << ")";

        // Update the rocket trajectory after launching
        drawPredictedCollision = false;  // Disable displaying predicted collision after launch
        updateRocketTrajectory();
    }
}


// Function to calculate the rocket's initial velocity for a desired height
b2Vec2 PhysicsWorld::calculateRocketVelocityForHeight(float desiredHeight) {
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


void PhysicsWorld::updateRocketTrajectory() {
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

void PhysicsWorld::createRocket(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    counter--;

    rocketBody = world->CreateBody(&bodyDef);
    // Use an image for the rocket
    QPixmap rocketixmap("://Resources/Images/RoundShot.png");
    rocketPixmap = rocketixmap.scaled(50, 50); // Adjust the size as needed

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 2.0f); // Rocket shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 100.3f;
  //fixtureDef.restitution = 10.0f;

    rocketBody->CreateFixture(&fixtureDef);

    // Set the rocket's initial position and velocity
    rocketPosition = rocketBody->GetPosition();
    rocketVelocity.Set(0.0f, 0.0f); // Set initial rocket velocity (adjust values as needed)
    rocketBody->SetUserData((void *) "Rocket");
}

void PhysicsWorld::mouseMoveEvent(QMouseEvent *event) {
    // Adjust the rocket's position and velocity based on the mouse position
    b2Vec2 mousePos(event->pos().x(), event->pos().y());
    rocketPosition.Set(qBound(100.f, mousePos.x, 100.f), qBound(100.0f, mousePos.y, 100.0f)); // Adjust as needed
    rocketVelocity.Set(mousePos.x, qBound(0.0f, height() - mousePos.y, 110.0f)); // Adjust as needed

    // You can print the rocket's position for debugging
    qDebug() << "Rocket Position: (" << rocketPosition.x << ", " << rocketPosition.y << ")";

    // Redraw the trajectory based on the updated rocket position and velocity
    updateRocketTrajectory();
}

void PhysicsWorld::setMusicPlayer(bool music) {
    // Instantiate a QMediaPlayer for music playback
    MusicPlayer = new QMediaPlayer;

    // Instantiate a QAudioOutput for sound output
    Speaker = new QAudioOutput;

    // Set the source URL for the music (adjust the path as needed)
    MusicPlayer->setSource(QUrl("qrc:/Resources/Audio/Leyndell, Royal Capital.mp3"));

    // Set the audio output for the music player
    MusicPlayer->setAudioOutput(Speaker);

    // Set the volume level for the music (adjust as needed)
    Speaker->setVolume(20);

    // Set the music to loop indefinitely (-1 means infinite loops)
    MusicPlayer->setLoops(-1);

    // Check the 'music' flag to determine whether to play or stop the music
    if (music) {
        // If 'music' is true, play the music
        MusicPlayer->play();
    } else {
        // If 'music' is false, stop the music playback
        MusicPlayer->stop();
    }
}


void PhysicsWorld::showBackground() {
    // Load the background image
    QPixmap background("://Resources/Images/Level1.webp");

    // Scale the background image to fit the window size (adjust as needed)
    background = background.scaled(1920, 1080, Qt::IgnoreAspectRatio);

    // Create a palette to set the background image
    QPalette pal;

    // Set the background image as the window's background using the palette
    pal.setBrush(QPalette::Window, background);
    this->setPalette(pal);
}


void PhysicsWorld::setTowers(QVector<Obstacles *> Towers) {
    towers = Towers;
}

void PhysicsWorld::setEnemies(QVector<Obstacles *> e) {
    enemies = e;
}

int PhysicsWorld::getCurrentLevel(){return currentLevel;}

void PhysicsWorld::setCurrentLevel(int index)
{
    currentLevel=index;

}

void PhysicsWorld::BeginContact(b2Contact *contactPoint) {
    b2Fixture *fixtureA = contactPoint->GetFixtureA();
    b2Fixture *fixtureB = contactPoint->GetFixtureB();

    b2Body *bodyA = fixtureA->GetBody();
    b2Body *bodyB = fixtureB->GetBody();

    // Cast the user data back to char* and print it
    char *userDataA = static_cast<char *>(bodyA->GetUserData());
    char *userDataB = static_cast<char *>(bodyB->GetUserData());


    qDebug() << "Collision detected! " << userDataA << " : " << userDataB;

    // Check if the collision is between a rocket and a tower
// Check if the collision is between a rocket and a tower
    if ((strcmp(userDataA, "Rocket") == 0 && strcmp(userDataB, "Tower") == 0) ||
        (strcmp(userDataA, "Tower") == 0 && strcmp(userDataB, "Rocket") == 0)) {
        // Handle the collision between the rocket and the tower
        // ...
        // Instantiate a QMediaPlayer for music playback
        QMediaPlayer* newMusicPlayer = new QMediaPlayer;

        // Instantiate a QAudioOutput for sound output
        QAudioOutput* newSpeaker = new QAudioOutput;

        // Set the source URL for the music (adjust the path as needed)
        newMusicPlayer->setSource(QUrl("qrc:/Resources/Audio/TowerBreak.mp3"));

        // Set the audio output for the music player
        newMusicPlayer->setAudioOutput(newSpeaker);

        // Set the volume level for the music (adjust as needed)
        newSpeaker->setVolume(20);

        //Play the effect
        newMusicPlayer->play();

        //delete newMusicPlayer;

        //delete newSpeaker;

        b2Body *towerBody = (strcmp(userDataA, "Tower") == 0) ? bodyA : bodyB;
        for (auto it = towers.begin(); it != towers.end(); ++it) {
            if ((*it)->get_body() == towerBody) {
                qDebug() << "Collision inside! " << (*it)->getHealth() << " : " << userDataB;

                (*it)->applyDamage(80);
                qDebug() << "Collision damage! " << (*it)->getHealth() << " : " << userDataB;
            }
            if ((*it)->getHealth() <= 0) {
                towerBody->SetUserData((void *) "TO_DELETE");

//                towers.erase(it);
                continue;
            }

        }
        towers.erase(std::remove_if(towers.begin(), towers.end(),
                                    [](const Obstacles *tower) { return tower->getHealth() <= 0; }),
                     towers.end());

        // Remove towers with health less than or equal to zero
    }
    // Check if the collision is between a rocket and an evil guy
    if ((strcmp(userDataA, "Rocket") == 0 && strcmp(userDataB, "EvilGuy") == 0) ||
        (strcmp(userDataA, "EvilGuy") == 0 && strcmp(userDataB, "Rocket") == 0)) {
        // Handle the collision between the rocket and the evil guy
        // ...
        // Instantiate a QMediaPlayer for music playback
        QMediaPlayer* newMusicPlayer = new QMediaPlayer;

        // Instantiate a QAudioOutput for sound output
        QAudioOutput* newSpeaker = new QAudioOutput;

        // Set the source URL for the music (adjust the path as needed)
        newMusicPlayer->setSource(QUrl("qrc:/Resources/Audio/ROBLOX Oof Sound Effect.mp3"));

        // Set the audio output for the music player
        newMusicPlayer->setAudioOutput(newSpeaker);

        // Set the volume level for the music (adjust as needed)
        newSpeaker->setVolume(20);

        //Play the effect
        newMusicPlayer->play();

        //delete newMusicPlayer;

        //delete newSpeaker;

        b2Body *evilGuyBody = (strcmp(userDataA, "EvilGuy") == 0) ? bodyA : bodyB;
        if (evilGuyBody) {
            contactPoint->SetEnabled(false);
            // ... other logic related to evil guy collision
        }
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            if ((*it)->get_body() == evilGuyBody) {
                qDebug() << "Collision inside! " << (*it)->getHealth() << " : " << userDataB;

                (*it)->applyDamage(80);


                qDebug() << "Collision damage! " << (*it)->getHealth() << " : " << userDataB;

            }
                if ((*it)->getHealth() <= 0) {
                    // Mark the enemy for deletion
                    evilGuyBody->SetUserData((void*)"TO_DELETE");
//                    enemies.erase(it);
                    continue;
                }
        }
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                     [](const Obstacles *enemy) { return enemy->getHealth() <= 0; }),
                      enemies.end());

        if(enemies.empty())
        {
                MidMenu *midmenu = new MidMenu;

                midmenu->get_startmenu(Menu);

                midmenu->get_window(this);

                counter--;

                update();

                midmenu->calculate_stars();

                midmenu->show();

                timer->start(500000); // Adjust the timer interval as needed

        }

    }

}

void PhysicsWorld::get_startmenu(StartMenu* start)
{
    Menu = start;
}

void PhysicsWorld::set_currentlevelindex(int curr)
{
    currentlevelindex = curr;
}

int PhysicsWorld::get_winoffset()
{
    return winoffset;
}

void PhysicsWorld::set_winoffset(int wincon)
{
    winoffset= wincon;
}

int PhysicsWorld::get_counter()
{
    return counter;
}

//void PhysicsWorld::BeginContact(
//        b2Contact *contactPoint) //cp will tell you which fixtures collided, now we look at which body they are attached to, now which particles are assosiated with these bodies?
//{//SetUserData and GetUserData are in body class:
//    //we set a name to a body
//
//    b2Fixture *EvilGuyF = contactPoint->GetFixtureA();
//    b2Fixture *RocketF = contactPoint->GetFixtureB();
//
//    b2Body *EvilGuy = EvilGuyF->GetBody();
//    b2Body *Rocket = RocketF->GetBody();
//    if (EvilGuy->GetUserData() && Rocket->GetUserData()) {
//
//        qDebug() << "Collision detected! " << static_cast<char *>(EvilGuy->GetUserData()) << " : "
//                 << static_cast<char *>(Rocket->GetUserData()) << " : " << (void *) "Rocket" << " : "
//                 << (void *) "EvilGuy";
//    }
//    bool isRocketEvilGuyCollision =
//            ((EvilGuy->GetUserData() == (void *) "Rocket" && Rocket->GetUserData() == (void *) "EvilGuy") ||
//             (EvilGuy->GetUserData() == (void *) "EvilGuy" && Rocket->GetUserData() == (void *) "Rocket"));
//
//    qDebug() << (EvilGuy->GetUserData() == (void *) "EvilGuy");
//    // Check if either fixture is associated with the EvilGuy
//    //    bool EvilGuy = (EvilGuyF->GetBody()->GetUserData() == (void*)"EvilGuy");
//    //    bool Rocket = (RocketF->GetBody()->GetUserData() == (void*)"Rocket");
//
//    // Check if the contact involves EvilGuy
//
//    b2Body *evilGuyBody = (EvilGuy->GetUserData() == (void *) "EvilGuy") ? EvilGuy : Rocket;
//    if (isRocketEvilGuyCollision) {
//        qDebug() << "Collision detected inside!";
//        contactPoint->SetEnabled(false);
//
//        b2World *world = evilGuyBody->GetWorld();
//
//        timer->start(500000);
//
//        hide();
//
//        QGraphicsScene *scene = new QGraphicsScene;
//
//        QGraphicsView *view = new QGraphicsView;
//
//        scene->setSceneRect(0, 0, 700, 600);
//
//        view->setFixedSize(700, 600);
//
//        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//
//        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//
//        view->setScene(scene);
//
//        scene->setBackgroundBrush(QBrush(QPixmap("://Resources/Images/victory.jpg").scaled(700, 600)));
//
//        view->show();
//
//    }
//    b2Fixture *fixtureA = contactPoint->GetFixtureA();
//    b2Fixture *fixtureB = contactPoint->GetFixtureB();
//
//    // Check if either fixture is associated with a tower
//    bool isTowerA = (fixtureA->GetBody()->GetUserData() == (void *) "Tower");
//    bool isTowerB = (fixtureB->GetBody()->GetUserData() == (void *) "Tower");
//
//    // Check if the contact involves a tower
//    if (isTowerA || isTowerB) {
//        // Get the tower body
//        b2Body *towerBody = isTowerA ? fixtureA->GetBody() : fixtureB->GetBody();
//
//        // Find the corresponding tower object in the towers vector
//        for (auto it = towers.begin(); it != towers.end(); ++it) {
//            if ((*it)->get_body() == towerBody) {
//                // Decrease the health of the tower
//                (*it)->applyDamage(80); // Adjust the damage value as needed
//
//                if ((*it)->getHealth() <= 0) {
//                    // If the tower's health is zero or less, remove it from the towers vector
//                    towers.erase(it);
//                }
//
//                break;
//            }
//        }
//
//
//        if (evilGuyBody) {
//
//            return;
//
//        }
//
//
//    }
//}
