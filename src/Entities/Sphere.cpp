/**
 * @file Shpere.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/Sphere.h"

using namespace CotopaxiEngine;

Sphere::Sphere(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "", parentNode)
{
    this->setOgreEntity(ENGINE->getSceneManager()->createEntity(name, Ogre::SceneManager::PT_SPHERE));
    this->getNode()->attachObject(this->getOgreEntity());
    this->weight = 10;
    this->state = DEFAULT;

    this->getNode()->setPosition(ENGINE->getStartPosition());
    this->getNode()->setScale(ENGINE->SCALE * 0.005, ENGINE->SCALE * 0.005, ENGINE->SCALE * 0.005);

    this->addComponent(ENGINE->getGraphic()->getComponent(this));

    int colMask = PhysicsModule::COL_STATIC |
            PhysicsModule::COL_NOTHING |
            PhysicsModule::COL_TYPECHANGER |
            PhysicsModule::COL_BUTTON |
            PhysicsModule::COL_GHOST;

    this->addComponent(ENGINE->getPhysics()->getComponent(this,
            weight,
            PhysicsModule::SPHERE,
            PhysicsModule::COL_PLAYER,
            colMask));

    ((PhysicsComponent*) ENGINE->getPhysics()->getComponent(this))->setComponentGravity(Ogre::Vector3(0, -10, 0));

    light = ENGINE->getSceneManager()->createLight("SphereLight");
    light->setVisible(false);
    light->setType(Ogre::Light::LT_POINT);
    light->setCastShadows(true);
    light->setDiffuseColour(1.0, 1.0, 1.0);
    this->getNode()->attachObject(light);
}

void Sphere::receiveEvent(CotopaxiEngine::Event* event)
{
    if (event->getType() == Event::EventType::TRANSLATE) {
//		PhysicsComponent* comp =  dynamic_cast<PhysicsComponent*>(ENGINE->getPhysics()->getComponent(this));
//		comp->setActive(false);
//		comp->setActive(true);
    } else {
        Entity::receiveEvent(event);
    }
}

void Sphere::setElement(const Element& state)
{
    this->state = state;

    switch (state) {
        case Element::AIR:
            light->setVisible(true);
            light->setPowerScale(2);
            light->setDiffuseColour(0.0, 0.0, 1.0);
            this->getGraphicComponent()->setShader(new AirShader(this));
            break;
        case Element::EARTH:
            light->setVisible(false);
            this->getGraphicComponent()->setShader(new EarthShader(this));            
            break;
        case Element::FIRE:
            light->setVisible(true);
            light->setPowerScale(7);
            light->setDiffuseColour(1.0, 0.0, 0.0);
            this->getGraphicComponent()->setShader(new FireShader(this));
            break;
        case Element::WATER:
            light->setVisible(true);
            light->setPowerScale(2);
            light->setDiffuseColour(1.0, 1.0, 1.0);
            this->getGraphicComponent()->setShader(new WaterShader(this));
            break;
    }
}