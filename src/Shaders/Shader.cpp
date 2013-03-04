/**
 * @file Shader.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/Shader.h"
#include "Entities/Entity.h"
#include <string>

using namespace CotopaxiEngine;
using namespace Ogre;

Shader::Shader(CotopaxiEngine::Entity* entity, std::string shaderName, std::string materialName)
: entity(entity),
shaderName(shaderName),
materialName(materialName)
{
    load();
}

Shader::~Shader()
{
    delete pass;
}

void Shader::load()
{
    // determining shader level and generating a part of the level string 
    std::string levelString = "_basic";
    if (SHADER_LEVEL == INTERMEDIATE) {
        levelString = "_intermediate";
    } else if (SHADER_LEVEL == ADVANCED) {
        levelString = "_advanced";
    }

    std::string vertexString;
    std::string geometryString;
    std::string fragmentString;

    // trying to use actual shader level, choosing basic as default/backup
    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(shaderName + levelString + ".vert")) {
        vertexString = shaderName + levelString + ".vert";
    } else {
        vertexString = shaderName + "_basic.vert";
    }

    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(shaderName + levelString + ".geom")) {
        geometryString = shaderName + levelString + ".geom";
    } else {
        geometryString = shaderName + "_basic.geom";
    }

    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(shaderName + levelString + ".frag")) {
        fragmentString = shaderName + levelString + ".frag";
    } else {
        fragmentString = shaderName + "_basic.frag";
    }

    // creating new material
    material = MaterialManager::getSingletonPtr()->create(materialName + shaderName,
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    pass = material->getTechnique(0)->getPass(0);

    // with dynamic lighting only geometry with normals will be displayed
    pass->setLightingEnabled(true);
    material->setReceiveShadows(true);

    // loading vertex shader if there is one
    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(vertexString)) {
        HighLevelGpuProgramPtr vertex =
                HighLevelGpuProgramManager::getSingletonPtr()->createProgram(
                shaderName + "_v",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                "glsl", GpuProgramType::GPT_VERTEX_PROGRAM);
        vertex->setSourceFile(vertexString);
        pass->setVertexProgram(vertex->getName());
    }
	
    // loading geometry shader if there is one
    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(geometryString)) {
        geometry = HighLevelGpuProgramManager::getSingletonPtr()->createProgram(
                shaderName + "_g",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "glsl",
                GpuProgramType::GPT_GEOMETRY_PROGRAM);
        geometry->setSourceFile(geometryString);
        pass->setGeometryProgram(geometry->getName());
    }

    // loading fragment shader if there is one
    if (ResourceGroupManager::getSingleton()
            .resourceExistsInAnyGroup(fragmentString)) {
        HighLevelGpuProgramPtr fragment =
                HighLevelGpuProgramManager::
                getSingletonPtr()->createProgram(shaderName + "_f",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                "glsl", GpuProgramType::GPT_FRAGMENT_PROGRAM);
        fragment->setSourceFile(fragmentString);
        pass->setFragmentProgram(fragment->getName());
    }
    entity->getOgreEntity()->setMaterialName(material->getName());
}

GpuProgramParametersSharedPtr Shader::getVertex()
{
    return pass->getVertexProgramParameters();
}

GpuProgramParametersSharedPtr Shader::getFragment()
{
    return pass->getFragmentProgramParameters();
}

GpuProgramParametersSharedPtr Shader::getGeometry()
{
    return pass->getGeometryProgramParameters();
}

void Shader::setTexture(std::string name, std::string parameterName)
{
    TextureUnitState* texture = getPass()->createTextureUnitState(name);
    texture->setTextureNameAlias(parameterName);
    texture->setName(parameterName);
}

void Shader::setGeometryShaderParameters(Ogre::RenderOperation::OperationType in,
        Ogre::RenderOperation::OperationType out, int max)
{
    GLSLProgram* t = static_cast<GLSLProgram*> (geometry.getPointer());
    t->setInputOperationType(in);
    t->setOutputOperationType(out);
    t->setMaxOutputVertices(max);
}