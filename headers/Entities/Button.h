/**
 * @file Button.h
 * @brief Button definition resides in this file.
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "stdafx.h"
#include "Entities/Entity.h"

namespace CotopaxiEngine {

    /**
     * @class Button
     * 
     * @brief Represents a button that can be activated by the Sphere.
     */
    class Button : public Entity
    {
    public:
        Button(std::string name, Ogre::SceneNode* parentNode);
        virtual ~Button();
        static Entity* create(std::string name, Ogre::SceneNode* parentNode)
        {
            return new Button(name, parentNode);
        }
    };
}

#endif

