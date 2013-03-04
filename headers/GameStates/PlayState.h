/**
@file PlayState.h
@brief Contains the PlayState

@author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "stdafx.h"
#include "GameStates/GameState.h"
#include "Shaders/Shader.h"

namespace CotopaxiEngine
{
    /**
     * @class PlayState
     * @brief The main state, when the user is playing the game.
     *
     * The level is loaded and playable.
     */
    class PlayState : public GameState
    {
    public:
        PlayState();
        void load();
        void loadNext();

        void setLevel(int level) {
            this->level = level;
        }

        int getLevel() const {
            return level;
        }

		virtual void receiveEvent(Event* e);
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
    private:
        int level;
		Entity* ground;
		bool changeLevel;
    };
}

#endif