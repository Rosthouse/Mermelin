/**
 * PhysicsModule.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Modules/PhysicsModule.h"
#include "Components/GhostComponent.h"

#include "BulletCollision/CollisionDispatch/btGhostObject.h"

using namespace CotopaxiEngine;

PhysicsModule::PhysicsModule()
{
    broadphase = new btAxisSweep3(btVector3(-10000, -10000, -10000),
            btVector3(10000, 10000, 10000), 1024);
    config = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(config);
    solver = new btSequentialImpulseConstraintSolver();
    dynamics = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
    dynamics->setGravity(btVector3(0, -9.8, 0));
    dbgdraw = new BtOgre::DebugDrawer(ENGINE->getSceneManager()->getRootSceneNode(), dynamics);
    dynamics->setDebugDrawer(dbgdraw);
    dynamics->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback);
}

PhysicsModule::~PhysicsModule()
{
    delete solver;
    delete dispatcher;
    delete config;
    delete broadphase;
    delete dbgdraw;
    delete dynamics;
}

bool PhysicsModule::frameStarted(const Ogre::FrameEvent&evt)
{
    for (std::map<std::string, GhostComponent*>::iterator it = ghosts.begin();
            it != ghosts.end(); it++) {
        it->second->checkOverlappingObjects();
    }
    dynamics->clearForces();
    return true;
}

bool PhysicsModule::frameEnded(const Ogre::FrameEvent&evt)
{
    dynamics->debugDrawWorld();
    dbgdraw->setDebugMode(ENGINE->getState() == Engine::STATE_DEBUGING);
    dbgdraw->step();
    return true;
}

bool PhysicsModule::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (ENGINE->getState() == ENGINE->STATE_RUNNING 
            || ENGINE->getState() == ENGINE->STATE_DEBUGING) {
        dynamics->stepSimulation(evt.timeSinceLastFrame, 10);
    }
    return true;

}

void PhysicsModule::setGravity(const btVector3& gravity)
{
    dynamics->setGravity(gravity);
}

BaseComponent* PhysicsModule::getComponent(Entity* parent, float mass, Shape s, int group,
        int mask, bool hasTrigger)
{

    PhysicsComponent* component;

    // checking if component exists
    if (components.find(parent->getName()) == components.end()) {
        component = hasTrigger ? new GhostComponent((btScalar) mass, s, group, mask)
                : new PhysicsComponent((btScalar) mass, s, group, mask);
        component->setParent(parent);

        components[parent->getName()] = component;

        if (hasTrigger) {
            ghosts[parent->getName()] = (GhostComponent*) component;
        }
    } else {
        component = components[parent->getName()];
    }

    return component;
}

BaseComponent* PhysicsModule::getComponent(Entity* parent)
{
    btScalar mass = 5.0;
    return getComponent(parent, mass, PhysicsModule::SPHERE);
}

btDynamicsWorld* PhysicsModule::getWorld()
{
    return dynamics;
}

void PhysicsModule::setDrawDebugWorld(bool draw)
{
    dbgdraw->setDebugMode(draw);
}

void PhysicsModule::removeComponent(std::string component)
{
    std::map<std::string, PhysicsComponent*>::iterator componentToRemove =
            components.find(component);

    if (componentToRemove != components.end()) {
        components.erase(componentToRemove);
    }

	std::map<std::string, GhostComponent*>::iterator ghostToRemove = ghosts.find(component);

	if(ghostToRemove != ghosts.end())
	{
		ghosts.erase(ghostToRemove);
	}
}