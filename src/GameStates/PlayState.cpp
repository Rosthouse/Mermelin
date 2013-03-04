/**
 * @file PlayState.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "GameStates/PlayState.h"
#include "Engine.h"
#include "Resources/Managers/LevelManager.h"
#include "Entities/Sphere.h"
#include "Shaders/EarthShader.h"

using namespace CotopaxiEngine;

PlayState::PlayState()
:level(1)
{
	changeLevel = false;
	ENGINE->registerForEventType(this, Event::LEVEL_END);
}

void PlayState::load()
{
    ENGINE->setState(ENGINE->STATE_STOPPED);
	
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    LevelManager::getSingleton().load("level_" + std::to_string(((long double) level)) + ".txt",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
#else
    LevelManager::getSingleton().load("level_" + std::to_string(level) + ".txt",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
#endif
	Entity* sphere = NULL;
   
	if(!loaded)
	{
		sphere = sphere = ENGINE->produceEntity("sphere", "playerSphere");
		ground = ENGINE->produceEntity("groundplate", "GroundPlate");
		ground->receiveEvent(new Event(Event::TRANSLATE));
	} else {
		sphere = ENGINE->getEntity("playerSphere");
	}

	sphere->getNode()->setPosition(ENGINE->getStartPosition());
	sphere->receiveEvent(new Event(Event::TRANSLATE));
	ENGINE->getCamera()->attachTo(sphere);

    loaded = true;
}

void PlayState::loadNext()
{
	LevelManager::getSingleton().unload("level_" + std::to_string(((long double)level)) + ".txt");
	ENGINE->removeEntity(ground);
    level++;
    load();
}

void PlayState::receiveEvent(Event* e)
{
	if(e->getType() == Event::LEVEL_END)
	{
		changeLevel = true;
	}
}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt)
{
	if(changeLevel)
	{
		loadNext();
		changeLevel = false;
	}

	return true;
}
