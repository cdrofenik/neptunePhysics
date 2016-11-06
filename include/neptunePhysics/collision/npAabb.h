#ifndef NEPTUNE_NPAABB_H
#define NEPTUNE_NPAABB_H

#include "math/npVector3.hpp"

namespace NeptunePhysics {

	struct npAabb {

	public:
		//float m_min[3];
		npVector3 m_minVec;

		//float m_max[3];
		npVector3 m_maxVec;

		npAabb() {
			m_minVec = npVector3(0, 0, 0);
			m_maxVec = npVector3(0, 0, 0);
		}

		npAabb(const npVector3 &minValues, const npVector3 &maxValues) : m_minVec(minValues),
			m_maxVec(maxValues) {}

		npReal getSize() const {
			return (m_maxVec.x - m_minVec.x) * (m_maxVec.y - m_minVec.y) * (m_maxVec.z - m_minVec.z);
		}

		bool contains(const npAabb& volume) const {
			return (m_minVec.x < volume.m_minVec.x &&
				m_minVec.y < volume.m_minVec.y &&
				m_minVec.z < volume.m_minVec.z &&
				m_maxVec.x > volume.m_maxVec.x &&
				m_maxVec.y > volume.m_maxVec.y &&
				m_maxVec.z > volume.m_maxVec.z);
		}

		bool isEqual(const npAabb& volume) const {
			return (m_minVec.x == volume.m_minVec.x &&
				m_minVec.y == volume.m_minVec.y &&
				m_minVec.z == volume.m_minVec.z &&
				m_maxVec.x == volume.m_maxVec.x &&
				m_maxVec.y == volume.m_maxVec.y &&
				m_maxVec.z == volume.m_maxVec.z);
		}
	};

	struct npAabbUpdateData
	{
		npAabb originalAabb;
		npVector3 directionDiff;

		npAabbUpdateData(npAabb a, npVector3 b) :
			originalAabb(a),
			directionDiff(b) {}
	};

	inline bool npTestAabbAabb(const npAabb& first, const npAabb& second)
	{
		bool overlap = true;
		overlap = (first.m_minVec.x > second.m_maxVec.x || first.m_maxVec.x < second.m_minVec.x) ? false : overlap;
		overlap = (first.m_minVec.z > second.m_maxVec.z || first.m_maxVec.z < second.m_minVec.z) ? false : overlap;
		overlap = (first.m_minVec.y > second.m_maxVec.y || first.m_maxVec.y < second.m_minVec.y) ? false : overlap;
		return overlap;
	}

	__forceinline void npMergeAabbAabb(const npAabb& first, const npAabb& second, npAabb& result)
	{
		result.m_minVec.x = (first.m_minVec.x < second.m_minVec.x) ? first.m_minVec.x : second.m_minVec.x;
		result.m_minVec.y = (first.m_minVec.y < second.m_minVec.y) ? first.m_minVec.y : second.m_minVec.y;
		result.m_minVec.z = (first.m_minVec.z < second.m_minVec.z) ? first.m_minVec.z : second.m_minVec.z;

		result.m_maxVec.x = (first.m_maxVec.x > second.m_maxVec.x) ? first.m_maxVec.x : second.m_maxVec.x;
		result.m_maxVec.y = (first.m_maxVec.y > second.m_maxVec.y) ? first.m_maxVec.y : second.m_maxVec.y;
		result.m_maxVec.z = (first.m_maxVec.z > second.m_maxVec.z) ? first.m_maxVec.z : second.m_maxVec.z;
	}

	__forceinline npReal npChangeInSurfaceAabbAabb(const npAabb& original, const npAabb& newElement)
	{
		npAabb newElementCopy;
		npMergeAabbAabb(original, newElement, newElementCopy);

		return newElementCopy.getSize() - original.getSize();
	}

	__forceinline npReal npProximityAabbAabb(const npAabb& a, const npAabb& b)
	{
		npVector3 d = (a.m_minVec + a.m_maxVec) - (b.m_minVec + b.m_maxVec);
		return fabsf(d.x) + fabsf(d.y) + fabsf(d.z);
	}
}

#endif