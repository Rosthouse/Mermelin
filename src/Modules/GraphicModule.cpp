/**
 * GraphicModule.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Modules/GraphicModule.h"
#include "Engine.h"
#include "Entities/Camera.h"

using namespace CotopaxiEngine;

GraphicModule::GraphicModule()
{
	//ENGINE->registerForEventType(this, Event::LEVEL_END);
}

BaseComponent* GraphicModule::getComponent(Entity* parent)
{
    GraphicComponent* component = new GraphicComponent();
    component->setParent(parent);

	components[parent->getName()] = component;

    //components.push_back(component);
	return (BaseComponent*) components[parent->getName()];
}

void GraphicModule::removeComponent( std::string componentName)
{
	std::map<std::string, GraphicComponent*>::iterator compToRemove = components.find(componentName);

	if(compToRemove != components.end())
	{
		components.erase(compToRemove);
	}
}

bool GraphicModule::frameRenderingQueued(const Ogre::FrameEvent& event)
{
    std::map<std::string, GraphicComponent*>::iterator it = components.begin();
    for (; it != components.end(); ++it) {
		it->second->update(event.timeSinceLastFrame);
    }
    if (ENGINE->getCamera()->isAttached()) {
        ENGINE->getCamera()->update();
    }
    return true;
}

void GraphicModule::refreshAllShaders()
{
    Ogre::GpuProgramManager::getSingletonPtr()->reloadAll();
}

void GraphicModule::receiveEvent(Event* e)
{
}