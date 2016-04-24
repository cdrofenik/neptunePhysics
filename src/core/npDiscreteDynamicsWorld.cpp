#include "core/npDiscreteDynamicsWorld.h"

#include "core/npForceGenerator.h"

#include "math/npTransform.hpp"

namespace NeptunePhysics {

	npDiscreteDynamicsWorld::npDiscreteDynamicsWorld()
	{
		m_particleGravity = new npParticleGravity(npVector3(0.0f, -2.99f, 0.0f));
		
		//Add other springs
		m__particleBungee = new npParticle(npVector3(3, 18, 0),
			npVector3(0, 0, 0), npVector3(0, 0, 0), 0.0f, 0.0f);

		m_particleBungee = new npParticleBungee(m__particleBungee, 8.0f, 6.0f);


		//Achored spring
		m_particleAnchored = new npParticleAnchoredSpring(npVector3(0.0f, 4.0f, 0.0f), 1.0f, 3.5f);

		//Bouyancy spring
		m_particleBouyancy = new npParticleBouyancy(0.05f, 11.1f, 0.0f);
	}

	npDiscreteDynamicsWorld::~npDiscreteDynamicsWorld()
	{
		m_particleGravity = nullptr;
		m_registry.clear();
		m_particleList.clear();
	}

	void npDiscreteDynamicsWorld::stepSimulation(float _deltaTime)
	{
		for (auto& body : m_particleList)
		{
			body.integrate(_deltaTime);
		}

		m_registry.updateForces(_deltaTime);
	}

	void npDiscreteDynamicsWorld::addParticle(npParticle _body)
	{
		m_particleList.push_back(_body);
	}

	void npDiscreteDynamicsWorld::addToForceRegistry()
	{
		std::vector<npParticle>::iterator iter;
		int counter = 0;
		for (iter = m_particleList.begin(); iter != m_particleList.end(); iter++) {
			switch (counter)
			{
			case 0:
				m_registry.add(&(*iter), m_particleAnchored);
				break;
			case 1:
				m_registry.add(&(*iter), m_particleBouyancy);
				break;
			case 2:
				m_registry.add(&(*iter), m_particleBungee);
				break;
			default:
				m_registry.add(&(*iter), m_particleGravity);
				break;
			}
			counter++;
		}
	}

	npParticle npDiscreteDynamicsWorld::getParticle(int _idx)
	{
		return m_particleList.at(_idx);
	}

}