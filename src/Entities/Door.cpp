/**
 * @file Door.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Engine.h"
#include "Components/GraphicComponent.h"
#include "Modules/GraphicModule.h"
#include "Entities/Door.h"
#include "Logic/Trigger.h"
#include "Modules/PhysicsModule.h"
#include "Components/PhysicsComponent.h"

using namespace CotopaxiEngine;

Door::Door(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "Door_Arc", parentNode), state(CLOSED)
{
    this->addComponent(ENGINE->getGraphic()->getComponent(this));
    leftDoor = ENGINE->createEntity("leftDoor_" + name, "Door_Left", this->getNode());
    leftDoor->addComponent(ENGINE->getGraphic()->getComponent(leftDoor));
    leftDoor->addComponent(ENGINE->getPhysics()->getComponent(leftDoor, 0, PhysicsModule::TRIMESH, PhysicsModule::COL_STATIC, PhysicsModule::COL_PLAYER, false));

    rightDoor = ENGINE->createEntity("rightDoor_" + name, "Door_Right", this->getNode());
    rightDoor->addComponent(ENGINE->getGraphic()->getComponent(rightDoor));
    rightDoor->addComponent(ENGINE->getPhysics()->getComponent(rightDoor, 0, PhysicsModule::TRIMESH, PhysicsModule::COL_STATIC, PhysicsModule::COL_PLAYER, false));

	leftDoor->registerListener(Event::ANIMATION_ENDED, this);
	leftDoor->registerListener(Event::ANIMATION_ENDED, this);
}

Door::~Door()
{
	ENGINE->removeEntity(leftDoor);
	ENGINE->removeEntity(rightDoor);
	leftDoor = NULL;
	rightDoor = NULL;
}

void Door::open()
{
    state = OPENING;
    leftDoor->getGraphicComponent()->setAnimation("OpenLeftDoor");
    rightDoor->getGraphicComponent()->setAnimation("OpenRightDoor");
}

void Door::receiveEvent(Event* event)
{
    if (event->getType() == Event::CONDITION_FULFILLED) {
        if(state == CLOSED) {
            open();
        }
    }

	if(event->getType() == Event::ANIMATION_ENDED)
	{        
		if(state == Door::OPENING) {
			state = OPEN;		
			rightPhysics = dynamic_cast<PhysicsComponent*>(ENGINE->getPhysics()->getComponent(rightDoor));
			rightPhysics->setActive(false);
			leftPhysics = dynamic_cast<PhysicsComponent*>(ENGINE->getPhysics()->getComponent(leftDoor));
			leftPhysics->setActive(false);            
		}
	}

    if (event->getType() == Event::TRANSLATE) {
        Event* e = new Event(Event::PHYSICS_UPDATE);
        leftDoor->receiveEvent(e);
        rightDoor->receiveEvent(e);
        delete e;
    }
}

void Door::addComponent(BaseComponent* component)
{
    Entity::addComponent(component);

    Trigger* trigger = dynamic_cast<Trigger*> (component);

    if (trigger != NULL) {
        this->registerListener(Event::COLLISION_ENTER, component);
        this->registerListener(Event::COLLISION_EXIT, component);
    }
}