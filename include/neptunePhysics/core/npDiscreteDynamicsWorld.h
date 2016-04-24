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

		void addParticle(npParticle _body);
		void addToForceRegistry();

		npParticle getParticle(int _idx);

	private:
		//std::vector<npRigidBody> m_rigidBody = std::vector<npRigidBody>();

		npParticleForceRegistry m_registry;
		std::vector<npParticle> m_particleList = std::vector<npParticle>();

		//Force Generators
		npParticleGravity* m_particleGravity;
		npParticle* m__particleBungee;
		npParticleBungee* m_particleBungee;
		npParticleAnchoredSpring* m_particleAnchored;
		npParticleBouyancy* m_particleBouyancy;
	};
}
#endif