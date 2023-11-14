#include "material.h"


Material::Material(QString name, float density, float friction, float restution, QPixmap pix)
    :name(name), density(density), friction(friction), restution(restution), pix(pix)
{
}

Material *Material::fromName(QString name)
{
    if(name == "King")
        return king();
    if(name == "Strip")
        return strip();
    if(name == "Foreman")
        return foreman();
    if(name == "Fat Pig")
        return fatPig();
    if(name == "Wood Box")
        return woodBox();
    if(name == "Soldier")
        return soldier();
    if(name == "Professor")
        return professor();
    if(name == "Wood VBox")
        return woodVRect();
	if(name == "Corporal Pig")
		return corporal();
    if(name == "Red Bird")
		return red();
	if(name == "Bomb")
		return bomb();
    if(name == "Chunk")
        return chunk();
    if(name == "Blue")
        return blue();
	if(name == "Terence")
		return terence();
    if(name == "Stone Box")
        return stoneBox();
    if(name == "Melon")
        return melon();
    if(name == "Wood HBox")
        return woodHrect();
    if(name == "Wood Table")
        return woodTable();
    if(name == "Wood HBox")
        return woodHrect();
    if(name == "Ice Box")
        return iceBox();
    if(name == "Ice VBox")
        return iceVrect();
    if(name == "Ice HBox")
        return iceHrect();
    if(name == "Stone VBox")
        return stoneVRect();
    if(name == "Stone HBox")
        return stoneHRect();
    if(name == "Ground1")
        return ground_1();
    if(name == "Ground2")
        return ground_2();
    if(name == "Sky")
        return sky();
    if(name == "Dark Sky")
        return darkSky();
    if(name == "Red Sky")
        return redSky();
    if(name == "Sun")
        return sun();
    if(name == "Satellite")
        return satellite();
    if(name == "Hill")
        return hill();
    if(name == "Wood Triangle1")
        return woodTriangle1();
    if(name == "Ice Triangle")
        return iceTriangle();
    if(name == "Stone Triangle")
        return stoneTriangle();
    if(name == "Wood Triangle")
        return woodTriangle();
    if(name == "Grass")
        return grass();
    if(name == "Wide Table")
        return wideTable();
    if(name == "Ground3")
        return ground3();
    if(name == "Blue Sky")
        return blueSky();
    if(name == "Cloud1")
        return cloud1();
    if(name == "Cloud2")
        return cloud2();
    if(name == "Jungle")
        return jungle();
}

Material *Material::king()
{
    return new Material("king", .5f, 1.0f, 0.25f, QPixmap(":/piggs/piggs/king.png"));
}

Material *Material::foreman()
{
    return new Material("foreman", .6f, 1.0f, .4f, QPixmap(":/piggs/piggs/foreman.png"));
}

Material *Material::soldier()
{
    return new Material("soldier", .4f, 1.0f, .25f, QPixmap(":/piggs/piggs/sodier.png"));
}

Material *Material::professor()
{
    return new Material("professor", .5f, .9f, .25f, QPixmap(":/piggs/piggs/professor.png"));
}

Material *Material::fatPig()
{
    return new Material("fat pig", .70f, .6f, .25f, QPixmap(":/piggs/piggs/Fat_pig.png"));
}

Material * Material::corporal()
{
    return new Material("corporal pig", .2f, .9f, .25f, QPixmap(":/piggs/piggs/corporal-pig.png"));
}

Material *Material::strip()
{
    return new Material("strip", 0.0f, 1.0f, .1f, QPixmap(":/fixture/fixture/strip.png"));
}

Material *Material::woodBox()
{
    return new Material("wood box", .7f, .7f, .05f, QPixmap(":/blocks/Blocks/wood_rec.png"));
}

Material *Material::woodTable()
{
    return new Material("wood table", 4.0f, .8f, .025f, QPixmap(":/blocks/Blocks/wood_table.png"));
}

Material *Material::wideTable()
{
    return new Material("wide table", 4.0f, 1.0f, .025f, QPixmap(":/blocks/Blocks/wideTable.png"));
}

Material *Material::woodVRect()
{
    return new Material("wood vbox", .5f, .7f, .025f, QPixmap(":/blocks/Blocks/wood_vrec.png"));
}

