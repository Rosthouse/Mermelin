/**
 * @file Camera.h
 * @brief Contains the Camera Entity. An Ogre::Camera object is used.
 * 
 * @authors Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"
#include "Entity.h"
#include "Engine.h"
#include "SFML/Audio/Listener.hpp"

namespace CotopaxiEngine {

    /**
     * @class Camera
     * @brief Contains the Camera Entity. An Ogre::Camera object is used.
     */
    class Camera : public Entity
    {
    public:
        Camera(std::string name = "Camera", Ogre::SceneNode* 
                parentNode = ENGINE->getSceneManager()->getRootSceneNode());
        virtual ~Camera();
        
        /**
         * @fn attachTo
         * Attaches the Camera to an Entity. It will follow the object using a
         * specied offset.
         * @param object the Entity to which the camera will be attached.
         */
        void attachTo(Entity* object);
        
        /**
         * @fn reattach
         * Attaches the camera to a previous attached object.
         */
        void reattach();
        
        /**
         * @fn detach
         * Detaches the Camera from the Entity. It doesn't follow the object
         * anymore (unitl it's reattached).
         */
        void detach();
        
        /**
         * @fn setOffset
         * Defines the distance between the object and the camera.
         * @param offset Ogre::Vector3 with x, y, z coordinates.
         */
        void setOffset(Ogre::Vector3 offset);
        
        /**
         * @fn update
         * Updates the position and view direction of the camera. This
         * function should be called as often as possible, when the Camera 
         * instance is attached to an object.
         */
        void update();

        virtual void setParentNode(Ogre::SceneNode* newParent);
        
        /**
         * @fn translate
         * Moves the Camera along the Cartesian axes.
         * @param translation Ogre::Vector with x, y, z values representing the 
         * translation.
         */
        void translate(const Ogre::Vector3& translation);
        
        /**
         * @fn rotate
         * Rotate the node around an arbitrary axis using a Quarternion.
         * @param rotation Quaternion defining the rotation.
         */
        void rotate(const Ogre::Quaternion& rotation);
        
        static Entity* create(std::string name, Ogre::SceneNode* parentNode)
        {
            return new Camera(name, parentNode);
        };
        
        /**
         * @fn getCamera
         * Makes the Ogre::Camera accesible from outside.
         * @return pointer to a Ogre::Camera instance.
         */
        Ogre::Camera* getCamera() const
        {
            return camera;
        }

        /**
         * @fn isAttached
         * Checks attachment state of the Camera.
         * @return true if Camera is attached to an object.
         */
        bool isAttached() const;

    private:
        bool attached;
        Ogre::Camera* camera;
        Ogre::Vector3 offset;
        Entity* object;
    };
}
#endif