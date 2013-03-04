/**
 * InputComponent.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Components/InputComponent.h"

using namespace CotopaxiEngine;

void InputComponent::transfer(Event* event)
{
    parent->receiveEvent(event);
}

void InputComponent::setParent(Entity* parent)
{
    BaseComponent::setParent(parent);
    this->parent->registerListener(Event::PHYSICS_UPDATE, this);
}