/**
 * @file GameState.h
 * @brief Contains the basic game state
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "stdafx.h"
#include "Engine.h"

namespace CotopaxiEngine
{

    /**
     * @class GameState
     * @brief A base class implemented by other GameStates
     *
     * In a game engine, various different task have to be done, such as navigating a menu, 
     * playing intro videos, cutscenes, actual gameplay and many more. It's not feasible to 
     * build all that functionality staticaly somewhere in your code.
     * To do this, we implement GameStates, based on the State pattern.
     *
     * The gamestates will be managed in a stack, so switching between a previous or a following state is as easy as pushing it onto the stack.
     */
	class GameState: public EventListener
    {
    protected:
        bool loaded;
    public:
        GameState();
        ~GameState();

        bool isLoaded() {
            return loaded;
        };

        /**
         * @fn load
         * Loads the gamestate, initialize desired modules here
         */
        virtual void load() = 0;

        /**
         * @fn update
         * Updates the current gamestate
         */
        virtual bool frameStarted(const Ogre::FrameEvent& evt) {
            return true;
        }

		virtual void receiveEvent(Event* e){}

        void pushState(GameState* state);
        void popState();
    };
}


#endif

