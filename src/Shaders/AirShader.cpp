/**
 * @file Airhader.cpp
 * @author Patrick Joos, Eduardo Hahn Paredes
 */

#include "stdafx.h"
#include "Shaders/AirShader.h"

using namespace CotopaxiEngine;
using namespace Ogre;

AirShader::AirShader(CotopaxiEngine::Entity* entity)
: Shader(entity, "air")
{
    if (SHADER_LEVEL == Shader::BASIC) {
        this->getVertex()->setNamedConstantFromTime("time", Real(1));
        this->setTexture("caustics_color.png");
    } else if (SHADER_LEVEL == Shader::ShaderLevel::INTERMEDIATE) {
        createCubeMap();
        this->getPass()->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        this->getPass()->setDepthWriteEnabled(false);

        this->getVertex()->setNamedAutoConstant("camera",
                GpuProgramParameters::ACT_CAMERA_POSITION);
        this->getVertex()->setNamedAutoConstant("world",
                GpuProgramParameters::ACT_WORLDVIEW_MATRIX);

        this->setTexture("clouds_color.png");
        this->setTexture("cubeMap");
        this->getFragment()->setNamedConstantFromTime("time", Ogre::Real(1));
        this->getFragment()->setNamedConstant("colorMap", 0);
        this->getFragment()->setNamedConstant("cubeMap", 1);
    }
}

AirShader::~AirShader()
{
    ENGINE->getSceneManager()->destroyCamera(cubeCam);
    MeshManager::getSingleton().remove("floor");
    TextureManager::getSingleton().remove("cubeMap");
}

void AirShader::createCubeMap()
{
    // creating the camera used to render to our cubemap
    Ogre::String name = entity->getName() + Ogre::String("_cubeCam");

    if (ENGINE->getSceneManager()->hasCamera(name)) {
        cubeCam = ENGINE->getSceneManager()->getCamera(name);
    } else {
        cubeCam = ENGINE->getSceneManager()->createCamera(name);
        cubeCam->setFOVy(Degree(30));
        cubeCam->setNearClipDistance(0.1);
        entity->getNode()->attachObject(cubeCam);

        // creating the dynamic cube map texture
        TexturePtr tex = TextureManager::getSingleton().createManual("cubeMap",
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                TEX_TYPE_CUBE_MAP, 128, 128, 0, PF_R8G8B8, TU_RENDERTARGET);

        // assigning the camera to all 6 render targets of the texture
        // (1 for each direction)
        for (unsigned int i = 0; i < 6; i++) {
            targets[i] = tex->getBuffer(i)->getRenderTarget();
            targets[i]->addViewport(cubeCam)->setOverlaysEnabled(false);
            targets[i]->addListener(this);
        }
    }
}

void AirShader::preRenderTargetUpdate(const RenderTargetEvent& evt)
{
    entity->getNode()->setVisible(false);
    cubeCam->setOrientation(Quaternion::IDENTITY);
    if (evt.source == targets[0]) cubeCam->yaw(Degree(-90));
    else if (evt.source == targets[1]) cubeCam->yaw(Degree(90));
    else if (evt.source == targets[2]) cubeCam->pitch(Degree(90));
    else if (evt.source == targets[3]) cubeCam->pitch(Degree(-90));
    else if (evt.source == targets[5]) cubeCam->yaw(Degree(180));
}

void AirShader::postRenderTargetUpdate(const RenderTargetEvent& evt)
{
    entity->getNode()->setVisible(true);

//        targets[0]->writeContentsToFile("file0.png");
//        targets[1]->writeContentsToFile("file1.png");
//        targets[2]->writeContentsToFile("file2.png");
//        targets[3]->writeContentsToFile("file3.png");
//        targets[4]->writeContentsToFile("file4.png");
//        targets[5]->writeContentsToFile("file5.png");

}