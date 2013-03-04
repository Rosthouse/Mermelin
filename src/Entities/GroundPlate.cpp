/**
 * @file GroundPlate.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/GroundPlate.h"
#include "Entities/Sphere.h"
#include "Modules/PhysicsModule.h"
#include "Components/PhysicsComponent.h"
#include "Engine.h"

using namespace CotopaxiEngine;

GroundPlate::GroundPlate(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "Floor", parentNode)
{
    this->getNode()->setPosition(0.0, -20.0, 0.0);
    this->getNode()->setVisible(true);
    //this->getNode()->setScale(100.0, 0, 100.0);

	this->addComponent(ENGINE->getGraphic()->getComponent(this));
    
    this->addComponent(ENGINE->getPhysics()->getComponent(this, 0.0, 
            PhysicsModule::PLANE, PhysicsModule::COL_GHOST, PhysicsModule::COL_PLAYER, true));
}

GroundPlate::~GroundPlate() { }

void GroundPlate::receiveEvent(Event* e)
{    
    if (e->getType() == Event::COLLISION_ENTER) {
        std::cout << "hahahhaha ENDLICH\n\n";
        Sphere* sphere = dynamic_cast<Sphere*> (e->entity);
        if (sphere != NULL) {

			
            sphere->getNode()->setPosition(ENGINE->getStartPosition());

            Event* e = new Event(Event::TRANSLATE);
            sphere->receiveEvent(e);
            delete e;
        }
    } else {
        Entity::receiveEvent(e);
    }

	if(e->getType() == Event::TRANSLATE)
	{
		int i = 1;
		ENGINE->getPhysics()->getComponent(this)->receiveEvent(e);
	}
}