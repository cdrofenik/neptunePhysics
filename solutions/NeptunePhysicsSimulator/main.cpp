#include "main.h"

// Neptune Physics
#include "neptunePhysics/Math/npTransform.hpp"
#include "neptunePhysics/Collision/CollisionShapes/npCollisionShape.h"
#include "neptunePhysics/Core/npDiscreteDynamicsWorld.h"
#include "neptunePhysics/Dynamics/npRigidBody.h"

// Logging
#include "logging\npLogging.hpp"

// Refactoring
#include "Camera.h"
#include "ModelShader.h"
#include "DisplayManager.h"
#include "ObjectLoader.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "DrawableBV.h"

// GLM
#include <glm/glm.hpp>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

using namespace NeptunePhysics;

Camera gameCamera;

bool wireFrameMode = true;
bool showBoundingVolumes = true;

bool pauseSimulation = false;
bool keys[1024];
bool firstMouse = true;

GLdouble deltaTime = 0;
GLdouble lastFrame = 0;
double lastX;
double lastY;

//TODO: Create Manager struct as container for data
std::vector<DrawableBV> drawableModelList;

// Keyboard input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //Wireframe mode
    if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        wireFrameMode = !wireFrameMode;
        glPolygonMode(GL_FRONT_AND_BACK, wireFrameMode ? GL_LINE : GL_FILL);
    }

    //Pause simulation
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        pauseSimulation = !pauseSimulation;
    }

    //Pause simulation
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        showBoundingVolumes = !showBoundingVolumes;
    }

    //Close application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // Resolves muliple buttons pressed at the same 
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void initializeObjects(npDiscreteDynamicsWorld* world, const glm::vec3& minValues, const glm::vec3& maxValues)
{
    unsigned int rigidBodyCount = 2;
    
    npVector3r Pos(0.0f, 2.75f, 0.0f);
    npVector3r veloPos(0, 0, 0);
    npVector3r accelPos(0, 0, 0);

    drawableModelList.clear();
    //for (size_t i = 0; i < rigidBodyCount; i++)
    //{
    //    npVector3 startPos = Pos + npVector3(i * 1.5f, i * 2.75f, 0.0f);

    //    npRigidBody tmpBody(5, startPos, veloPos, accelPos);
    //    tmpBody.setAngularDamping(0.05f);
    //    tmpBody.setLinearDamping(0.011f);
    //    world->addRigidBody(tmpBody);

    //    //Adding drawable bounding volume
    //    DrawableAABB drawnBody(minValues, maxValues);
    //    drawableModelList.push_back(drawnBody);
    //}
    int indexCounter = 2;

    npAabb bodyAabb = npAabb(
        npVector3r(minValues.x, minValues.y, minValues.z),
        npVector3r(maxValues.x, maxValues.y, maxValues.z)
    );

    npVector3r startPos1 = Pos + npVector3r(-2.5f * indexCounter, 0.0f, 0.0f);
    npRigidBody body1(5, startPos1, veloPos, accelPos);
    body1.setAngularDamping(0.05f);
    body1.setLinearDamping(0.011f);
    body1.addForce(npVector3r(0.5f, 0.0f, 0.0f));
    world->addRigidBody(body1, bodyAabb);

    indexCounter++;
    npVector3r startPos2 = Pos + npVector3r(+2.5f * indexCounter, 0.0f, 0.0f);
    npRigidBody body2(5, startPos2, veloPos, accelPos);
    body2.setAngularDamping(0.05f);
    body2.setLinearDamping(0.011f);
    body2.addForce(npVector3r(-0.5f, 0.0f, 0.0f));
    world->addRigidBody(body2, bodyAabb);

    //Adding drawable bounding volume
    DrawableAABB drawnBody1(minValues, maxValues);
    drawableModelList.push_back(drawnBody1);

    DrawableAABB drawnBody2(minValues, maxValues);
    drawableModelList.push_back(drawnBody2);

    //Earth plane (approx.)
    /*npRigidBody _tmpBody(0, npVector3(0.0f, 0.0f, 0.0f), veloPos, accelPos);
    world->addRigidBody(_tmpBody);*/

    DrawablePlane tmpPlane(glm::vec3(-50, 0, -50), 100, 100);
    drawableModelList.push_back(tmpPlane);

    //Adding force generators
    world->addToForceRegistry();
}

