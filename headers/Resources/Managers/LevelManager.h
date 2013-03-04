/**
 * @file LevelManager.h
 * @brief Responsible for accessing level resources.
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <OgreResourceManager.h>
#include "Resources/Files/Level.h"

namespace CotopaxiEngine {

    /**
     * @class LevelManager
     * @brief Responsible for accessing level resources.
     */
    class LevelManager : public Ogre::ResourceManager, public Ogre::Singleton<LevelManager>
    {
    protected:
        Ogre::Resource* createImpl(const Ogre::String& name,
                Ogre::ResourceHandle handle,
                const Ogre::String& group,
                bool isManual, Ogre::ManualResourceLoader* loader,
                const Ogre::NameValuePairList* createParams);

    public:
        LevelManager();
        virtual ~LevelManager();

        /**
         * @fn load
         * Loads the Level using the resource manager from Ogre.
         * @param name Name of the level file (ex. level1.txt")
         * @param group The resource group in Ogre
         * @return An instance of Level.
         */
        virtual LevelPtr load(const Ogre::String& name, const Ogre::String& group);

        /**
         * @fn getSingleton
         * Makes use of the Ogre template class OgreSingleton to creating a single-instance
         * of LevelManager.
         * @return A LevelManager instance.
         */
        static LevelManager& getSingleton();

        /**
         * @fn getSingletonPtr
         * Makes use of the Ogre template class OgreSingleton to creating a single-instance
         * of LevelManager.
         * @return A pointer to a LevelManager instance.
         */
        static LevelManager* getSingletonPtr();
    };
}


#endif