Material *Material::woodHrect()
{
    return new Material("wood hbox", .5f, .7f, .03f, QPixmap(":/blocks/Blocks/wood_hrec.png"));
}

Material * Material::red()
{
    return new Material("red", .5f, .9f, .5f, QPixmap(":/actors/Characters/red.png"));
}

Material *Material::chunk()
{
    return new Material("chunk", .5f, .9f, .5f, QPixmap(":/actors/Characters/chunk.png"));

}

Material *Material::blue()
{
    return new Material("blue", .3f, .9f, .5f, QPixmap(":/actors/Characters/blue.png"));
}

Material * Material::bomb()
{
    return new Material("bomb", .8f, .9f, .3f, QPixmap(":/actors/Characters/Bomb.png"));
}

Material * Material::terence()
{
    return new Material("terence", 3.0f, .9f, .5f, QPixmap(":/actors/Characters/terence.png"));

}

Material *Material::stoneBox()
{
    return new Material("stone box", 7.0f, .6f, .25f, QPixmap(":/blocks/Blocks/stone_rec.png"));

}

Material *Material::stoneVRect()
{
    return new Material("stone vbox", 3.0f, .6f, .25f, QPixmap(":/blocks/Blocks/stone_vrec.png"));
}

Material *Material::stoneHRect()
{
    return new Material("stone hbox", 3.0f, .6f, .25f, QPixmap(":/blocks/Blocks/stone_hrec.png"));
}

Material *Material::iceBox()
{
    return new Material("ice box", .125f, .4f, .03f, QPixmap(":/blocks/Blocks/ice_rec.png"));
}

Material *Material::iceVrect()
{
    return new Material("ice vbox", .225f, .4f, .03f, QPixmap(":/blocks/Blocks/ice_vrec.png"));
}

Material *Material::iceHrect()
{
    return new Material("ice hbox", .5f, .4f, .03f, QPixmap(":/blocks/Blocks/ice_hrec.png"));
}

Material *Material::ground_1()
{
    return new Material("ground1", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/ground1.png"));
}

Material *Material::ground_2()
{
    return new Material("ground2", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/ground2.png"));
}

Material *Material::ground3()
{
    return new Material("ground3", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/ground3.png"));
}

Material *Material::sky()
{
    return new Material("sky", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/sky.png"));
}

Material *Material::darkSky()
{
    return new Material("dark sky", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/sky3.png"));
}

Material *Material::redSky()
{
    return new Material("red sky", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/sky2.png"));
}

Material *Material::blueSky()
{
    return new Material("red sky", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/sky4.png"));
}

Material *Material::sun()
{
    return new Material("sun", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/sun.png"));
}

Material *Material::cloud2()
{
    return new Material("cloud2", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/cloude2.png"));
}

Material *Material::cloud1()
{
    return new Material("cloud1", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/cloude1.png"));
}

Material *Material::satellite()
{
    return new Material("satellite", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/satellite.png"));
}

Material *Material::hill()
{
    return new Material("hill", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/hill_b_s.png"));
}

Material *Material::jungle()
{
    return new Material("jungle", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/jungle.png"));
}

Material *Material::grass()
{
    return new Material("grass", 0.0f, 0.0f, 0.0f, QPixmap(":/fixture/fixture/grass.png"));
}

Material *Material::woodTriangle1()
{
    return new Material("wood triangle_1", .5f, .9f, .25f, QPixmap(":/blocks/Blocks/wood_triangle1.png"));
}

Material *Material::woodTriangle()
{
    return new Material("wood triangle", .5f, .9f, .25f, QPixmap(":/blocks/Blocks/wood_triangle.png"));
}

Material *Material::iceTriangle()
{
    return new Material("ice triangle", .25f, .6f, .25f, QPixmap(":/blocks/Blocks/ice_triangle.png"));
}

Material *Material::stoneTriangle()
{
    return new Material("stone triangle", 2.0f, .9f, .25f, QPixmap(":/blocks/Blocks/stone_triangle.png"));
}

Material *Material::melon()
{
    return new Material("melon", 1.0f, .2f, .70f, QPixmap(":/blocks/Blocks/melon.png"));
}


