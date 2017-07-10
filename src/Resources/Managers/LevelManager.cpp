/**
 * @file LevelManager.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Resources/Managers/LevelManager.h"
using namespace CotopaxiEngine;

template<> LevelManager* Ogre::Singleton<LevelManager>::ms_Singleton = 0;

LevelManager* LevelManager::getSingletonPtr()
{
    return ms_Singleton;
}

LevelManager& LevelManager::getSingleton()
{
    assert(ms_Singleton);
    return (*ms_Singleton);
}

LevelManager::LevelManager()
{
    mResourceType = "Level";
    mLoadOrder = 30.0f;

    Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);

}

LevelManager::~LevelManager()
{
    Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

LevelPtr LevelManager::load(const Ogre::String& name, const Ogre::String& group)
{
    LevelPtr level = getByName(name);

    if (level.isNull())
        level = create(name, group);

    level->load();
    return level;
}

Ogre::Resource* LevelManager::createImpl(const Ogre::String& name,
        Ogre::ResourceHandle handle,
        const Ogre::String& group,
        bool isManual, Ogre::ManualResourceLoader* loader,
        const Ogre::NameValuePairList* createParams)
{
    return new Level(this, name, handle, group, isManual, loader);
}