/**
 * @file BaseComponent.h
 * @author Patrick Joos, Eduardo Hahn Paredes
 * @brief Defines the interface for all our components.
 */

#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include "Entities/Entity.h"

namespace CotopaxiEngine {
	class BaseModule;
    /**
     * @class BaseComponent
     * @brief Every Component should inherit from this class.
     * 
     * It has a pointer to an Entity and can delegate events to it.
     */
	class BaseComponent: public EventListener
    {
    protected:
        
        /** @brief The Entity that has the component */
        Entity* parent;
        
    public:
        virtual ~BaseComponent(){
			parent = NULL;
		}

        /**
         * @fn setParent
         * Setter of the Entity which uses the component.
         * @param parent The entity that has to be set
         */
        virtual void setParent(Entity* parent)
        {
            this->parent = parent;
        }
        
        /**
         * @fn getParent
         * Getter of the Entity which uses the component.
         * @return The entity that the component belongs to.
         */
        virtual Entity* getParent()
        {
            return parent;
        }
        
        /**
         * @fn receiveEvent
         * Passes an event to the component.
         * @param event The event that has to be passed.
         */
        virtual void receiveEvent(Event* event) { }
    };
}

#endif