/**
 * @file LogicModule.h
 * @brief Contains the LogicModule
 * 
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef LOGICMODULE_H
#define LOGICMODULE_H

#include "Modules/LogicModule.h"
#include "Components/BaseComponent.h"

using namespace std;
namespace CotopaxiEngine
{
    //forward declarations
    class LogicComponent;
    class Trigger;
    class Condition;
    
    /**
     * @class LogicModule
     * @brief handles logic behaviour between Entities
     * 
     * Games are driven by rules. These rules are enforced by the LogicModule.
     */
    class LogicModule : public BaseModule
    {
    public:
        LogicModule();
        Trigger* getTrigger(std::string name);
        Condition* getTarget(Entity* parent);
        BaseComponent* createTrigger(Entity* parent, std::string name);
        BaseComponent* createTarget(Entity* parent);
        BaseComponent* getComponent(Entity* parent);
    private:
        std::map<std::string, Trigger*> triggers;
        std::map<std::string, Condition*> targets;
    };
}

#endif