#include "core/npDiscreteDynamicsWorld.h"

#include "math/npTransform.hpp"

#include "logging/npLogging.hpp"

namespace NeptunePhysics {

	npDiscreteDynamicsWorld::npDiscreteDynamicsWorld()
	{
		//Initilize starting forces
		m_forces.push_back(npVector3(.0f, -0.98f, .0f)); // force of gravity * 0.1

	}

	npDiscreteDynamicsWorld::~npDiscreteDynamicsWorld()
	{

	}

	void npDiscreteDynamicsWorld::stepSimulation(float _deltaTime)
	{
		// Iterate through rigid bodies
		//}
		for (auto& body : m_rigidBodyList)
		{
			//calculate physics for each body positions
			npVector3 forcesSum;
			for (auto force : m_forces)
			{
				forcesSum += force;
			}

			//Calulcate new position
			npVector3 translation = forcesSum * _deltaTime;
			npVector3 oldPos = body.getPosition();
			npVector3 newPos = oldPos + translation;

			//Set new positions for rigid body
			body.setNewPosition(newPos);
		}
	}

	void npDiscreteDynamicsWorld::addRigidBody(npRigidBody _body)
	{
		m_rigidBodyList.push_back(_body);
	}

	npRigidBody npDiscreteDynamicsWorld::getRigidBody(int _idx)
	{
		return m_rigidBodyList.at(_idx);
	}

}