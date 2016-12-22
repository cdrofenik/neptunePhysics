#include "core/npDiscreteDynamicsWorld.h"
//#include "core/npForceGenerator.h"

#include "math/npVector3.hpp"
#include "math/npTransform.hpp"

#include "collision/npAabb.h"
#include "collision/npContact.h"

#include "core/npAlignedArray.h"

namespace NeptunePhysics
{

    npDiscreteDynamicsWorld::npDiscreteDynamicsWorld()
    {
        //not real gravity anymore
        m_gravityForce = new npGravityForce(npVector3r(0.0f, -0.0f, 0.0f)); // - 0.009f
        m_dbvt = new npDbvt();
        m_pairManager = new npPairManager();
        m_sas = new npSortAndSweep(&m_pairManager);
        m_grid = new npUniformGrid();

        numRigidBodies = 0;
    }

    npDiscreteDynamicsWorld::~npDiscreteDynamicsWorld()
    {
        delete m_gravityForce;
        delete m_dbvt;
        m_registry.clear();
        m_rigidBodyList.clear();
    }

    void npDiscreteDynamicsWorld::stepSimulation(float _deltaTime)
    {
        int counter = 0;
        npAlignedArray<npAabbUpdateData> changedAabbList = npAlignedArray<npAabbUpdateData>();
        for (auto& body : m_rigidBodyList)
        {
            if (body.isAwake()) {
                npVector3r oldPositiong = body.getPosition();
                body.integrate(_deltaTime);
                npVector3r moveVector = body.getPosition() - oldPositiong;

                npAabb updatedAabb;
                updatedAabb.m_minVec = m_aabbList.at(counter).m_minVec + moveVector;
                updatedAabb.m_maxVec = m_aabbList.at(counter).m_maxVec + moveVector;
                //m_sas->update(npAabbUpdateData(m_aabbList.at(counter), moveVector), counter);
                //m_dbvt->update(npAabbUpdateData(m_aabbList.at(counter), moveVector), counter);
                m_grid->update(npAabbUpdateData(m_aabbList.at(counter), moveVector), counter);


                changedAabbList.push_back(npAabbUpdateData(m_aabbList.at(counter), moveVector));
            }
            counter++;
        }
        //Update tree

        //Broad phase -> get collisions
        //m_dbvt->getPotentialContacts(&m_pairManager);
        m_grid->getPotentialContacts(&m_pairManager);
        auto potentialPairs = m_pairManager->getPotentialPairs();

        //Narrow phase -> get actual colliding bodies
        //TODO: implement narrrow phase algorithims

        //Resolve coliding bodies
        for (int i = 0; i < potentialPairs.size(); i++)
        {
            i += 1;
            //Resolve collision
            //npPc[i].bodyA->addForce(npVector3(-0.5f, 0.0f, 0.0f));
            //npPc[i].bodyB->addForce(npVector3(0.5f, 0.0f, 0.0f));
        }

        for (int i = 0; i < changedAabbList.size(); i++)
        {
            auto currentDiff = changedAabbList[i];

            m_aabbList[i].m_maxVec = currentDiff.originalAabb.m_maxVec +
                currentDiff.directionDiff;
            m_aabbList[i].m_minVec = currentDiff.originalAabb.m_minVec +
                currentDiff.directionDiff;
        }

        m_registry.updateForces(_deltaTime);
    }

    void npDiscreteDynamicsWorld::addRigidBody(npRigidBody body, npAabb boundingVolume)
    {
        //Add rigid body to list
        m_rigidBodyList.push_back(body);
        m_aabbList.push_back(npAabb(body.getPosition() + boundingVolume.m_minVec,
            body.getPosition() + boundingVolume.m_maxVec));

        //Insert rigid body's aabb into tree
        //m_sas->insert(m_aabbList.at(numRigidBodies), numRigidBodies);
        //m_dbvt->insert(m_aabbList.at(numRigidBodies), numRigidBodies);
        m_grid->insert(m_aabbList.at(numRigidBodies), numRigidBodies);
        numRigidBodies++;
    }

    void npDiscreteDynamicsWorld::addToForceRegistry()
    {
        std::vector<npRigidBody>::iterator iter;
        int counter = 0;
        for (iter = m_rigidBodyList.begin(); iter != m_rigidBodyList.end(); iter++) {
            m_registry.add(&(*iter), m_gravityForce);
            counter++;
        }
    }

    npRigidBody npDiscreteDynamicsWorld::getRigidBody(int _idx)
    {
        return m_rigidBodyList.at(_idx);
    }

}