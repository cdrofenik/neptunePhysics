#include "collision/npRigidBody.h"

#include <math.h>

namespace NeptunePhysics
{

	static inline void _calculateTransformMatrix(npMatrix3x4& _transformMatrix, const npVector3& _pos,
		const npQuarternion& _orientation)
	{
		_transformMatrix.m[0] = 1 - (2 * _orientation.j * _orientation.j + 2 * _orientation.k * _orientation.k);
		_transformMatrix.m[1] = 2 * _orientation.i * _orientation.j + 2 * _orientation.k * _orientation.r;
		_transformMatrix.m[2] = 2 * _orientation.i * _orientation.k - 2 * _orientation.j * _orientation.r;
		_transformMatrix.m[3] = _pos.x;

		_transformMatrix.m[4] = 2 * _orientation.i * _orientation.j - 2 * _orientation.k * _orientation.r;
		_transformMatrix.m[5] = 1 - (2 * _orientation.i * _orientation.i + 2 * _orientation.k * _orientation.k);
		_transformMatrix.m[6] = 2 * _orientation.j * _orientation.k + 2 * _orientation.i * _orientation.r;
		_transformMatrix.m[7] = _pos.y;

		_transformMatrix.m[8] = 2 * _orientation.i * _orientation.k + 2 * _orientation.j * _orientation.r;
		_transformMatrix.m[9] = 2 * _orientation.j * _orientation.k - 2 * _orientation.i * _orientation.r;
		_transformMatrix.m[10] = 1 - (2 * _orientation.i * _orientation.i + 2 * _orientation.j * _orientation.j);
		_transformMatrix.m[11] = _pos.z;
	}

	static inline void _transformIntertiaTensor(npMatrix3& iitWorld, const npQuarternion& _q,
		const npMatrix3& iitBody, const npMatrix3x4& _rotMatrix)
	{
		npReal t4 = _rotMatrix.m[0] * iitBody.m[0] + _rotMatrix.m[1] * iitBody.m[3] +
			_rotMatrix.m[2] * iitBody.m[6];

		npReal t9 = _rotMatrix.m[0] * iitBody.m[1] + _rotMatrix.m[1] * iitBody.m[4] +
			_rotMatrix.m[2] * iitBody.m[7];

		npReal t14 = _rotMatrix.m[0] * iitBody.m[2] + _rotMatrix.m[1] * iitBody.m[5] +
			_rotMatrix.m[2] * iitBody.m[8];

		npReal t28 = _rotMatrix.m[4] * iitBody.m[0] + _rotMatrix.m[5] * iitBody.m[3] +
			_rotMatrix.m[6] * iitBody.m[6];

		npReal t33 = _rotMatrix.m[4] * iitBody.m[1] + _rotMatrix.m[5] * iitBody.m[4] +
			_rotMatrix.m[6] * iitBody.m[7];

		npReal t38 = _rotMatrix.m[4] * iitBody.m[2] + _rotMatrix.m[5] * iitBody.m[5] +
			_rotMatrix.m[6] * iitBody.m[8];

		npReal t52 = _rotMatrix.m[8] * iitBody.m[0] + _rotMatrix.m[9] * iitBody.m[3] +
			_rotMatrix.m[10] * iitBody.m[6];

		npReal t57 = _rotMatrix.m[8] * iitBody.m[1] + _rotMatrix.m[9] * iitBody.m[4] +
			_rotMatrix.m[10] * iitBody.m[7];

		npReal t62 = _rotMatrix.m[8] * iitBody.m[2] + _rotMatrix.m[9] * iitBody.m[5] +
			_rotMatrix.m[10] * iitBody.m[8];

		iitWorld.m[0] = t4 * _rotMatrix.m[0] + t9 * _rotMatrix.m[1] + t14 * _rotMatrix.m[2];
		iitWorld.m[1] = t4 * _rotMatrix.m[4] + t9 * _rotMatrix.m[5] + t14 * _rotMatrix.m[6];
		iitWorld.m[2] = t4 * _rotMatrix.m[8] + t9 * _rotMatrix.m[9] + t14 * _rotMatrix.m[10];
		iitWorld.m[3] = t28 * _rotMatrix.m[0] + t33 * _rotMatrix.m[1] + t38 * _rotMatrix.m[2];
		iitWorld.m[4] = t28 * _rotMatrix.m[4] + t33 * _rotMatrix.m[5] + t38 * _rotMatrix.m[6];
		iitWorld.m[5] = t28 * _rotMatrix.m[8] + t33 * _rotMatrix.m[9] + t38 * _rotMatrix.m[10];
		iitWorld.m[6] = t52 * _rotMatrix.m[0] + t57 * _rotMatrix.m[1] + t62 * _rotMatrix.m[2];
		iitWorld.m[7] = t52 * _rotMatrix.m[4] + t57 * _rotMatrix.m[5] + t62 * _rotMatrix.m[6];
		iitWorld.m[8] = t52 * _rotMatrix.m[8] + t57 * _rotMatrix.m[9] + t62 * _rotMatrix.m[10];
	}

