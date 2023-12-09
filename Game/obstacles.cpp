#include "obstacles.h"
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>

Obstacles::Obstacles(float x, float y, float width, float height, QPixmap pixmap, b2World *world,
                     qreal density /* = 10.0f */, qreal friction /* = 0.2f */, qreal restitution /* = 0.2f */)
    : GameItem(world), health(100) {

    // Initialize QGraphicsPixmapItem to display the obstacle
    g_pixmap.setPixmap(pixmap.scaled(width, height));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width() / 2, g_pixmap.boundingRect().height() / 2);
    g_size = QSize(width, height);

    this->x = x;
    this->y = y;

    // Box2D body definition for the obstacle
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x, y);
    bodydef.userData = this; // Set user data to this obstacle
    gBody = world->CreateBody(&bodydef);

    // Box2D shape for the obstacle body
    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(width / 2, height / 2);

    // Fixture definition for the obstacle body
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = density;
    fixturedef.friction = friction;
    fixturedef.restitution = restitution;
    gBody->SetAngularDamping(3);
    gBody->CreateFixture(&fixturedef);
    gBody->SetUserData((void*)"Tower"); // Set user data for Box2D body

}

// Return the obstacle's pixmap
QPixmap Obstacles::get_pixmap() {
    return g_pixmap.pixmap();
}

// Get the X-coordinate of the obstacle (scaled)
int Obstacles::get_x() {
    return x * 25;
}

// Get the Y-coordinate of the obstacle (scaled)
int Obstacles::get_y() {
    return (-y) * 25;
}

// Get the size of the obstacle
QSizeF Obstacles::get_size() {
    return g_size;
}

// Get the Box2D body of the obstacle
b2Body *Obstacles::get_body() {
    return gBody;
}

// Apply damage to the obstacle
void Obstacles::applyDamage(int damage) {
    setHealth(health - damage);
    if (health <= 0) {
        // If obstacle is destroyed, play a sound effect
        QMediaPlayer* MusicPlayer = new QMediaPlayer;
        QAudioOutput* Speaker = new QAudioOutput;

        MusicPlayer->setSource(QUrl("qrc:/Resources/Audio/buildfaileffect.mp3"));
        MusicPlayer->setAudioOutput(Speaker);
        Speaker->setVolume(20);
        MusicPlayer->setLoops(-1);

        MusicPlayer->play();
    }
}

// Set the health of the obstacle
void Obstacles::setHealth(int h) {
    health = h;
    if (health <= 0) {
        // If obstacle is destroyed, perform any additional actions
        // emit enemyDestroyed();
    }
}

// Get the current health of the obstacle
int Obstacles::getHealth() const {
    return health;
}
