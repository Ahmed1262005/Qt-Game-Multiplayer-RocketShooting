#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QPixmap>

class Material
{
public:
    Material(QString name, float density, float friction, float restution, QPixmap pix);
    static Material *fromName(QString name);
    static Material *king();
    static Material *foreman();
    static Material *strip();
    static Material *fatPig();
	static Material *corporal();
    static Material *woodBox();
    static Material *soldier();
    static Material *professor();
    static Material *woodVRect();
	static Material *red();
    static Material *chunk();
    static Material *blue();
	static Material *bomb();
	static Material *terence();
    static Material *melon();
    static Material *woodHrect();
    static Material *stoneBox();
    static Material * stoneVRect();
    static Material *stoneHRect();
    static Material *iceBox();
    static Material *iceVrect();
    static Material *iceHrect();
    static Material *woodTable();
    static Material *wideTable();
    static Material *ground_1();
    static Material *ground_2();
    static Material *ground3();
    static Material *sky();
    static Material *darkSky();
    static Material *redSky();
    static Material *blueSky();
    static Material *sun();
    static Material *cloud1();
    static Material *cloud2();
    static Material *satellite();
    static Material *hill();
    static Material *jungle();
    static Material *grass();
    static Material *woodTriangle1();
    static Material *woodTriangle();
    static Material *iceTriangle();
    static Material *stoneTriangle();


public:
    QString name;
    float density;
    float friction;
    float restution;
    QPixmap pix;
};

#endif // MATERIAL_H
