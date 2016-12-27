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

		//All broad phase algorithms
		npDbvt* m_dbvt;
		npSortAndSweep* m_sas;
		npUniformGrid* m_grid;
	};
}
#endif