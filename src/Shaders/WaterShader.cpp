/**
 * @file WaterShader.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/WaterShader.h"

using namespace CotopaxiEngine;

WaterShader::WaterShader(Entity* entity)
: Shader(entity, "water")
{
    if (SHADER_LEVEL == Shader::BASIC) {
        this->setTexture("ocean_floor_color.png");
        this->setTexture("caustics_color.png");
		this->getVertex()->setNamedConstantFromTime("time", Ogre::Real(1));
    } else if (SHADER_LEVEL == Shader::ShaderLevel::INTERMEDIATE) {
        this->setTexture("sun_color.png");
        this->setTexture("ocean_floor_color.png");
        this->getFragment()->setNamedConstant("LightMap", 0);
        this->getFragment()->setNamedConstant("GroundMap", 1);
        this->getFragment()->setNamedConstantFromTime("time", Ogre::Real(1));
    }
}