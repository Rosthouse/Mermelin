/**
 * Event.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Event.h"

using namespace CotopaxiEngine;

Event::Event(EventType e)
: type(e) 
{ 
	component = NULL;
	entity = NULL;
}

Event::EventType Event::getType() const
{
    return type;
}