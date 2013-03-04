/**
 * @file PhysicsComponent.h
 * @brief Defines physics properties of a Entity
 * 
 * This class gives the Entity access to the PhysicsModule.
 * 
 * @author Patrick Joos, Eduardo Hahn Paredes
 * @todo write doxygen
 */

#ifndef PHYSICSCOMPONENT_H
#define	PHYSICSCOMPONENT_H

#include "Modules/PhysicsModule.h"
#include "BaseComponent.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

namespace CotopaxiEngine
{

    /**
     * @class PhysicsComponent
     * @brief Representation of physics for an Entity
     * 
     * Modern game engines provide a rich physics engine and the CotopaxiEngine 
     * is not different. The PhysicComponent is the interface between the game 
     * Entity and the physics Engine, providing functions for creating and 
     * monitoring the physic world for an Entity.
     */
    class PhysicsComponent : public BaseComponent
    {
    public:
        PhysicsComponent(btScalar mass, PhysicsModule::Shape, short group, short mask);
        virtual ~PhysicsComponent();

        virtual void setParent(Entity* parent);
        btRigidBody* getBody() const;
        virtual void receiveEvent(Event *event);
        virtual void handleContact(PhysicsComponent* contact);

        Ogre::Vector3 getComponentGravity();
        void setComponentGravity(const Ogre::Vector3& gravity);
		void setActive(bool active);

        Ogre::Entity* physicsEntity;
    protected:
        PhysicsModule::Shape physicsShape;
        btRigidBody* body;
        btCollisionShape* shape;
        BtOgre::RigidBodyState* state;
        btScalar mass;
        btVector3 inertia;
        short group;
        short mask;
    private:
        void applyPhysics(Ogre::Vector3 v);
		void createBody();
    };
}

#endif