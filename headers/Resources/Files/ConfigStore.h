/**
 * @file ConfigStore.h
 * @brief Enables to save settings in the Ogre configuration file
 * @author Firestryke31, Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef CONFIGSTORE_H
#define	CONFIGSTORE_H

namespace CotopaxiEngine {

    /**
     * @class ConfigStore
     * @brief Enables to save settings in the Ogre configuration file
     * 
     * This can be useful to write back changes in the configuration.
     */
    class ConfigStore : public Ogre::ConfigFile
    {
    public:
        void setSetting(const Ogre::String &key, const Ogre::String &section, const Ogre::String &value, bool append = false)
        {
            Ogre::ConfigFile::SettingsMultiMap* currentSettings;

            // finding the section
            Ogre::ConfigFile::SettingsBySection::const_iterator seci = mSettings.find(section);

            if (seci == mSettings.end()) {
                // if the section doesn't exist, creating it
                currentSettings = OGRE_NEW_T(SettingsMultiMap, Ogre::MEMCATEGORY_GENERAL)();
                mSettings[section] = currentSettings;
            } else {
                currentSettings = seci->second;
            }

            if (!append) {
                // removing the existing setting(s)
                Ogre::ConfigFile::SettingsMultiMap::iterator seti = currentSettings->find(key);

                if (seti != currentSettings->end())
                    currentSettings->erase(seti);
            }

            // adding the new setting
            currentSettings->insert(Ogre::ConfigFile::SettingsMultiMap::value_type(key, value));
        }
    };
}

#endif