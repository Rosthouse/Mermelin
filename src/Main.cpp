/**
 * @mainpage CotopaxiEngine
 *
 * The CotopaxiEngine is a 3D game engine, based on OGRE, Bullet, SFML and libRocket.
 * It's a student project intended to teach game engine design as well as being a learning 
 * experience.
 * 
 * It is written completly in C++, using several features of the new C++11 standard, as supported 
 * by various compilers.
 * 
 * As this engine was developed on Linux and Windows, it is thought to be completly platform 
 * agnostic, meaning you can build and run it on most modern platforms.
 * 
 * The most important library in this project is OGRE.
 * @see http://www.ogre3d.org/
 *
 * @file Main.cpp
 * @brief This is the entry point. It loads everything.
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Engine.h"

/** 
 * @namespace CotopaxiEngine
 * @brief The namespace used for the CotopaxiEngine. Contains the game and its engine.
 * 
 * Every class (except external source code) should use this namespace.
 * 
 * @namespace BtOgre
 * @brief The namespace of the BtOgre part. It's the link between OGRE and Bullet.
 * 
 * Those files where developed by Nikhilesh (nikki).
 * More information at: https://github.com/nikki93/btogre
 */
using namespace CotopaxiEngine;

int main(int argc, char* argv[])
{
    try {
        ENGINE->load("Mermelin");
        ENGINE->start();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}