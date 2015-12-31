#ifndef NEPTUNE_NPRIGIDBODY_H
#define NEPTUNE_NPRIGIDBODY_H

#include "npCollisionShape.h"

#include "core/npMotionState.h"

namespace NeptunePhysics {

	class npRigidBody
	{
	public:
		npRigidBody(unsigned int _meshId, float _mass, npBV _boundVol, npMotionState _motState) :
			m_id(_meshId),
			m_mass(_mass),
			m_boundingVolume(_boundVol),
			m_motionState(_motState) {}

		~npRigidBody() {}

		float getMass() const { return m_mass; }
		npBV getBoundingVolume() const { return m_boundingVolume; }
		npMotionState getMotionState() const { return m_motionState; }

		npVector3 getPosition() { return m_motionState.GetPosition(); }
		void setNewPosition(const npVector3& _newPosition) { m_motionState.ChangePosition(_newPosition); }

		//void SetMotionsState(const npMotionState& _monState) { m_motionState = _monState; }

	private:
		unsigned int m_id;
		float m_mass;
		npBV m_boundingVolume;
		npMotionState m_motionState;
	};

}
#endif