/**
 * @file TypeChanger.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/TypeChanger.h"

using namespace CotopaxiEngine;

TypeChanger::TypeChanger(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "TypeChanger", parentNode)
{
    this->addComponent(ENGINE->getGraphic()->getComponent(this));
    symbolBar = ENGINE->createEntity("bar_" + name, "TypeChangerAE", this->getNode());
    symbolBar->addComponent(ENGINE->getGraphic()->getComponent(symbolBar));
    symbolTriangle = ENGINE->createEntity("triangle_" + name, "TypeChangerElement", this->getNode());
    symbolTriangle->addComponent(ENGINE->getGraphic()->getComponent(symbolTriangle));
}

TypeChanger::~TypeChanger()
{
}

void TypeChanger::setElement(CotopaxiEngine::Element element)
{
    this->element = element;

    switch (element)
    {
        case Element::AIR:
            symbolTriangle->getGraphicComponent()->setShader(new AirShader(symbolTriangle));
            symbolBar->getGraphicComponent()->setShader(new AirShader(symbolBar));
            break;
        case Element::EARTH:
            symbolTriangle->getGraphicComponent()->setShader(new EarthShader(symbolTriangle));
            symbolBar->getGraphicComponent()->setShader(new EarthShader(symbolBar));
            break;
        case Element::FIRE:
            symbolTriangle->getGraphicComponent()->setShader(new FireShader(symbolTriangle));
            break;
        case Element::WATER:
            symbolTriangle->getGraphicComponent()->setShader(new WaterShader(symbolTriangle));
            break;
    }
}

void TypeChanger::receiveEvent(Event* e)
{
    if (e->getType() == Event::COLLISION_ENTER) {
        Sphere* sphere = dynamic_cast<Sphere*> (e->entity);
        if (sphere != NULL) {
            sphere->setElement(this->element);
        }
    } else {
        Entity::receiveEvent(e);
    }
}