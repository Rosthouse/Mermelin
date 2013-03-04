/**
 * @file GameState.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "GameStates/GameState.h"

using namespace CotopaxiEngine;

GameState::GameState()
{
    loaded = false;
}

GameState::~GameState() { }

void GameState::pushState(GameState* gameState)
{
    ENGINE->pushState(gameState);
}

void GameState::popState()
{
    ENGINE->popState();
}
