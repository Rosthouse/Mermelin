/**
 * @file Trigger.h
 * @brief Is used to fire events.
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef TRIGGER_H
#define	TRIGGER_H

#include "Components/LogicComponent.h"
#include "Condition.h"
#include "Engine.h"

namespace CotopaxiEngine {

    /**
     * @class Trigger
     * 
     * @brief Is used to fire events.
     *
     * It can be fulfilled or not. The @link check @endlink function indicates it.
     */
    class Trigger : public LogicComponent
    {
    public:
        Trigger(std::string name);
        virtual ~Trigger();

        void addTarget(Condition* entity);
        bool check();

        /**
         * @fn fire
         * Sendes Events of type Event::TRIGGER to the registered targets.
         */
        void fire();

        /**
         * @fn receiveEvent
         * Accepts and calles @link fire @endlink if the incoming Event is of type 
         * Event::COLLISION_ENTER.
         * @param event Any Event
         */
        virtual void receiveEvent(Event* event);

        /**
         * @fn setName
         * Every Trigger has to be a name, so it can be identified later.
         * @param name The name to give
         * @attention do not use the same name twice
         */
        void setName(std::string name);

        /**
         * @fn getName
         * Shows the name
         * @return The name and identifier of the Trigger instance
         */
        std::string getName() const;

    private:
        std::string name;
        std::vector<Condition*>* targets;
        bool fired;
    };
}

#endif
