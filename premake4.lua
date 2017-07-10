-- PREMAKE4 SCRIPT
-- This is our premake4 project file for the CotopaxiEngine. It allows you to
-- create solution or makefiles for your desired OS and IDE
-- Authors: Patrick Joos, Eduardo Hahn Paredes

-- General tips:
-- Forward slashes in Windows: Windows uses \ for folder separation, however it
-- does support /. Always use /, since premake works better that way

function default(osName, actionName)
    if osName ~= nil and os.is(osName) == false then
        return
    end

    if _ACTION == nil then
        _ACTION = actionName
    end
end

default("windows", "vs2010")
default("linux", "gmake")

solution "Thesis"
project "Engine"
kind "WindowedApp"
language "C++"

files { "headers/**.h", "src/**.cpp", "media/shaders/**.frag", "media/shaders/**.geom", "media/shaders/**.vert" }
includedirs { "headers" }

configurations { "Debug", "Release" }
    if os.is("windows") then
        configuration { "windows" }

        pchheader "stdafx.h"
        pchsource "src/stdafx.cpp"

    	ogre_home = os.getenv("OGRE_HOME")
    	gamedev_libs = os.getenv("GAMEDEV_LIBS")
    	boost_include = os.getenv("BOOST_INCLUDE")
    	boost_libs = os.getenv("BOOST_LIBS")

    	includedirs{
            ogre_home .. "/include/OGRE",
            ogre_home .. "/include/OIS",
            gamedev_libs .. "/bullet/src",
            gamedev_libs .. "/SFML-1.6/include",
            ogre_home .. "/boost_1_47",
            gamedev_libs .. "/libRocket/Include"
        }

        libdirs{ gamedev_libs .. "/SFML-1.6/extlibs/bin" }
        os.remove("Thesis.sdf")
        buildoptions { "/Zm200" }
    end

    if os.is("linux") then
        configuration { "linux" }

        pchheader "headers/stdafx.h"
        pchsource "src/stdafx.cpp"
        libdirs {
            "/usr/lib/OGRE/",
            "/usr/local/lib",
            "/usr/lib/x86_64-linux-gnu/",
            "/usr/lib/"
        }

	includedirs {
            "/usr/include/OGRE/",
            "/usr/include/ois/",
            "/usr/local/include/",
            "/usr/local/include/bullet/",
            "/usr/local/include/bullet/ConvexDecomposition",          
	}

        links {
            "OgreMain",
            "OgreTerrain",
            "OIS",
            "BulletDynamics",
            "BulletCollision",
            "LinearMath",
            "sfml-system",
            "sfml-audio",
            "pthread",
            "RocketCore",
            "RocketControls"
        }

        buildoptions { "-std=c++0x"	}
    end

configuration "Debug"
    targetdir ("bin/debug")
    defines { "DEBUG" }
    flags { "Symbols" }

    if os.is("windows") then
        libdirs {
            ogre_home .. "/lib/debug",
            gamedev_libs .. "/bullet/bin",
            gamedev_libs .. "/cppunit/lib",
            gamedev_libs .. "/SFML-1.6/lib",
            ogre_home .. "/boost/lib/",
            gamedev_libs .. "/libRocket/bin"
        }
		
        links {
            "OgreMain_d",
            "OIS_d",
            "OgreTerrain_d",
            "OgrePaging_d",
            "OgreProperty_d",
            "OgreRTShaderSystem_d",
            "BulletCollision",
            "BulletDynamics",
            "LinearMath_Debug",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "RocketCore_d",
            "RocketControls_d",
			"RocketDebugger_d"
        }
		
        debugdir(ogre_home .. "/bin/debug")
    end

    if os.is("linux") then
        buildoptions { "-O2 -g" }
    end

configuration "Release"
    targetdir ("bin/release")
    defines { "NDEBUG" }
    flags { "Optimize" }

    if os.is("windows") then
        libdirs {
            ogre_home .. "/lib/release",
            gamedev_libs .. "/bullet/bin",
            gamedev_libs .. "/SFML-1.6/lib",
            ogre_home .. "/boost/lib/",
            gamedev_libs .. "/libRocket/bin"
        }
        links {
            "OgreMain",
            "OIS",
            "OgreTerrain",
            "OgrePaging",
            "OgreProperty",
            "OgreRTShaderSystem",
            "BulletCollision",
            "BulletDynamics",
            "LinearMath",
            "sfml-system-s",
            "sfml-audio-s",
            "RocketCore",
            "RocketControls"            
        }		
        debugdir(ogre_home .. "/bin/release")
    end

    if os.is("linux") then
        buildoptions { "-O3" }
    end
