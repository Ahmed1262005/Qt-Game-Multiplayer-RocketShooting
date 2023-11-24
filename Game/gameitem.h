#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>


class GameItem : public QObject{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
public slots:
    void paint();
protected:
    b2Body *gBody;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *world;
    static QSizeF worldsize, g_windowsize;

};

#endif // GAMEITEM_H
