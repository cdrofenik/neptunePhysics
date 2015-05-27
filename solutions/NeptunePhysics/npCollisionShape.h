#ifndef NEPTUNE_NPCOLLISIONSHAPE_H
#define NEPTUNE_NPCOLLISIONSHAPE_H

#include "npPrecision.h"
#include "npVector.h"

namespace neptunePhysics {

	enum npCollisionShapeType
	{
		AABB,
		Sphere,
		Particle
	};

	class npCollisionShape {
		npCollisionShapeType type;
	};

	class npAABB : npCollisionShape {

	public:
		npVector3 c; // Center point
		npReal halfX, halfY, halfZ; // Halfway extents of AABB along each axis
		npCollisionShapeType type = npCollisionShapeType::AABB;
		npAABB() : c(0.0, 0, 0), halfX(0), halfY(0), halfZ(0) {}
		npAABB(npVector3& centerPoint, npReal half_x, npReal half_y, npReal half_z) : c(centerPoint),
			halfX(half_x), halfY(half_y), halfZ(half_z) {}
	};

	class npSphere : npCollisionShape {

	public:
		npVector3 c; // Center point
		npReal r; // Radius
		npCollisionShapeType type = npCollisionShapeType::Sphere;
		npSphere() : c(0.0, 0, 0), r(0) {}
		npSphere(npVector3& centerPoint, npReal radius) : c(centerPoint), r(radius) {}
	};

	class npParticle : npCollisionShape {

	public:
		npVector3 pos;
		npReal size;
		npCollisionShapeType type = npCollisionShapeType::Particle;
		npParticle() : pos(0.0, 0, 0), size(0) {}
		npParticle(npVector3& centerPoint, npReal radius) : pos(centerPoint), size(radius) {}
	};
}


#endif