#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "npForceGenerator.h"
#include "npParticle.h"

#include "../collision/npRigidBody.h"

#include "math/npVector3.hpp"

#include <vector>

namespace NeptunePhysics {

	class npDiscreteDynamicsWorld
	{
	public:
		npDiscreteDynamicsWorld();
		~npDiscreteDynamicsWorld();

		void stepSimulation(float _deltaTime);

		void addRigidBody(npRigidBody _body);
		void addToForceRegistry();

		npRigidBody getRigidBody(int _idx);

	private:
		npForceRegistry m_registry;
		std::vector<npRigidBody> m_rigidBodyList = std::vector<npRigidBody>();

		//Force Generators
		npGravityForce* m_gravityForce;
	};
}
#endif