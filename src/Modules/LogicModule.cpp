/**
 * LogicModule.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Modules/LogicModule.h"
#include "Logic/Trigger.h"
#include "Logic/Condition.h"

using namespace CotopaxiEngine;

LogicModule::LogicModule(){}

BaseComponent* LogicModule::createTrigger(Entity* parent, std::string name)
{
    Trigger* trigger = new Trigger(name);
    trigger->setParent(parent);
    triggers[name] = trigger;
    return (BaseComponent*) trigger;
}

BaseComponent* LogicModule::createTarget(Entity* parent)
{
    Condition* target = new Condition();
    target->setParent(parent);
    targets[parent->getName()] = target;
    return (BaseComponent*) target;
}

Trigger* LogicModule::getTrigger(std::string name)
{
    return triggers[name];
}

Condition* LogicModule::getTarget(Entity* parent)
{
    return targets[parent->getName()];
}

BaseComponent* LogicModule::getComponent(Entity* parent)
{
    return (BaseComponent*) targets[parent->getName()];
}