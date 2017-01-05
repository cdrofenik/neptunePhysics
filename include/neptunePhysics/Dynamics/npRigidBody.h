#ifndef NEPTUNE_NPRIGIDBODY_H
#define NEPTUNE_NPRIGIDBODY_H

#include "Math/npMatrix3x4.hpp"

#include "Core/npMotionState.h"

#include "Collision/npCollisionObject.h"

namespace NeptunePhysics {

	class npRigidBody : public npCollisionObject
	{
	public:
		npRigidBody(const float& _mass, const npVector3r& _position,
			const npVector3r& _velocity, const npVector3r& _acceleration) :
			m_inverseMass(_mass),
			m_position(_position),
			m_velocity(_velocity),
			m_acceleration(_acceleration) {}

		~npRigidBody() {}

	protected:
		npReal m_inverseMass;
		npReal m_linearDamping;
		npReal m_angularDamping;

		npVector3r m_position;
		npVector3r m_velocity;
		npVector3r m_acceleration;

		npVector3r m_rotation;
		npQuarternion m_orientation;

		npMatrix3 m_inverseInertiaTensor;
		npMatrix3 m_inverseInertiaTensorWorld;

		npVector3r m_forceAccum;
		npVector3r m_torqueAccum;

		npVector3r m_lastFrameAcceleration;

		bool m_isAwake;
		bool m_canSleep;

	public:
		#pragma region Setters/Getters

		void setInverseMass(const npReal &_imass);
		npReal getInverseMass() const;

		void setLinearDamping(const npReal &_linDamp);
		npReal getLinearDamping() const;

		void setAngularDamping(const npReal &_angDamp);
		npReal getAngularDamping() const;

		void setPosition(const npVector3r &_pos);
		npVector3r getPosition() const;

		void setVelocity(const npVector3r &_vel);
		npVector3r getVelocity() const;

		void setAcceleration(const npVector3r &_acc);
		npVector3r getAcceleration() const;

		void setRotation(const npVector3r &_rot);
		npVector3r getRotation() const;

		void setOrientation(const npQuarternion &_q);
		void setOrientation(const npReal & _r, const npReal &_i, const npReal &_j, const npReal &_k);
		npQuarternion getOrientation() const;

		#pragma endregion

		void integrate(npReal duration);

		void addForce(const npVector3r &force);

		void addForceAtPoint(const npVector3r &force, const npVector3r &point);

		void addForceAtBodyPoint(const npVector3r &force, const npVector3r &point);

		void setIntertiaTensor(const npMatrix3 &inertiaTensor);

		npVector3r getPointInLocalSpace(const npVector3r &point) const;

		npVector3r getPointInWorldSpace(const npVector3r &point) const;

		void calculateDerivedData();

		void clearAccum();

		bool isAwake() const;

		bool isAsleep() const;
	};

}
#endif