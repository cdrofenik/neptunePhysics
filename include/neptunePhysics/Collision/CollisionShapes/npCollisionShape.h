#ifndef NEPTUNE_NPCOLLISIONSHAPE_H
#define NEPTUNE_NPCOLLISIONSHAPE_H

#include "math/npPrecision.hpp"
#include "math/npVector3.hpp"

namespace NeptunePhysics {

	enum npCollisionShapeType
	{
		BOX_SHAPE,
		SPHERE_SHAPE,
		CONVEX_SHAPE,
		PLANE_SHAPE
	};

	class npCollisionShape
	{
	public:
		npCollisionShape() : m_margin(0.0), m_scale(1.0), m_type(1) {}
		~npCollisionShape() {}

		void setMargin(const npReal &margin) { m_margin = margin; }
		npReal getMargin() const { return m_margin; }

		void setScale(const npReal &scale) { m_scale = scale; }
		npReal getScale() const { return m_scale; }

		void setType(const int &type) { m_type = type; }
		int getType() const { return m_type; }

		virtual void getAabb(npVector3r &aabbMin, npVector3r &aabbMax) const = 0;
		virtual void getBoundingSphere(npVector3r &center, npReal &radius) const {}

	protected:
		npReal m_margin;
		npReal m_scale;
		int m_type;
	};
}
#endif