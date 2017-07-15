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

default("windows", "vs2017")
default("linux", "gmake")


workspace "Thesis"
    configurations { "Debug", "Release" }
    
    if os.is("windows") then
        configuration { "windows" }

        pchheader "stdafx.h"
        pchsource "src/stdafx.cpp"

    	ogre_home = os.getenv("OGRE_HOME")
    	gamedev_libs = os.getenv("GAMEDEV_LIBS")
    	boost_include = os.getenv("BOOST_INCLUDE")
    	boost_libs = os.getenv("BOOST_LIBS")

    	includedirs {
            "include/BOOST",
            "include/OGRE",
            "include/OIS",
            "include/BULLET",
            "include/SFML",
            "include/LIBROCKET"
        }

        libdirs {
            "libs/extlibs/SFML" ,
            "libs/extlibs/BOOST"
        }
        os.remove("Thesis.sdf")
        buildoptions { "/Zm500" }
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


project "Engine"
    kind "WindowedApp"
    language "C++"

    files { "headers/**.h", "src/**.cpp", "media/shaders/**.frag", "media/shaders/**.geom", "media/shaders/**.vert" }
    includedirs { "headers" }
    flags {"StaticRuntime"}



configuration "Debug"
    targetdir ("bin/debug")
    defines { "DEBUG" }
    symbols "On"

    if os.is("windows") then
        libdirs {
            "libs/Debug/OGRE",
            "libs/Debug/BULLET",
            "libs/Debug/SFML",
            "libs/extlibs/BOOST",
            "libs/Debug/LIBROCKET"
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
            "LinearMath",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "RocketCore",
            "RocketControls",
			"RocketDebugger"
        }
		
        debugdir("libs/Debug/OGRE")
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
            gamedev_libs .. "/bullet-2.80-rev2531/lib",
            gamedev_libs .. "/SFML-1.6/lib/",
            ogre_home .. "/boost_1_47/lib/",
            gamedev_libs .. "/libRocket/Build/Release"
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