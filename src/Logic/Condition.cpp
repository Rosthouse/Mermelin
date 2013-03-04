/**
 * @file Condition.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Logic/Condition.h"
#include "Logic/Trigger.h"

using namespace CotopaxiEngine;

Condition::Condition()
: triggers(new vector<Trigger*>), subconditions(new std::vector<Condition*>) { }

Condition::~Condition()
{
    delete triggers;
    delete subconditions;
}

void Condition::addTrigger(Trigger* trigger)
{
    triggers->push_back(trigger);
}

void Condition::addSubCondition(Condition* condition)
{
    subconditions->push_back(condition);
}

bool Condition::check()
{
    // checking triggers
    for (vector<Trigger*>::iterator it = triggers->begin(); it != triggers->end(); it++) {
        if (conditionOperator == Condition::AND) {
            if ((*it)->check() == false) {
                return false;
            }
        }
        if (conditionOperator == Condition::OR) {
            if ((*it)->check() == true) {
                return true;
            }
        }
    }

    // checking subconditions
    for (vector<Condition*>::iterator it = subconditions->begin(); it != subconditions->end(); it++) {
        if (conditionOperator == Condition::AND) {
            if ((*it)->check() == false) {
                return false;
            }
        }
        if (conditionOperator == Condition::OR) {
            if ((*it)->check() == true) {
                return true;
            }
        }
    }
    return true;
}

void Condition::setOperator(int conditionOperator)
{
    this->conditionOperator = conditionOperator;
}

int Condition::getOperator() const
{
    return conditionOperator;
}

void Condition::receiveEvent(Event* event)
{
    if (event->getType() == Event::TRIGGER) {
        if (check()) {
            parent->receiveEvent(new Event(Event::CONDITION_FULFILLED));
        }
    }
}