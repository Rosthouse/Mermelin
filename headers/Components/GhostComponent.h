/**
 * @file GhostComponent.h
 * @brief Contains the GhostComponent
 * @author Patrick Joos, Eduardo Hahn Paredes
 * @todo write doxygen
 */

#ifndef GHOSTCOMPONENT_H
#define	GHOSTCOMPONETN_H

#include "stdafx.h"
#include <string>
#include "Modules/PhysicsModule.h"
#include "Components/PhysicsComponent.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

namespace CotopaxiEngine {

    /**
     * @class GhostComponent
     * @brief Access to Bullets btGhostObject
     */
    class GhostComponent : public PhysicsComponent
    {
    public:
        GhostComponent(btScalar mass, PhysicsModule::Shape s, short group, short mask);
		~GhostComponent();
        
        virtual void setParent(Entity* parent);
        btGhostObject* getGhost();
        void checkOverlappingObjects();
		virtual void receiveEvent(Event* e);
    private:
        btGhostObject* ghostObject;
		std::set<std::string> lastKnownColliders;
    };
}

#endif