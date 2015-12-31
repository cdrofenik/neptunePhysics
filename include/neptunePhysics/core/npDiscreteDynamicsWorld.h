#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "math/npVector3.hpp"
#include "collision/npRigidBody.h"

#include <vector>

namespace NeptunePhysics {

	class npDiscreteDynamicsWorld
	{
	public:
		npDiscreteDynamicsWorld();
		~npDiscreteDynamicsWorld();

		void stepSimulation(float _deltaTime);

		void addRigidBody(npRigidBody _body);

		npRigidBody getRigidBody(int _idx);

	private:
		std::vector<npVector3> m_forces;
		std::vector<npRigidBody> m_rigidBodyList = std::vector<npRigidBody>();
	};
}
#endif