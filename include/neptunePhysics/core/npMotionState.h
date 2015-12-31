#ifndef NEPTUNE_NPMOTIONSTATE_H
#define NEPTUNE_NPMOTIONSTATE_H

#include "math/npMatrix4.hpp"

namespace NeptunePhysics
{
	class npMotionState
	{
	public:
		npMotionState(npMatrix4 _startingState) : m_stateMarix(_startingState) {}
		~npMotionState() {}

		npMatrix4 GetStateMatrix4() { return m_stateMarix; }

		npVector3 GetPosition() { return npVector3(m_stateMarix.m[0][3], m_stateMarix.m[1][3], m_stateMarix.m[2][3]); }

		void ChangePosition(npVector3 _newPosition)
		{
			m_stateMarix.m[0][3] = _newPosition.x;
			m_stateMarix.m[1][3] = _newPosition.y;
			m_stateMarix.m[2][3] = _newPosition.z;
		}

	private:
		npMatrix4 m_stateMarix;
	};
}

#endif