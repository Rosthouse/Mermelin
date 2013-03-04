/**
 * @file AudioComponent.h
 * @author Patrick Joos, Eduardo Hahn Paredes
 * @brief Contains the Audiocomponent
 */

#ifndef AUDIOCOMPONENT_H
#define	AUDIOCOMPONENT_H

#include "stdafx.h"

#include "Components/BaseComponent.h"
#include "Engine.h"
#include "Modules/AudioModule.h"
#include "Resources/Managers/AudioManager.h"
#include "Resources/Files/Audio.h"

namespace CotopaxiEngine {

    /**
     * @class AudioComponent
     * @brief Provides the ability to play a sound to an Entity
     * 
     * The sound will automaticaly play in the same position as the parent 
     * entity is currently.
     */
    class AudioComponent : public BaseComponent
    {
    public:
        AudioComponent();
        ~AudioComponent();

        /**
         * @fn play
         * Plays a sound file
         * @param file The path to the sound file to play
         * @return Wether the sound could be played or not
         * @remark If the sound is not found in the sound list, this method will return false
         */
        bool play(std::string soundName, bool loop = false);

        /**
         * @fn play
         * Stops a sound file
         * @param file The path to the sound file to play
         */
        void stop(std::string soundName);

        /**
         * @fn addSound
         * Adds a sound to a AudioComponent
         * @param soundName Name of the sound to be loaded
         * @return Bool, whether the loading was succesfull
         */
        bool addSound(std::string soundName);

        /**
         * @fn removeSound
         * Removes a sound from a AudioComponent
         * @param soundName Name of the sound to be removed
         * @return Bool, whether the removment was succesfull
         * @todo implement!
         */
        void removeSound(std::string soundName);

		void setParent(Entity* entity);

        void receiveEvent(Event* e);
    private:
        std::map<std::string, Audio*> audioList;
    };
}

#endif
