/**
 * @file Earth_Shader.h
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/RotationShader.h"

using namespace CotopaxiEngine;

RotationShader::RotationShader(Entity* entity, int speed, int axis, 
        std::string materialName)
: Shader(entity, "rotation", materialName),
speed(speed),
axis(axis)
{
    this->getVertex()->setNamedConstantFromTime("time", Ogre::Real(1));
    this->getVertex()->setNamedConstant("axis", axis);
    this->getVertex()->setNamedConstant("speed", speed);
}