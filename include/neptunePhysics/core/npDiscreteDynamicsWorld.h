#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "npForceGenerator.h"

#include "../Collision/CollisionShapes/npAabb.h"
#include "../Dynamics/npParticle.h"
#include "../Dynamics/npRigidBody.h"
#include "../Collision/BroadPhase/npDbvt.h"
#include "../Collision/BroadPhase/npSortAndSweep.h"
#include "../Collision/BroadPhase/npUniformGrid.h"

#include <vector>

namespace NeptunePhysics {

	class npDiscreteDynamicsWorld
	{
	public:
		npDiscreteDynamicsWorld();
		~npDiscreteDynamicsWorld();

		void stepSimulation(float _deltaTime);

		void addRigidBody(const npRigidBody &_body, npAabb boundingVolume);
		void addConstantForce(const unsigned int &_index, npForceGenerator* _generator);
		void setupForceRegistry();

		npRigidBody getRigidBody(int _idx);

	private:
		std::vector<npRigidBody> m_rigidBodyList = std::vector<npRigidBody>();
		std::vector<npAabb> m_aabbList = std::vector<npAabb>();
		int numRigidBodies;

		npForceRegistry m_registry;
		npAlignedArray<npIndexForces> m_registeredForces = npAlignedArray<npIndexForces>();


		//Pair Manager
		npPairManager* m_pairManager;

		npIBroadPhase* m_broadphase;

		void checkNarrowPhase();
	};
}
#endif