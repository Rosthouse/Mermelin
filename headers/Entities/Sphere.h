/**
 * @file Shpere.h
 * @brief Represents the marble. The most important object in the game.
 * @author Patrick Joos, Eduardo Hahn Paredes
 * 
 * It can be in different states, including the representation of the 4 elements.
 */
#ifndef SPHERE_H
#define	SPHERE_H

#include "Entity.h"
#include "Modules/GraphicModule.h"
#include "Modules/PhysicsModule.h"
#include "Components/PhysicsComponent.h"

#include "Shaders/Shader.h"
#include "Shaders/AirShader.h"
#include "Shaders/EarthShader.h"
#include "Shaders/FireShader.h"
#include "Shaders/WaterShader.h"

namespace CotopaxiEngine
{

    /**
     * @class Sphere
     * @brief It's the most important Entity in the game.
     *
     * Its states represents the four elements of the game.
     * @see Element
     */
    class Sphere : public Entity
    {
    public:
        Sphere(std::string name, Ogre::SceneNode* parentNode);

        /**
         * @fn setWeight
         * Sets the weight (used by the PhysicsModule)
         * @param weight a positive integer
         */
        void setWeight(int weight) {
            this->weight = weight;
        }

        /**
         * @fn getWeight
         * Shows the weight
         * @return The used in physics
         */
        int getWeight() const {
            return weight;
		}

        /**
         * @fn getState
         * Indicates which Element is loaded on the sphere
         * @return The element
         */
        Element getState() const {
            return state;
        }

        /**
         * @fn setElement
         * The Sphere can be put in a predefined state using a given Element
         * @param element An Element like AIR or FIRE
         */
		void setElement(const Element& element);
        virtual void receiveEvent(Event* e);
        static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new Sphere(name, parentNode);
        };
    private:
        Ogre::Light* light;
        Element state;        
        int weight;
    };
}

#endif