#ifndef NEPTUNE_NPRIGIDBODY_H
#define NEPTUNE_NPRIGIDBODY_H

#include "math/npMatrix3x4.h"

#include "core/npMotionState.h"

namespace NeptunePhysics {

	class npRigidBody
	{
	public:
		npRigidBody(const float& _mass, const npVector3& _position,
			const npVector3& _velocity, const npVector3& _acceleration) :
			m_inverseMass(_mass),
			m_position(_position),
			m_velocity(_velocity),
			m_acceleration(_acceleration) {}

		~npRigidBody() {}

	protected:
		npReal m_inverseMass;
		npReal m_linearDamping;
		npReal m_angularDamping;

		npVector3 m_position;
		npVector3 m_velocity;
		npVector3 m_acceleration;

		npVector3 m_rotation;
		npQuarternion m_orientation;
		npMatrix3x4 m_transformMatrix;

		npMatrix3 m_inverseInertiaTensor;
		npMatrix3 m_inverseInertiaTensorWorld;

		npVector3 m_forceAccum;
		npVector3 m_torqueAccum;

		npVector3 m_lastFrameAcceleration;

		bool m_isAwake;
		bool m_canSleep;

	public:
		#pragma region Setters/Getters

		void setInverseMass(const npReal& _imass);
		npReal getInverseMass() const;

		void setLinearDamping(const npReal& _linDamp);
		npReal getLinearDamping() const;

		void setAngularDamping(const npReal& _angDamp);
		npReal getAngularDamping() const;

		void setPosition(const npVector3& _pos);
		npVector3 getPosition() const;

		void setVelocity(const npVector3& _vel);
		npVector3 getVelocity() const;

		void setAcceleration(const npVector3& _acc);
		npVector3 getAcceleration() const;

		void setRotation(const npVector3& _rot);
		npVector3 getRotation() const;

		void setOrientation(const npQuarternion& _q);
		void setOrientation(const npReal& _r, const npReal& _i, const npReal& _j, const npReal& _k);
		npQuarternion getOrientation() const;

		void setTransformMatrix(const npMatrix3x4& _rot);
		npMatrix3x4 getTransformMatrix() const;

		#pragma endregion

		void integrate(npReal duration);

		void addForce(const npVector3& force);

		void addForceAtPoint(const npVector3& force, const npVector3& point);

		void addForceAtBodyPoint(const npVector3& force, const npVector3& point);

		void setIntertiaTensor(const npMatrix3& inertiaTensor);

		npVector3 getPointInLocalSpace(const npVector3 &point) const;

		npVector3 getPointInWorldSpace(const npVector3 &point) const;

		void calculateDerivedData();

		void clearAccum();

		bool isAwake() const;

		bool isAsleep() const;
	};

}
#endif