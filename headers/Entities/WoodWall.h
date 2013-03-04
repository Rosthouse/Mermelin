/**
 * @file WoodWall.h
 * @brief Represents a wooden wall that can be burned down.
 * @author Patrick Joos, Eduardo Hahn Paredes
 * 
 * It can be in 3 different states: normal, burning and gone
 */

#ifndef WOODWALL_H
#define	WOODWALL_H

#include "Entity.h"

namespace CotopaxiEngine
{

    /**
     * @class WoodWall
     * @brief Represents a wooden wall that can be burned down.
     *
     * It's realized by a single mesh calles Wall_Wood.mesh. If the wall is
     * in NORMAL state the Shpere will colide against it, but when it is in
     * GONE state the Sphere can pass through.
     */
    class WoodWall : public Entity
    {
    public:

        /** @enum WoodWallState	Defines all types of states a door can have */
        enum WoodWallState
        {
            NORMAL,
            BURNING,
            GONE
        };

        WoodWall(std::string name, Ogre::SceneNode* parentNode);

        /**
         * @fn setState
         * Puts the TypeChanger in the given state
         * @param state the WoodWallState to be set
         */
        void setState(WoodWallState state) {
            this->state = state;
        }

        /**
         * @fn getState
         * Indicates the current state of the wall.
         * @return one of the 3 possible states
         */
        WoodWallState getState() const {
            return state;
        }

        static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new WoodWall(name, parentNode);
        }

        virtual void receiveEvent(Event e);
    private:
        WoodWallState state;
    };
}

#endif