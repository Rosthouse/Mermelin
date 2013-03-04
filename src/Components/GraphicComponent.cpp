/**
 * GraphicComponent.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Components/GraphicComponent.h"
#include "Engine.h"

using namespace CotopaxiEngine;

GraphicComponent::GraphicComponent()
{
    animated = false;
    hasShader = false;
}

GraphicComponent::~GraphicComponent()
{
	ENGINE->getModule(Engine::ModuleType::MODULE_GRAPHIC)->removeComponent(parent->getName());

    if (animated) {
        delete animation;
    }
    if (hasShader) {
        delete shader;
    }
}

void GraphicComponent::setParent(Entity* parent)
{
    BaseComponent::setParent(parent);
    parent->setGraphicComponent(this);
    parent->getOgreEntity()->setCastShadows(true);
}

void GraphicComponent::update(Ogre::Real time)
{
    if (animated) {
        animation->addTime(time);
        Event* e = new Event(Event::PHYSICS_UPDATE);
        parent->receiveEvent(e);

        if (animation->hasEnded()) {
            animated = false;
            Event* animationEnded = new Event(Event::ANIMATION_ENDED);
            this->parent->receiveEvent(animationEnded);
			delete animationEnded;
        }
        delete e;
    }
}

void GraphicComponent::setAnimation(std::string name, bool loop)
{
    animation = parent->getOgreEntity()->getAnimationState(name);
	parent->getOgreEntity()->setDisplaySkeleton(true);

    animation->setLoop(loop);
    animation->setEnabled(true);
    animated = true;

    this->parent->receiveEvent(new Event(Event::ANIMATION_STARTED));
}

void GraphicComponent::setShader(Shader* shader)
{
    this->shader = shader;
    hasShader = true;
}

void GraphicComponent::removeShader()
{
    hasShader = false;
    delete shader;
}