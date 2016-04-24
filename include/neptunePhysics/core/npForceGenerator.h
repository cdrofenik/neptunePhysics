#ifndef NEPTUNE_NPFORCEGENERATOR_H
#define NEPTUNE_NPFORCEGENERATOR_H

#include "npParticle.h"

#include <vector>

namespace NeptunePhysics {

	class npParticleForceGenerator
	{
	public:
		virtual void updateForce(npParticle* particle, npReal duration) = 0;
	};

	class npParticleGravity : public npParticleForceGenerator
	{
	public:
		npParticleGravity(npVector3 _gravity) : m_gravity(_gravity) {};
		~npParticleGravity() {};
		
		virtual void updateForce(npParticle* particle, npReal duration);

	private:
		npVector3 m_gravity;
	};

	class npParticleSpring : public npParticleForceGenerator
	{
	public:
		npParticleSpring(npParticle* _particle, npReal _springContant, npReal _length) :
			m_other(_particle), m_springConstant(_springContant), m_realLength(_length) {};
		~npParticleSpring() {};


		virtual void updateForce(npParticle* particle, npReal duration);

	private:
		npParticle* m_other;
		npReal m_springConstant;
		npReal m_realLength;
	};

	class npParticleAnchoredSpring : public npParticleForceGenerator
	{
	public:
		npParticleAnchoredSpring(npVector3 _anchor, npReal _springContant, npReal _length) :
			m_anchor(_anchor), m_springConstant(_springContant), m_restLength(_length) {};
		~npParticleAnchoredSpring() {};

		virtual void updateForce(npParticle* particle, npReal duration);

	private:
		npVector3 m_anchor;
		npReal m_springConstant;
		npReal m_restLength;
	};

	class npParticleBungee : public npParticleForceGenerator
	{
	public:
		npParticleBungee(npParticle* _particle, npReal _springContant, npReal _length) :
			m_other(_particle), m_springConstant(_springContant), m_restLength(_length) {};
		~npParticleBungee() {};

		virtual void updateForce(npParticle* particle, npReal duration);

	private:
		npParticle* m_other;
		npReal m_springConstant;
		npReal m_restLength;
	};

	class npParticleBouyancy : public npParticleForceGenerator
	{
	public:
		npParticleBouyancy(npReal _maxDepth, npReal _volume, npReal _waterHeight,
			npReal _liquidDensity = 1000.0f) :
			m_maxDepth(_maxDepth), m_volume(_volume), m_waterHeight(_waterHeight),
			m_liquidDensirt(_liquidDensity) {};
		~npParticleBouyancy() {};

		virtual void updateForce(npParticle* particle, npReal duration);

	private:
		npReal m_maxDepth;
		npReal m_volume;
		npReal m_waterHeight;
		npReal m_liquidDensirt;
	};

	class npParticleForceRegistry
	{
	protected:
		struct npParticleForceRegistration
		{
			npParticleForceRegistration(npParticleForceGenerator *_fg, npParticle *_particle) :
				particle(_particle), fg(_fg) {};

			npParticle *particle;
			npParticleForceGenerator *fg;
		};

		typedef std::vector<npParticleForceRegistration> _Registry;
		_Registry registration;

	public:

		void add(npParticle* particle, npParticleForceGenerator * generator);

		npParticle* getParticle(int _index);

		void remove(npParticle* particle, npParticleForceGenerator * generator);

		void clear();

		void updateForces(npReal duration);
	};

	/*class npForceGenerator
	{
	public:
		virtual void updateForce(npRigidBody *body, npReal duration) = 0;
	};

	class npGravityForce : public npForceGenerator
	{
		npVector3 m_gravity;
	public:
		npGravityForce(const npVector3 &_gravity);
		virtual void updateForce(npRigidBody *body, npReal duration) = 0;
	};*/


}


#endif