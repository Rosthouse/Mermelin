/**
@file GraphicModule.h
@brief Contains the GraphicModule.

@author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef GRAPHICMODULE_H
#define GRAPHICMODULE_H
#include "Modules/BaseModule.h"
#include "Components/BaseComponent.h"
#include "Components/GraphicComponent.h"

using namespace std;
namespace CotopaxiEngine
{
    class Entity;
    class GraphicComponent;

    /**
     * @class GraphicModule
     * @brief Will handle updating animations and such things.
     */
    class GraphicModule : public BaseModule
    {
    private:
        std::map<std::string, GraphicComponent*> components;
    public:
		GraphicModule();
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);
        BaseComponent* getComponent(Entity* parent);
        void refreshAllShaders();
		void receiveEvent(Event* e);
		void removeComponent(std::string component);
    };
}
#endif