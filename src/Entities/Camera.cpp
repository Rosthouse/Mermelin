/**
 * @file Camera.cpp
 * @authors Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Entities/Camera.h"

using namespace CotopaxiEngine;

Camera::Camera(std::string name, Ogre::SceneNode* parentNode)
: Entity(name, "", parentNode)
{
    offset = Ogre::Vector3(0, 10, 0);

    camera = ENGINE->getSceneManager()->createCamera(name);
    camera->setNearClipDistance(0.1);
    camera->setFarClipDistance(10000);

    this->getNode()->attachObject(camera);
    ENGINE->getWindow()->addViewport(camera);
}

bool Camera::isAttached() const
{
    return attached;
}

void Camera::attachTo(CotopaxiEngine::Entity* object)
{
    this->object = object;
    this->setParentNode(object->getNode());
    this->getNode()->setInheritOrientation(false);
    this->getNode()->lookAt(object->getNode()->getPosition(),
            Ogre::Node::TS_PARENT);

    attached = true;
}

void Camera::detach()
{
    this->setParentNode(ENGINE->getSceneManager()->getRootSceneNode());
    this->getNode()->setPosition(object->getNode()->getPosition() + offset);
    camera->lookAt(object->getNode()->getPosition());
    attached = false;
}

void Camera::reattach()
{
    if (object != NULL) {
        attachTo(object);
    } else {
        Ogre::LogManager::getSingletonPtr()->logMessage(
                Ogre::LogMessageLevel::LML_TRIVIAL,
                "Cannot reattach a Camera if it has not been attached first"
                );
    }
}

void Camera::setOffset(Ogre::Vector3 offset)
{
    this->offset = offset;
}

Camera::~Camera()
{
    delete camera;
}

void Camera::update()
{
    Ogre::Vector3 position = Ogre::Vector3(
            this->getNode()->getPosition().x + offset.x,
            0.0,
            this->getNode()->getPosition().z + offset.z
            );
    this->getNode()->setPosition(position);
    this->getNode()->setOrientation(1.0, 1.0, 0.0, 0.0);
    camera->lookAt(object->getNode()->getPosition());
}

void Camera::setParentNode(Ogre::SceneNode* newParent)
{
    Entity::setParentNode(newParent);
    this->getNode()->setInheritOrientation(false);
}

void Camera::translate(const Ogre::Vector3& translation)
{
    this->getNode()->translate(translation, Ogre::Node::TS_PARENT);
}

void Camera::rotate(const Ogre::Quaternion& rotation)
{
    this->getNode()->rotate(rotation, Ogre::Node::TS_LOCAL);
}