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
std::vector<DrawableShape> drawableModelList;

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

npRigidBody generateRigidBody(
    npDiscreteDynamicsWorld* world,
    const npAabb &bodyAabb,
    const npVector3r &startPosition,
    npForceGenerator* forceGenerator,
    const npCollisionShapeType &type,
    unsigned int &count)
{
    npRigidBody rBody(10,
        startPosition,
        npVector3r(0.0, 0.0, 0.0),
        npVector3r(0.0, 0.0, 0.0));
    
    npCollisionShape* shape = new npBoxShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());
    if (type == npCollisionShapeType::SPHERE_SHAPE)
        shape = new npSphereShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());

    rBody.setAngularDamping(0.05f);
    rBody.setLinearDamping(0.011f);
    rBody.setCollisionShape(shape);

    world->addRigidBody(rBody, bodyAabb);
    world->addConstantForce(count, forceGenerator);
    count++;

    return rBody;
}

void initializeObjects(npDiscreteDynamicsWorld* world, const glm::vec3& minValues, const glm::vec3& maxValues)
{
    unsigned int rigidBodyCount = 2;
    
    npVector3r Pos(0.0f, 0.0f, 0.0f);
    npVector3r veloPos(0, 0, 0);
    npVector3r accelPos(0, 0, 0);

    drawableModelList.clear();
    int indexCounter = 2;

    npAabb bodyAabb = npAabb(
        npVector3r(minValues.x, minValues.y, minValues.z),
        npVector3r(maxValues.x, maxValues.y, maxValues.z)
    );

    npVector3r startPos1 = npVector3r(-0.9, 0.0f, 0.0f);
    unsigned int counter = 0;
    npLinearPendulumForce* pForce = new
        npLinearPendulumForce(startPos1, startPos1 +
            npVector3r(1.1f, 0.0f, 0.0f), 3);
    auto body = generateRigidBody(world,
        bodyAabb,
        startPos1,
        pForce,
        npCollisionShapeType::BOX_SHAPE,
        counter);

    DrawableShape bodyShape;
    if (body.getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE) {
        bodyShape = Box(minValues, maxValues);
    }
    else if (body.getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE) {
        bodyShape = Sphere(minValues, maxValues);
    }
    drawableModelList.push_back(bodyShape);

    indexCounter++;
    npVector3r startPos2 = npVector3r(0.9, 0.0f, 0.0f);
    npLinearPendulumForce* pForce2 = new
        npLinearPendulumForce(startPos2, startPos2 +
            npVector3r(-1.1f, 0.0f, 0.0f), 3);
    body = generateRigidBody(world,
        bodyAabb,
        startPos2,
        pForce2,
        npCollisionShapeType::SPHERE_SHAPE,
        counter);

    if (body.getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE) {
        bodyShape = Box(minValues, maxValues);
    }
    else if (body.getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE) {
        bodyShape = Sphere(minValues, maxValues);
    }
    drawableModelList.push_back(bodyShape);

    //Adding force generators
    world->setupForceRegistry();
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
    auto meshRawModel = objLoader.LoadMesh("..\\..\\external\\resources\\objects\\suzanneSmall.obj");

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

            #ifdef _DEBUG
            if (!pauseSimulation) {
                Log_DEBUG("main.cpp - 197", "Body position:", rigidBdy.getPosition());
            }
            #endif

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