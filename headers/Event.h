/**
 * @file Event.h
 * @brief Defines the different types of events that can be used.
 *
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef EVENT_H
#define EVENT_H
namespace CotopaxiEngine {

    // forward declarations
    class BaseComponent;
    class Entity;

    /**
     * @class Event
     * @brief Defines Event Types for internal communication.
     *
     * It's an almost empty container for messaging between different classes. An Entity* can be 
     * used as additional information if needed.
     */
    class Event
    {
    public:

        /**
         * @enum EventType
         * Defines all types of events
         * - COLLISION_ENTER            Collistion occured (started)
         * - COLLISION                  General collision event
         * - COLLISION_EXIT             Collision ended
         * - PHYSICS_UPDATE             Update the physics-world
         * - TRANSLATE                  A translation has occured (in level-parsing for example)
         * - TRIGGER                    Used by LogicComponents (trigger has been fired)
         * - CONDITION_FULFILLED        Used by LogicComponents (condition has been fulfilled)
         * - ANIMATION_STARTED          The mesh animation has started
         * - ANIMATION_ENDED            The mesh animation has ended
         */
        enum EventType
        {
            COLLISION_ENTER,
            COLLISION,
            COLLISION_EXIT,
            PHYSICS_UPDATE,
            TRANSLATE,
            TRIGGER,
            CONDITION_FULFILLED,
            ANIMATION_STARTED,
            ANIMATION_ENDED,
			LEVEL_END
        };

        Event(EventType);

        /**
         * @fn getType
         * @return the type of an event
         */
        virtual EventType getType() const;

        /** Can be used to access the Entity that produced the Event. */
        Entity* entity;
		BaseComponent* component;
    private:
        EventType type;
    };

	class EventListener
	{
	public:
		virtual void receiveEvent(Event* e) = 0;
	};
}

#endif