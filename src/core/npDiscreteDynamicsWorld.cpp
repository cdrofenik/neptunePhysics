#include "Core/npDiscreteDynamicsWorld.h"
#include "Core/npAlignedArray.hpp"

#include "math/npVector3.hpp"
#include "math/npTransform.hpp"

#include "Collision/CollisionShapes/npAabb.h"
#include "Collision/CollisionShapes/npBoxShape.h"
#include "Collision/NarrowPhase/npCollisionAlgorithm.h"

namespace NeptunePhysics
{

	npDiscreteDynamicsWorld::npDiscreteDynamicsWorld()
	{
		m_pairManager = new npPairManager();
		m_broadphase = new npSweepAndPrune(m_pairManager); //npDbvt, npUniformGrid, npSortAndSweep(m_pairManager)

		npPUniformGrid* test = new npPUniformGrid();

		numRigidBodies = 0;
	}

	npDiscreteDynamicsWorld::~npDiscreteDynamicsWorld()
	{
		delete m_broadphase;
		delete m_pairManager;
		m_registry.clear();
		m_rigidBodyList.clear();

		numRigidBodies = 0;
	}

	//Check if colliding return - collision pair info to pair manager if really colliding
	//Narrow phase + Generating Collisions
	void npDiscreteDynamicsWorld::checkNarrowPhase()
	{
		unsigned int size = m_pairManager->getPotentialPairs().size();
		if (size > 0)
		{
			npAlignedArray<npPotentialPair> pairs = m_pairManager->getPotentialPairs();
			for (unsigned int i = 0; i < size; i++)
			{
				//Get pair
				npCollisionObject* obj0 = &m_rigidBodyList.at(pairs.at(i).bodyIdA);
				npCollisionObject* obj1 = &m_rigidBodyList.at(pairs.at(i).bodyIdB);

				//Process pair - Narrow phase
				npCollisionInfo info;
				info.setCollisionObjects(obj0, obj1);
				if (npCollisionAlgorithm::processCollision(obj0, obj1, info))
					m_pairManager->addCollisionPairInfo(info);
				else
					m_pairManager->removeCollisionPairInfo(info);
			}
		}
		
	}

	void npDiscreteDynamicsWorld::stepSimulation(float _deltaTime)
	{
		int counter = 0;
		npAlignedArray<npAabbUpdateData> changedAabbList = npAlignedArray<npAabbUpdateData>();
		for (auto& body : m_rigidBodyList)
		{
			if (body.isAwake() && body.getInverseMass() > 0) {
				npVector3r oldPositiong = body.getPosition();
				body.integrate(_deltaTime);
				npVector3r moveVector = body.getPosition() - oldPositiong;

				npAabb updatedAabb;
				updatedAabb.m_minVec = m_aabbList.at(counter).m_minVec + moveVector;
				updatedAabb.m_maxVec = m_aabbList.at(counter).m_maxVec + moveVector;
				m_broadphase->update(npAabbUpdateData(m_aabbList.at(counter), moveVector), counter);

				changedAabbList.push_back(npAabbUpdateData(m_aabbList.at(counter), moveVector));
			}
			counter++;
		}

		//BROAD PHASE
		m_broadphase->getPotentialContacts(m_pairManager);

		//NARROW PHASE
		checkNarrowPhase();

		//Collision Resolve?


		//Updated aabb list
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

	void npDiscreteDynamicsWorld::addRigidBody(const npRigidBody &body, npAabb boundingVolume)
	{
		//Add rigid body to list
		m_rigidBodyList.push_back(body);
		m_aabbList.push_back(npAabb(body.getPosition() + boundingVolume.m_minVec,
			body.getPosition() + boundingVolume.m_maxVec));

		//Add aabb to broadPhase algorithm
		m_broadphase->insert(m_aabbList.at(numRigidBodies), numRigidBodies);

		numRigidBodies++;
	}

	void npDiscreteDynamicsWorld::addConstantForce(const unsigned int &_index, npForceGenerator* _generator)
	{
		npIndexForces idxFrc;
		idxFrc.index = _index;
		idxFrc.force = _generator;
		m_registeredForces.push_back(idxFrc);
	}

	void npDiscreteDynamicsWorld::setupForceRegistry()
	{
		std::vector<npRigidBody>::iterator iter;
		int counter = 0;
		for (int i = 0; i < m_registeredForces.size(); i++)
		{
			npRigidBody* rb = &m_rigidBodyList.at(m_registeredForces.at(i).index);
			m_registry.add(rb, m_registeredForces.at(i).force);
		}
	}

	npRigidBody npDiscreteDynamicsWorld::getRigidBody(int _idx)
	{
		return m_rigidBodyList.at(_idx);
	}

}