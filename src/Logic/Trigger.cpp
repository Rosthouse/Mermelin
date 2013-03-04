/**
 * @file Trigger.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Logic/Trigger.h"

using namespace CotopaxiEngine;

Trigger::Trigger(std::string name)
: name(name), targets(new vector<Condition*>) { }

void Trigger::setName(std::string name)
{
    this->name = name;
}

std::string Trigger::getName() const
{
    return name;
}

Trigger::~Trigger()
{
    delete targets;
}

void Trigger::addTarget(Condition* condition)
{
    targets->push_back(condition);
}

bool Trigger::check()
{
    return fired;
}

void Trigger::fire()
{
    for (int i = 0; i < targets->size(); i++) {
        targets->at(i)->receiveEvent(new Event(Event::TRIGGER));
    }
    fired = true;
}

void Trigger::receiveEvent(Event* event)
{
    if (event->getType() == Event::COLLISION_ENTER) {
        fire();
    }
}