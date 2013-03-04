/**
 * @file FireShader.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/FireShader.h"

using namespace CotopaxiEngine;

FireShader::FireShader(Entity* entity)
: Shader(entity, "fire")
{
    if (SHADER_LEVEL == Shader::BASIC) {
        this->getFragment()->setNamedConstantFromTime("time", Ogre::Real(1));
        this->getFragment()->setNamedConstant("startColor", Ogre::ColourValue(1, 1, 0, 1));
        this->getFragment()->setNamedConstant("endColor", Ogre::ColourValue(1, 0, 0, 1));
    } else if (SHADER_LEVEL == Shader::ShaderLevel::INTERMEDIATE) {
		this->getFragment()->setNamedConstantFromTime("time", Ogre::Real(1));
		this->getFragment()->setNamedConstant("modifier", 0.1f);

		this->setTexture("lava_cloud.png");
		this->getFragment()->setNamedConstant("Texture1", 0);
		this->setTexture("lava_tile.jpg");
		this->getFragment()->setNamedConstant("Texture2", 1);
    }
}