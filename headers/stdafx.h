#ifndef PRECOMPILED_HEADERS_H
#define	PRECOMPILED_HEADERS_H
 
// OGRE
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <RenderSystems/GL/OgreGLSLProgram.h>
#include <OgreFontManager.h>

// OIS
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
// SFML
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Thread.hpp>

// Bullet2Ogre
#include "External/BtOgre/BtOgreExtras.h"
#include "External/BtOgre/BtOgreGP.h"
#include "External/BtOgre/BtOgrePG.h"

// Boost
#include "boost/algorithm/string.hpp"

// Rocket
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Core/String.h>
#include <Rocket/Core/Context.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/SystemInterface.h>

#if DEBUG
#include <Rocket/Debugger.h>
#endif


// Common
#include <string>
#include <map>

// Other
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#endif