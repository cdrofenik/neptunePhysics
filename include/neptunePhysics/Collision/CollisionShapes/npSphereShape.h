#ifndef NAPTUNE_NPSPHERESHAPE_H
#define NAPTUNE_NPSPHERESHAPE_H

#include "Math/npVector3.hpp"

#include "npCollisionShape.h"

namespace NeptunePhysics
{
	class npSphereShape : public npCollisionShape
	{
	public:
		npSphereShape() : m_center(npVector3r()), m_radius(0.0) {}
		npSphereShape(const npVector3r &centerPoint, const npReal &radius) :
			m_center(centerPoint),
			m_radius(radius)
		{
			setType(npCollisionShapeType::SPHERE_SHAPE);
		}
		npSphereShape(const npVector3r &centerPoint, const npVector3r &halfSize) :
			m_center(centerPoint)
		{
			setType(npCollisionShapeType::SPHERE_SHAPE);

			if (halfSize.x > halfSize.y)
				if (halfSize.x > halfSize.z)
					m_radius = halfSize.x;
				else
					m_radius = halfSize.z;
			else
				if (halfSize.y > halfSize.z)
					m_radius = halfSize.y;
				else
					m_radius = halfSize.z;
		}

		~npSphereShape();

		virtual void getAabb(npVector3r &aabbMin, npVector3r &aabbMax) const {}

		void getBoundingSphere(npVector3r &center, npReal &radius) const
		{
			center = m_center;
			radius = m_radius;
		}

		npReal getRadius() const { return m_radius; }

	private:
		npVector3r m_center;
		npReal m_radius;
	};
}

#endif