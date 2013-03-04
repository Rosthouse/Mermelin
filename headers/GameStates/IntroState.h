/**
@file IntroState.h
@brief Contains the IntroState

@author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "stdafx.h"
#include "GameStates/GameState.h"
//#include "GameStates/PlayState.h"

namespace CotopaxiEngine
{
    class PlayState;

    /**
     * @class IntroState
     * @brief Shows intro videos and images
     *
     * This state shows a splashscreen and intro videos. It changes into menustate, when 
     * finished or the user cancles the intro
     * @todo implement
     */
    class IntroState : public GameState
    {
    private:
        Ogre::Rectangle2D* rect;
        Ogre::Timer timer;
        PlayState* playState;
    public:
        IntroState();
        ~IntroState();

        virtual void load();
        virtual void unload();

        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        virtual void pause() { }
    };
}

#endif