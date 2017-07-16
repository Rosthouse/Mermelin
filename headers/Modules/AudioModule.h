/**
 * @file AudioModule.h
 * @brief Contains the AudioModule.
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef AUDIOMODULE_H
#define AUDIOMODULE_H
#include "stdafx.h"
#include "Modules/BaseModule.h"

namespace CotopaxiEngine
{

    // forward declarations
    class AudioComponent;

    /**
     * @class PlaySound
     * @brief This class is needed for multithreading in audio for sounds (in memory)
     */
    class PlaySound : private sf::Thread
    {
    public:
		PlaySound(std::string path, bool loop) : path(path), loop(loop), sf::Thread(&PlaySound::Run, this) {}

        virtual ~PlaySound() {
            delete sound;
            delete buffer;
        }

        void play() {
            launch();
        }

        sf::Sound* getSound() const {
            return sound;
        }

    private:
        bool loop;
        std::string path;
        sf::SoundBuffer* buffer;
        sf::Sound* sound;

        virtual void Run() {
            buffer = new sf::SoundBuffer();
            if (!buffer->loadFromFile(path)) {
                throw std::exception();
            }
            sound = new sf::Sound();
            sound->setBuffer(*buffer);
            sound->setLoop(loop);
            sound->play();
        }
    };

    /**
     * @class PlayMusic
     * @brief This class is needed for multithreading in audio for music (streaming)
     */
    class PlayMusic : private sf::Thread
    {
    public:

        PlayMusic(std::string path, bool loop)
        : path(path), loop(loop), sf::Thread(&PlayMusic::Run, this) { }

        virtual ~PlayMusic() {
            delete music;
        }

        void play() {
            launch();
        }

        sf::Music* getMusic() const {
            return music;
        }

    private:
        bool loop;
        std::string path;
        sf::Music* music;

        virtual void Run() {
            music = new sf::Music();
            if (!music->openFromFile(path)) {
                throw std::exception();
            }
            music->setLoop(loop);
            music->play();
        }
    };

    /**
     * @class AudioModule
     * @brief This is the connection to the audio library SMFL
     * 
     * This class is the main interface to the audio library of SMFL.
     */
    class AudioModule : public BaseModule
    {
    public:
        
        /**
         * @fn playSound
         * @param path where the file is located
         * @param loop the sound will be looped if true
         * @return a pointer to PlaySound
         */
        PlaySound* playSound(std::string path, bool loop = false);
        
        /**
         * @fn playMusic
         * @param path where the file is located
         * @param loop the music will be looped if true
         * @return a pointer to PlayMusic
         */
        PlayMusic* playMusic(std::string path, bool loop = false);
        
        /**
         * @fn stopSound
         * Stops the playback of the sound
         * @param sound pointer to the sound that shall be stopped.
         */
        void stopSound(PlaySound* sound);
        
        /**
         * @fn stopMusic
         * Stops the playback of the music
         * @param sound pointer to the music that shall be stopped.
         */
        void stopMusic(PlayMusic* music);
        
        /**
         * @fn setGlobalVolume
         * @param volume A float between 0.0 (mute) and 100.0 (loud)
         */
        void setGlobalVolume(float volume);
        
        BaseComponent* getComponent(Entity* entity);
        virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    private:
        std::vector<AudioComponent*> components;
    };
}
#endif