//TODO refactor this
NeptunePhysics::npMatrix4 create4x4Matrix(const NeptunePhysics::npMatrix3x4& matrix_)
{
    NeptunePhysics::npMatrix4 result(matrix_);
    return result;
}

// Callback for mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    gameCamera.ProcessMouseMovement(xoffset, yoffset);
}

int main() {

    DisplayManager displayManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Neptune Physics Simulator");
    displayManager.Enable(GL_DEPTH_TEST);
    //displayManager.Enable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //Input handling
    glfwSetInputMode(displayManager.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(displayManager.getWindow(), key_callback);
    glfwSetCursorPosCallback(displayManager.getWindow(), mouse_callback);

    //TODO: Add to camera setup
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    projection = glm::perspective(45.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    Renderer objRenderer;
    ObjectLoader objLoader;

    //Load Texture
    TextureLoader textLoader;
    GLuint textureId = textLoader.LoadTexture("..\\..\\external\\resources\\textures\\container.png");

    //Loading OBJ mesh
    auto meshRawModel = objLoader.LoadMesh("..\\..\\external\\resources\\objects\\suzanne.obj");

    //Init physics system
    npDiscreteDynamicsWorld* world = new npDiscreteDynamicsWorld();
    initializeObjects(world, meshRawModel.minVector, meshRawModel.maxVector);

    Light staticLight;
    staticLight.position = glm::vec3(0.0f, 1.0f, 10.0f);
    staticLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

    //Init Shaders
    ModelShader meshShader("shaders\\vertexShader.vert", "shaders\\fragmentShader.frag");
    ModelShader BVShader("shaders\\BVvertexShader.vert", "shaders\\BVfragmentShader.frag");

    while (!glfwWindowShouldClose(displayManager.getWindow()))
    {
        GLdouble currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        gameCamera.ProcessKeyboard(keys, deltaTime);

        objRenderer.PrepareForRendering();

        if (!pauseSimulation) {
            world->stepSimulation(deltaTime);
        }
        

        for (size_t i = 0; i < 2; i++)
        {
            auto rigidBdy = world->getRigidBody(i);

            if (!pauseSimulation) {
                Log_DEBUG("main.cpp - 197", "Body position:", rigidBdy.getPosition());
            }

            npMatrix4 resultingModelMatrix = create4x4Matrix(rigidBdy.getTransformMatrix()).transpose();

            //drawableBV has VBOs (vertex, color)
            BVShader.Use();
            BVShader.LoadViewMatrix(gameCamera.GetViewMatrix());
            BVShader.LoadProjectionMatrix(projection);
            BVShader.LoadModelMatrix(resultingModelMatrix);
            objRenderer.Render(drawableModelList.at(i));
            BVShader.Stop();


            //meshRawModel has other VBOs (vertex, normal, texCoords)
            meshShader.Use();
            meshShader.LoadViewMatrix(gameCamera.GetViewMatrix());
            meshShader.LoadProjectionMatrix(projection);
            meshShader.LoadModelMatrix(resultingModelMatrix);
            meshShader.LoadLightPosition(staticLight.position);
            meshShader.LoadLightColor(staticLight.color);
            meshShader.LoadShineVariables(0.0f, 0.0f);
            textLoader.UseTexture(textureId, meshShader.getProgramID(), "ourTexture");
            objRenderer.Render(meshRawModel, wireFrameMode);
            meshShader.Stop();
        }

        displayManager.UpdateDisplay();
    }

    objLoader.CleanUp();
    textLoader.CleanUp();
    displayManager.CloseDisplay();

    return 1;
    
}