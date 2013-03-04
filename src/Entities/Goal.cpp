/**
 * @file Goal.cpp
 * @authors Patrick Joos, Eduardo Hahn Paredes
 */
#include "stdafx.h"
#include "Entities/Goal.h"
#include "Entities/Sphere.h"

using namespace CotopaxiEngine;

Goal::Goal(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "Floor", parentNode)
{
    this->addComponent(ENGINE->getGraphic()->getComponent(this));
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingletonPtr()
            ->create("Goal", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::TextureUnitState* texture = material->getTechnique(0)->getPass(0)
            ->createTextureUnitState("goal_color.gif");

    this->getOgreEntity()->setMaterial(material);
    
    //this->addComponent(ENGINE->getPhysics()->getComponent(this, 0,
    //        PhysicsModule::TRIMESH, PhysicsModule::COL_GHOST, PhysicsModule::COL_PLAYER, true));
}

void Goal::receiveEvent(Event* e)
{
    if (e->getType() == Event::COLLISION_ENTER) {
        Sphere* sphere = dynamic_cast<Sphere*> (e->entity);
        if (sphere != NULL) {
            /*sphere->getNode()->setPosition(ENGINE->getStartPosition());

            Event* e = new Event(Event::TRANSLATE);
            sphere->receiveEvent(e);*/

			ENGINE->throwEvent(Event::LEVEL_END);
            delete e;
        }
	} else if(e->getType() == Event::TRANSLATE)
	{
		ENGINE->getPhysics()->getComponent(this)->receiveEvent(e);
	}else
	{
        Entity::receiveEvent(e);
    }
}

