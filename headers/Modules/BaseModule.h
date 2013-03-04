/**
@file BaseModule.h
@Contains the BaseModule

@author Patrick Joos, Eduardo Hahn Paredes
*/

#ifndef BASEMODULE_H
#define BASEMODULE_H
#include "stdafx.h"
#include "Event.h"

namespace CotopaxiEngine
{

    class BaseComponent; //Forward delcaration
	class Entity;
    
	/**
	@class BaseModule
	@brief BaseModule implemented by all Modules
	
	This is our base class for all our modules. It implements a framelistener from Ogre, so that we can use Ogre for our gameloop.
	Each Module inherits from this, so this serves as a common interface for all modules.
	*/
	class BaseModule: public EventListener
    {
    public:
		/**
		@fn load
		Loads the module
		*/
        virtual void load() { };
        /**
		@fn unload
		Unloads the module
		*/
		virtual void unload() { };
        /**
		@fn getComponent
		Produces a new Entity and attaches it to the given entity
		@param entity The entity to attache the new component to
		@return A pointer to the newly created component. This is a pointer to a BaseComponent, so, if needed, it should be casted to the corresponding subclass
		*/
		virtual BaseComponent* getComponent(Entity* entity) = 0;

		virtual void removeComponent(std::string component){};

		virtual bool frameStarted(const Ogre::FrameEvent& evt){ return true; };
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt){ return true; };
		virtual bool frameEnded(const Ogre::FrameEvent& evt){ return true; };

		virtual void receiveEvent(Event* e){}
    };
}

#endif
