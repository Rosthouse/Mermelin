/**
 * @file InputModule.h
 * @brief Contains the InputModule
 * 
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#ifndef INPUTMODULE_H
#define	INPUTMODULE_H

#include "stdafx.h"
#include "Modules/BaseModule.h"
#include "Engine.h"
#include "Event.h"
#include "Modules/GUIModule.h"

using namespace OIS;

namespace CotopaxiEngine
{
    // forward declarations
    class InputComponent;
    class Event;

    /**
     * @class InputModule
     * @brief Handels polling the user input and informing the required components
     * 
     * This module serves as a gateway to the input devices, such as Keyboard, Mouse, 
     * Wii-controller and others. It serves the connected Components with the keypresses they are 
     * interested in.
     * 
     * It's realised with the OIS (Object Oriented Input System) library
     * @see http://sourceforge.net/projects/wgois/
     */
    class InputModule : public BaseModule, public KeyListener,
    public MouseListener, public Ogre::WindowEventListener
    {
    public:
        
        InputModule(void);
        virtual ~InputModule();

        virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
        virtual void windowResized(Ogre::RenderWindow *rw);
        virtual void windowClosed(Ogre::RenderWindow *rw);

        // keyboard event
        virtual bool keyPressed(const KeyEvent &event);
        virtual bool keyReleased(const KeyEvent &event);

        // mouse events
        virtual bool mouseMoved(const MouseEvent &event);
        virtual bool mousePressed(const MouseEvent &event, MouseButtonID id);
        virtual bool mouseReleased(const MouseEvent &event, MouseButtonID id);

        virtual BaseComponent* getComponent(Entity *parent);

		
    private:
        bool menuMode;
        InputManager* input;
        Mouse* mouse;
        Keyboard* key;
        std::vector<InputComponent*> components;
        
        Ogre::Radian calculateAngle(float* time);
        void moveSphere(Ogre::Vector3 rotation);
        
        // Rocket
        typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
        KeyIdentifierMap keys;      
        
		Rocket::Core::Context* getContext(){ return ENGINE->getGUI()->getContext(); }

        int getModifier();
        void buildKeyMap();
    };
}

#endif