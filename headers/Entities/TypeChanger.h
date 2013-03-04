/**
 * @file TypeChanger.h
 * @brief Changes the type of the marble
 * @author Patrick Joos, Eduardo Hahn Paredes
 */
#ifndef TYPECHANGER_H
#define	TYPECHANGER_H

#include "Engine.h"
#include "Entities/Entity.h"
#include "Entities/Sphere.h"
#include "Shaders/Shader.h"
#include "Shaders/AirShader.h"
#include "Shaders/EarthShader.h"
#include "Shaders/FireShader.h"
#include "Shaders/WaterShader.h"

namespace CotopaxiEngine
{

    /**
     * @class TypeChanger
     * @brief Defines a trigger that changes the state of a Sphere
     *
     * A core part of our game is the ability to change the state of the 
     * players Sphere, to achieve certain effects. This class implements a 
     * simple trigger that will, on contact with a sphere, change the state of
     * the former.
     */
    class TypeChanger : public Entity
    {
    public:
        TypeChanger(std::string name, Ogre::SceneNode* parentNode);
        TypeChanger(const TypeChanger& orig);
        virtual ~TypeChanger();

        /**
         * setElement
         * Sets an Element for the TypeChanger.
         * @param element the Element to be set.
         */
        void setElement(CotopaxiEngine::Element element);
        virtual void receiveEvent(Event* e);

        static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new TypeChanger(name, parentNode);
        };
    private:
        Element element;
        Entity* symbolBar;
        Entity* symbolTriangle;
    };
}

#endif