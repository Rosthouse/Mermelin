/**
 * @file AudioManager.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Resources/Managers/AudioManager.h"
using namespace CotopaxiEngine;

template<> AudioManager *Ogre::Singleton<AudioManager>::ms_Singleton = 0;

AudioManager *AudioManager::getSingletonPtr()
{
    return ms_Singleton;
}

AudioManager &AudioManager::getSingleton()
{
    assert(ms_Singleton);
    return (*ms_Singleton);
}

AudioManager::AudioManager()
{
    mResourceType = "Audio";

    // low, because it will likely reference other resources
    mLoadOrder = 30.0f;

    // this is how we register the ResourceManager with OGRE
    Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

AudioManager::~AudioManager()
{
    // and this is how we unregister it
    Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

AudioPtr AudioManager::load(const Ogre::String &name, const Ogre::String &group, Audio::MODE mode)
{
    AudioPtr audioPtr = getByName(name);

    if (audioPtr.isNull()) {
        audioPtr = create(name, group, mode);
    }

    audioPtr->load();
    return audioPtr;
}

Ogre::Resource *AudioManager::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle,
        const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader,
        const Ogre::NameValuePairList *createParams)
{
    return new Audio(this, name, handle, group, Audio::MODE::SOUND, isManual, loader);
}