/**
 * @file GhostComponent.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Components/GhostComponent.h"

using namespace CotopaxiEngine;

GhostComponent::GhostComponent(btScalar mass, PhysicsModule::Shape s, short group, short mask)
: PhysicsComponent(mass, s, group, mask) { 
}

GhostComponent::~GhostComponent()
{
	ENGINE->getPhysics()->removeComponent(this->parent->getName());

	ENGINE->getPhysics()->getWorld()->removeCollisionObject(ghostObject);

    delete ghostObject;
}

void GhostComponent::setParent(Entity* entity)
{
    PhysicsComponent::setParent(entity);

    btCollisionShape* ghostShape;
    this->ghostObject = new btGhostObject();

    BtOgre::StaticMeshToShapeConverter* converter =
            new BtOgre::StaticMeshToShapeConverter(this->physicsEntity);

    if (this->physicsShape == PhysicsModule::PLANE) {
        ghostShape = converter->createPlane();
    } else {
        ghostShape = converter->createBox();
        ghostShape->setLocalScaling(btVector3(0.5, 0.5, 0.5));
    }

    Ogre::Vector3 position = this->parent->getNode()->_getDerivedPosition();

    btTransform trans(btTransform(btQuaternion(0, 0, 0, 1), BtOgre::Convert::toBullet(position)));

    this->ghostObject->setCollisionShape(ghostShape);
    this->ghostObject->setUserPointer(this);
    this->ghostObject->setWorldTransform(trans);

    this->ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE
            | this->ghostObject->getCollisionFlags());

    ENGINE->getPhysics()->getWorld()->addCollisionObject(ghostObject,
            PhysicsModule::CollisionMask::COL_GHOST, PhysicsModule::CollisionMask::COL_PLAYER);
}

btGhostObject* GhostComponent::getGhost()
{
    return this->ghostObject;
}

void GhostComponent::checkOverlappingObjects()
{
    int max = ghostObject->getNumOverlappingObjects();
    std::set<std::string> currentlyCollidingObjects;

    for (int i = 0; i < max; i++) {
        btCollisionObject* collidee = ghostObject->getOverlappingObject(i);
        PhysicsComponent* component = static_cast<PhysicsComponent*> (collidee->getUserPointer());

        std::string colliderName = component->getParent()->getName();
        currentlyCollidingObjects.insert(colliderName);

        std::set<std::string>::iterator colliderIterator = lastKnownColliders.begin();

        bool previouslyCollided = false;

        for (; colliderIterator != lastKnownColliders.end(); colliderIterator++) {
            if (colliderName == *colliderIterator) {
                previouslyCollided = true;
            }
        }

        Event* e;

        if (!previouslyCollided) {
            e = new Event(Event::COLLISION_ENTER);
        } else {
            e = new Event(Event::COLLISION);
        }

        e->entity = component->getParent();
        this->parent->receiveEvent(e);
        //delete e;
    }

    int setDeltas = lastKnownColliders.size() - currentlyCollidingObjects.size();

    if (setDeltas > 0) {

        // handling exit collisions
        std::vector<std::string>::iterator it;
        std::vector<std::string> delta(setDeltas);

        it = std::set_difference(lastKnownColliders.begin(),
                lastKnownColliders.end(),
                currentlyCollidingObjects.begin(),
                currentlyCollidingObjects.end(),
                delta.begin());

        for (; it != delta.end(); it++) {
            Entity* exitCollision = ENGINE->getEntity(*it);
            Event* exitEvent = new Event(Event::COLLISION_EXIT);
            exitEvent->entity = exitCollision;
            parent->receiveEvent(exitEvent);
            delete exitEvent;
        }
        //@todo delete events after sending them. Right now they all remain on the heap
    }

    lastKnownColliders = currentlyCollidingObjects;
}

void GhostComponent::receiveEvent(Event* e)
{
	if(e->getType() == Event::TRANSLATE)
	{
		btTransform transform;

        transform.setIdentity();
        Ogre::Vector3 position = parent->getNode()->_getDerivedPosition();
        Ogre::Quaternion orientation = parent->getNode()->_getDerivedOrientation();

		transform.setOrigin(BtOgre::Convert::toBullet(position));
		transform.setRotation(BtOgre::Convert::toBullet(orientation));

		ghostObject->setWorldTransform(transform);
	}
}