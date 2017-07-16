/**
 * @file Audio.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Resources/Files/Audio.h"

using namespace CotopaxiEngine;

Audio::Audio(Ogre::ResourceManager* creator,
        const Ogre::String &name,
        Ogre::ResourceHandle handle,
        const Ogre::String &group,
        MODE mode,
        bool isManual,
        Ogre::ManualResourceLoader *loader)
: Ogre::Resource(creator, name, handle, group, isManual, loader), sf::Thread(&Audio::Run, this)
{
    createParamDictionary("Audio");
    this->mode = mode;
}

Audio::~Audio()
{
    unload(); 
}

void Audio::loadImpl()
{
    Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(mName, 
            mGroup);

    std::vector<char> bytes;

    // settin output values
    bytes.resize(stream->size());

    // getting the binary file contents
    stream->read(&bytes[0], bytes.size());

    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    buffer->loadFromMemory(&bytes[0], bytes.size());

    sound = new sf::Sound(*buffer);
}

void Audio::unloadImpl() { }

size_t Audio::calculateSize() const
{
    return 0;
}

sf::Sound* Audio::getAudio()
{
    return this->sound;
}