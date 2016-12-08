#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "npForceGenerator.h"
#include "npParticle.h"

#include "../collision/npRigidBody.h"
#include "../collision/npDbvt.h"
#include "../collision/npSortAndSweep.h"

#include <vector>

namespace NeptunePhysics {

	class npDiscreteDynamicsWorld
	{
	public:
		npDiscreteDynamicsWorld();
		~npDiscreteDynamicsWorld();

		void stepSimulation(float _deltaTime);

		void addRigidBody(npRigidBody _body, npAabb boundingVolume);
		void addToForceRegistry();

		npRigidBody getRigidBody(int _idx);

	private:
		std::vector<npRigidBody> m_rigidBodyList = std::vector<npRigidBody>();
		std::vector<npAabb> m_aabbList = std::vector<npAabb>();
		int numRigidBodies;

		npForceRegistry m_registry;

		//Pair Manager
		npPairManager* m_pairManager;

		//Force Generators
		npGravityForce* m_gravityForce; //not real gravity anymore

		//All rigid body tree
		npDbvt* m_dbvt;
		npSortAndSweep* m_sas;
	};
}
#endif