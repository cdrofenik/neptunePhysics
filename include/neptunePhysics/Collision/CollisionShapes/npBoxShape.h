#ifndef NEPTUNE_NPBOXSHAPE_H
#define NEPTUNE_NPBOXSHAPE_H

#include "Math/npVector3.hpp"

#include "npCollisionShape.h"

namespace NeptunePhysics
{
	class npBoxShape : public npCollisionShape
	{
	public:
		npVector3r center;
		npVector3r halfSize;

		npBoxShape() : center(npVector3r()), halfSize(npVector3r()) {}
		npBoxShape(const npVector3r &centerPoint, const npVector3r &halfSpaces) :
			center(centerPoint),
			halfSize(halfSpaces)
		{
			setType(npCollisionShapeType::BOX_SHAPE);
		}
		~npBoxShape() {}

		virtual void getAabb(npVector3r &aabbMin, npVector3r &aabbMax) const
		{
			aabbMin = center - halfSize;
			aabbMax = center + halfSize;
		}

		//Calculates closest point on AABB box
		void closestPoint(const npVector3r &_point, npVector3r &_closestPoint) const
		{
			for (size_t i = 0; i < 3; i++)
			{
				npReal value = _point.getValue(i);
				if (value < -halfSize.getValue(i))
					value = -halfSize.getValue(i);
				if (value > halfSize.getValue(i))
					value = halfSize.getValue(i);
				_closestPoint.setValue(i, value);
			}
		}
	};
}

#endif