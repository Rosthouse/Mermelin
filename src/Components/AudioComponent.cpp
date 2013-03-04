/**
 * AudioComponent.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Components/AudioComponent.h"

using namespace CotopaxiEngine;

AudioComponent::AudioComponent() {}

AudioComponent::~AudioComponent()
{
	for(std::map<std::string, Audio*>::iterator it = audioList.begin(); it != audioList.end(); it++)
	{
		delete it->second;
	}
}

bool AudioComponent::addSound(std::string soundName)
{
    Audio* audio = AudioManager::getSingleton().load(soundName + ".ogg", 
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME).getPointer();
    if (audio->isLoaded()) {
        Ogre::Vector3 position = this->getParent()->getNode()->_getDerivedPosition();

        audio->getAudio()->SetPosition(position.x, position.y, position.z);
        audioList[soundName] = audio;
        return true;
    }

    return false;
}

void AudioComponent::removeSound(std::string soundName) {
    //@todo IMPLEMENT
}

bool AudioComponent::play(std::string name, bool loop)
{
    Audio* audioToPlay = audioList[name];
    if (audioToPlay != NULL) {
        audioToPlay->getAudio()->SetLoop(loop);
        audioToPlay->getAudio()->Play();
        return true;
    }

    return false;
}

void AudioComponent::stop(std::string soundName)
{
    Audio* audioToPlay = audioList[soundName];
    if (audioToPlay != NULL) {
        audioToPlay->getAudio()->Pause();
    }
}

void AudioComponent::receiveEvent(Event* e)
{
	if(e->getType() == Event::TRANSLATE)
	{
		std::map<std::string, Audio*>::iterator it = audioList.begin();

		Ogre::Vector3 position = getParent()->getNode()->_getDerivedPosition();

		for(;it!= audioList.end(); it++)
		{
			it->second->getAudio()->SetPosition(position.x, position.y, position.z);
		}
	}

    BaseComponent::receiveEvent(e);
}

void AudioComponent::setParent(Entity* e)
{
	BaseComponent::setParent(e);

	e->registerListener(Event::TRANSLATE, this);
}
