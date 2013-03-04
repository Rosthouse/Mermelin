/**
 * @file LogicComponent.h
 * @brief Adds some logic to an Entity.
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef LOGICCOMPONENT_H
#define	LOGICCOMPONENT_H

#include "BaseComponent.h"
#include "Modules/LogicModule.h"

namespace CotopaxiEngine {

    /**
     * @class LogicComponent
     * @brief Used if the Entity must have a role in a logical context.
     * 
     * It's the interface and the lowest common denominator for 
     * implementing the logic using the composite pattern.
     * @author Patrick Joos, Eduardo Hahn Paredes
     */
    class LogicComponent : public BaseComponent
    {
    public:

        /**
         * Checks Conditions and Triggers.
         * @return true if the condition is fulfilled or the trigger fired.
         */
        virtual bool check() = 0; // pure virutal (abstract) function
    };
}

#endif
