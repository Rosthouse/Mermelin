/**
 * Entity.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/Entity.h"
#include "Components/BaseComponent.h"
#include "Modules/GraphicModule.h"
#include "Engine.h"

using namespace std;
using namespace CotopaxiEngine;

Entity::Entity(){}

Entity::Entity(std::string name, std::string meshName, Ogre::SceneNode* parentNode) {
    this->name = name;
    this->node = parentNode->createChildSceneNode(name);

    if (meshName != "") {
        ogreEntity = ENGINE->getSceneManager()->createEntity(meshName + ".mesh");
        this->node->attachObject(ogreEntity);        
    } else {
        ogreEntity = NULL;
    }	
}

Entity::~Entity()
{
	for(ComponentVector::iterator it = components.begin(); it != components.end(); it++)
	{
		delete *it;
	}
}

void Entity::addComponent(BaseComponent *component) {
    components.push_back(component);
}

void Entity::registerListener(const Event::EventType& type, EventListener* listener) {

    eventListeners[type].push_back(listener);

    ENGINE->registerForEventType(this, type);
}

void Entity::receiveEvent(Event* e) {

	EventListenerVector::iterator it = eventListeners[e->getType()].begin();

    for (; it != eventListeners[e->getType()].end(); ++it) {
        (*it)->receiveEvent(e);
    }

}

void Entity::setParentNode(Ogre::SceneNode* newParent) {
    this->node->getParentSceneNode()->removeChild(this->node);

    newParent->addChild(node);
}

Ogre::SceneNode* Entity::getNode() const {
    return node;
}

void Entity::setOgreEntity(Ogre::Entity* ogreEntity) {
    this->ogreEntity = ogreEntity;
}

Ogre::Entity* Entity::getOgreEntity() const {
    return ogreEntity;
}

void Entity::setGraphicComponent(GraphicComponent* graphicComponent) {
    this->graphicComponent = graphicComponent;
}

GraphicComponent* Entity::getGraphicComponent() const {
    return graphicComponent;
}

void Entity::setName(std::string name) {
    this->name = name;
}

std::string Entity::getName() const {
    return name;
}

void Entity::removeComponent(BaseComponent* component)
{
	ComponentVector::iterator index = std::find(components.begin(), components.end(), component);


	this->components.erase(index);
}