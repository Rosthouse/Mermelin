/**
 * @file WoodWall.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/WoodWall.h"
#include "Entities/Sphere.h"

using namespace CotopaxiEngine;

WoodWall::WoodWall(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "Wall_Wood", parentNode)
{
    this->state = NORMAL;
}

void WoodWall::receiveEvent(Event event)
{
    if (event.getType() == Event::COLLISION_ENTER) {
        Sphere* playerSphere = dynamic_cast<Sphere*> (event.entity);

        if (playerSphere != NULL) {
            if (playerSphere->getState() == Element::FIRE) {
                this->getNode()->getParent()->removeChild(this->getNode());
                ENGINE->getPhysics()->removeComponent(this->getName());
            }
        }
    }
}