	#pragma region Setters/Getters
	
	void npRigidBody::setInverseMass(const npReal& _imass)
	{
		m_inverseMass = _imass;
	}

	npReal npRigidBody::getInverseMass() const
	{
		return m_inverseMass;
	}

	void npRigidBody::setLinearDamping(const npReal& _linDamp)
	{
		m_linearDamping = _linDamp;
	}

	npReal npRigidBody::getLinearDamping() const
	{
		return m_linearDamping;
	}

	void npRigidBody::setAngularDamping(const npReal& _angDamp)
	{
		m_angularDamping = _angDamp;
	}

	npReal npRigidBody::getAngularDamping() const
	{
		return m_angularDamping;
	}

	void npRigidBody::setPosition(const npVector3& _pos)
	{
		m_position = _pos;
	}

	npVector3 npRigidBody::getPosition() const
	{
		return m_position;
	}

	void npRigidBody::setVelocity(const npVector3& _vel)
	{
		m_velocity = _vel;
	}

	npVector3 npRigidBody::getVelocity() const
	{
		return m_velocity;
	}

	void npRigidBody::setAcceleration(const npVector3& _acc)
	{
		m_acceleration = _acc;
	}

	npVector3 npRigidBody::getAcceleration() const
	{
		return m_acceleration;
	}

	void npRigidBody::setRotation(const npVector3& _rot)
	{
		m_rotation = _rot;
	}

	npVector3 npRigidBody::getRotation() const
	{
		return m_rotation;
	}

	void npRigidBody::setTransformMatrix(const npMatrix3x4& _matrix)
	{
		m_transformMatrix = _matrix;
	}

	npMatrix3x4 npRigidBody::getTransformMatrix() const
	{
		return m_transformMatrix;
	}
	#pragma endregion

	void npRigidBody::addForce(const npVector3& force)
	{
		m_forceAccum += force;
		m_isAwake = true;
	}

	void npRigidBody::addForceAtPoint(const npVector3& force, const npVector3& point)
	{
		npVector3 pt = point;
		pt -= m_position;

		m_forceAccum += force;
		m_torqueAccum += pt % force;

		m_isAwake = true;
	}

	void npRigidBody::addForceAtBodyPoint(const npVector3& force, const npVector3& point)
	{
		npVector3 pt = getPointInWorldSpace(point);
		addForceAtPoint(force, pt);

		m_isAwake = true;
	}

	void npRigidBody::setIntertiaTensor(const npMatrix3& inertiaTensor)
	{
		m_inverseInertiaTensor.setInverse(inertiaTensor);
	}

	void npRigidBody::calculateDerivedData()
	{
		m_orientation.normalize();

		_calculateTransformMatrix(m_transformMatrix, m_position, m_orientation);

		_transformIntertiaTensor(m_inverseInertiaTensor, m_orientation, m_inverseInertiaTensor,
			m_transformMatrix);
	}

	npVector3 npRigidBody::getPointInLocalSpace(const npVector3 &point) const
	{
		return m_transformMatrix.transformInverse(point);
	}

	npVector3 npRigidBody::getPointInWorldSpace(const npVector3 &point) const
	{
		return m_transformMatrix.transform(point);
	}

	void npRigidBody::integrate(npReal duration)
	{
		if (m_inverseMass <= 0.0f) return;

		m_lastFrameAcceleration = m_acceleration;
		m_lastFrameAcceleration.addScaledVector(m_forceAccum, m_inverseMass);

		npVector3 angularAcceleration = m_inverseInertiaTensorWorld.transform(m_torqueAccum);

		m_velocity.addScaledVector(m_lastFrameAcceleration, duration);
		m_rotation.addScaledVector(angularAcceleration, duration);

		m_velocity *= powf(m_linearDamping, duration);
		m_rotation *= powf(m_angularDamping, duration);

		m_position.addScaledVector(m_velocity, duration);
		m_orientation.addScaledVector(m_rotation, duration);

		calculateDerivedData();

		clearAccum();
	}

	void npRigidBody::clearAccum()
	{
		//m_forceAccum;
		//m_torqueAccum;
	}

	bool npRigidBody::isAwake() const
	{
		return m_isAwake;
	}

	bool npRigidBody::isAsleep() const
	{
		return m_canSleep;
	}
}