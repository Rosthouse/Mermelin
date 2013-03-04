/**
 * @file Goal.h
 * @brief Contains the Goal class.
 * @author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef GOAL_H
#define	GOAL_H

#include "Entity.h"

namespace CotopaxiEngine
{
    /**
     * @class Goal
     * @brief Represents the goal of every game-level.
     */
    class Goal : public Entity
    {
    public:
        Goal(std::string name, Ogre::SceneNode* parentNode);
        virtual void receiveEvent(Event* e);
        
        static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new Goal(name, parentNode);
        };
    private:

    };
}

#endif

