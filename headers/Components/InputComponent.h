/**
 * @file InputComponent.h
 * @brief Contains the InputComponent.
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "BaseComponent.h"
#include "Modules/InputModule.h"

namespace CotopaxiEngine {

    /**
     * @class InputComponent
     * @brief Defines a basic component for interacting with the input system.
     */
    class InputComponent : public BaseComponent
    {
    public:
        
        /**
         * @fn transfer
         * Passes the Event to the Entity.
         * @param event
         */
        void transfer(Event* event);
        void setParent(Entity* parent);
    };
}

#endif