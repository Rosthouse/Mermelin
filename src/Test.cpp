/**
 * @file Test.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Test.h"
#include "Components/LogicComponent.h"

using namespace CotopaxiEngine;

bool Test::checkComponents() {
#ifdef DEBUG
    return false;
#endif
    return true;
}

bool Test::checkConditionTree(Level* level)
{
#ifdef DEBUG
    Entity* ent = ENGINE->createEntity("TreeTestEntity", "floor",
            ENGINE->getSceneManager()->getRootSceneNode());
    LogicComponent* comp = level->buildConditionTree("b1;AND;b2;OR;b3", ent);
    return false;
#endif
    return true;
}

bool Test::checkWrongSyntax() {
    return true;
}