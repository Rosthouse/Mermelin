/**
 * @file AudioManager.h
 * @brief Responsible for accessing audio resources.
 * @author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <OgreResourceManager.h>
#include "Resources/Files/Audio.h"

namespace CotopaxiEngine {

    /**
     * @class AudioManager
     * @brief Responsible for accessing audio resources.
     */
    class AudioManager : public Ogre::ResourceManager, public Ogre::Singleton<AudioManager>
    {
    protected:
        // must implement this from ResourceManager's interface
        Ogre::Resource *createImpl(const Ogre::String &name,
                Ogre::ResourceHandle handle,
                const Ogre::String &group,
                bool isManual,
                Ogre::ManualResourceLoader *loader,
                const Ogre::NameValuePairList *createParams);
    public:

        AudioManager();
        virtual ~AudioManager();

        /**
         * @fn load
         * Loads sound files using the resource manager from Ogre.
         * @param name Name of the level file (ex. level1.txt")
         * @param group The resource group in Ogre
         * @return An instance of Level.
         * @param mode An Audio::MODE
         * @return An instance of Audio.
         */
        virtual AudioPtr load(const Ogre::String &name, const Ogre::String &group, Audio::MODE mode = Audio::SOUND);

        /**
         * @fn getSingleton
         * Makes use of the Ogre template class OgreSingleton to creating a single-instance
         * of AudioManager.
         * @return An AudioManager instance.
         */
        static AudioManager &getSingleton();

        /**
         * @fn getSingletonPtr
         * Makes use of the Ogre template class OgreSingleton to creating a single-instance
         * of AudioManager.
         * @return A pointer to an AudioManager instance.
         */
        static AudioManager *getSingletonPtr();
    };
}

#endif