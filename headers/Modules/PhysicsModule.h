/**
@file PhysicsModule.h
@brief Contains the PhysicModule

@author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef PHYSICSMODULE_H
#define	PHYSICSMODULE_H
#include "stdafx.h"

#include "Modules/BaseModule.h"
#include "Engine.h"

#include "Shaders/Shader.h"
#include "Shaders/AirShader.h"
#include "Shaders/EarthShader.h"
#include "Shaders/FireShader.h"
#include "Shaders/WaterShader.h"

#define BIT(x) (1<<(x))

namespace CotopaxiEngine
{

    // Forward declarations
    class PhysicsComponent;
    class GhostComponent;
    class Entity;

    /**
     * @class PhysicsModule
     * @brief The PhyicsModule is the link to the Bullet Physics Library.
     *
     * To use pyhsics in our Engine, we need an interface to Bullet, which this class provides.
     * 
     * Unfortunately, updating the physics is a rather slow operation. It usually takes more time 
     * than any other operation (apart from rendering itself). Profiling showed that about 20% 
     * of the time in an update loop is spent processing the physics.
     * This takes a huge impact on the framerate. To solve this, the idea of doing the updating 
     * for physics in a separate thread came up. For this, the threading system of sfml was 
     * selected.
     * 
     * @see http://bulletphysics.org
     */
    class PhysicsModule : public BaseModule
    {
    public:

        enum Shape
        {
            SPHERE,
            BOX,
            PLANE,
            CYLINDER,
            TRIMESH
        };

        enum CollisionMask
        {
            COL_NOTHING = 0,
            COL_PLAYER = BIT(1),
            COL_STATIC = BIT(2),
            COL_POWERUP = BIT(3),
            COL_TYPECHANGER = BIT(4),
            COL_BUTTON = BIT(5),
            COL_GHOST = BIT(6),
            COL_NOCOLL = BIT(15)
        };

        PhysicsModule();
        virtual ~PhysicsModule();

        virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
        virtual bool frameStarted(const Ogre::FrameEvent& evt);
        virtual bool frameEnded(const Ogre::FrameEvent& evt);
        virtual BaseComponent* getComponent(Entity* parent);
        virtual BaseComponent* getComponent(Entity* parent, float mass, Shape,
                int group = COL_NOTHING, int mask = COL_NOCOLL, bool hasTrigger = false);
        virtual void removeComponent(std::string component);
        void setGravity(const btVector3& gravity);

        static int getGroup(int group) {
            return BIT(group);
        }

        void setDrawDebugWorld(bool draw);

        btDynamicsWorld* getWorld();
    private:
        btDynamicsWorld* dynamics;
        BtOgre::DebugDrawer* dbgdraw;
        btAxisSweep3* broadphase;
        btDefaultCollisionConfiguration* config;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        std::map<std::string, PhysicsComponent*> components;
        std::map<std::string, GhostComponent*> ghosts;
    };
}
#endif

