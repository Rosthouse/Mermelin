/**
 * AudioModule.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Components/AudioComponent.h"
#include "Entities/Camera.h"

using namespace CotopaxiEngine;

PlaySound* AudioModule::playSound(std::string path, bool loop)
{
    PlaySound* sound = new PlaySound(path, loop);
    sound->play();
    return sound;
}

PlayMusic* AudioModule::playMusic(std::string path, bool loop)
{
    PlayMusic* music = new PlayMusic(path, loop);
    music->play();
    return music;
}

void AudioModule::stopSound(PlaySound* sound)
{
    delete sound;
}

void AudioModule::stopMusic(PlayMusic* music)
{
    delete music;
}

BaseComponent* AudioModule::getComponent(Entity* parent)
{
    AudioComponent* component = new AudioComponent();
    component->setParent(parent);
    components.push_back(component);
    return (BaseComponent*) components.back();
}

void AudioModule::setGlobalVolume(float volume)
{
    float internalVolume = volume;

    if (internalVolume > 100.0) {
        internalVolume = 100.0;
    }
    if (internalVolume < 0.0) {
        internalVolume = 0.0;
    }

    sf::Listener::SetGlobalVolume(internalVolume);
}

bool AudioModule::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    Ogre::Vector3 position = ENGINE->getCamera()->getNode()->_getDerivedPosition();
    sf::Listener::SetPosition(position.x, position.y, position.z);
    return true;
}