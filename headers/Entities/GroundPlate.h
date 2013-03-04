/**
 * @file GroundPlate.h
 * @brief The floor that is located below the game.
 * 
 * @author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef GROUNDPLATE_H
#define GROUNDPLATE_H

#include "stdafx.h"
#include "Entity.h"

namespace CotopaxiEngine
{
    /**
     * @class GroundPlate
     * @brief An infinite plane that is located under the level.
     *
     * If the Sphere collides with it it will be reset to the starting position.
     */
	class GroundPlate: public Entity
	{
	public:
		GroundPlate(std::string name, Ogre::SceneNode* parentNode);
        virtual ~GroundPlate();
		virtual void receiveEvent(Event* e);

		static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new GroundPlate(name, parentNode);
        }
	};
}

#endif