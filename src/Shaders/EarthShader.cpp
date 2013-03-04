/**
 * @file EarthShader.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/EarthShader.h"

using namespace CotopaxiEngine;

EarthShader::EarthShader(Entity* entity)
: Shader(entity, "earth")
{
    if (SHADER_LEVEL == Shader::BASIC) {
        this->setTexture("dirt_color.png");
    } else if (SHADER_LEVEL == Shader::ShaderLevel::INTERMEDIATE) {
        this->setTexture("dirt_color.png");
        this->setTexture("dirt_normal.png");
        this->getVertex()->setNamedAutoConstant("light", 
                Ogre::GpuProgramParameters::ACT_LIGHT_POSITION, 0);
        this->getVertex()->setNamedAutoConstant("camera", 
                Ogre::GpuProgramParameters::ACT_CAMERA_POSITION);
        this->getFragment()->setNamedConstant("dirt_color", 0);
        this->getFragment()->setNamedConstant("dirt_normal", 1);
    }
}