#include "core/npDiscreteDynamicsWorld.h"

#include "core/npForceGenerator.h"

#include "math/npTransform.hpp"

namespace NeptunePhysics {

	npDiscreteDynamicsWorld::npDiscreteDynamicsWorld()
	{
		m_gravityForce = new npGravityForce(npVector3(0.0f, -0.009f, 0.0f));
	}

	npDiscreteDynamicsWorld::~npDiscreteDynamicsWorld()
	{
		m_gravityForce = nullptr;
		m_registry.clear();
		m_rigidBodyList.clear();
	}

	void npDiscreteDynamicsWorld::stepSimulation(float _deltaTime)
	{
		for (auto& body : m_rigidBodyList)
		{
			body.integrate(_deltaTime);
		}

		m_registry.updateForces(_deltaTime);
	}

	void npDiscreteDynamicsWorld::addRigidBody(npRigidBody _body)
	{
		m_rigidBodyList.push_back(_body);
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