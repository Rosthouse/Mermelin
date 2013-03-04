/**
 * @file Door.h
 * @brief Represents a door.
 * @author Patrick Joos, Eduardo Hahn Paredes
 * 
 * It can be in 4 different states: close, opening, open and closing.
 */
#ifndef DOOR_H
#define	DOOR_H

#include "Engine.h"
#include "Entity.h"

namespace CotopaxiEngine
{
    // forward declarations
    class LogicComponent;
    class PhysicsComponent;
    
    /**
     * @class Door
     * @brief Creates a Door Entity
     * 
     * It consists of 3 meshes:
     * Door_Arc (the arc) above the door and the 2 door wings
     * Door_Left and Door_Right.
     */   
    class Door : public Entity
    {
    public:
        
        /** @enum Doorstate	Defines all types of states a door can have */
        enum DoorState
        {
            CLOSED,
            OPEN,
            OPENING
        };
        
        Door(std::string name, Ogre::SceneNode* parentNode);
        virtual ~Door();

        /**
		 * @fn getState
		 * @return Indicates in which state the door is
		 */
        DoorState getState() const {
            return state;
        }
        
        /**
		 * @fn open
         * Loads the opening animation and sets the DoorState to OPENING
         * while the animation is running. Finally it sets the DoorState to OPEN.
		 */
        void open();
        
        virtual void receiveEvent(Event* e);
        
        /**
		@fn addComponent
        Loads the closing animation and sets the DoorState to CLOSING
        while the animation is running. Finally it sets the DoorState to CLOSED.
		*/
		void addComponent(BaseComponent* component);

        static Entity* create(std::string name, Ogre::SceneNode* parentNode) {
            return new Door(name, parentNode);
        }

        /**
         * @fn setLogicComponent
         * Allows to set a LogiComponent that defines the Condition for opening
         * the Door.
         * @param logicComponent
         */
        void setLogicComponent(LogicComponent* logicComponent) {
            this->logicComponent = logicComponent;
        }

        /**
         * @fn getLogicComponent
         * Gives access to the LogicComponent.
         * @return a pointer to the LogicComponent
         */
        LogicComponent* getLogicComponent() const {
            return logicComponent;
        };
        
    private:        
        DoorState state;
        LogicComponent* logicComponent;
        Entity* leftDoor;
        Entity* rightDoor;
        PhysicsComponent* rightPhysics;
        PhysicsComponent* leftPhysics;
    };
}

#endif