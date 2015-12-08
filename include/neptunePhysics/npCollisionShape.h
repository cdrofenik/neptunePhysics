#ifndef NEPTUNE_NPCOLLISIONSHAPE_H
#define NEPTUNE_NPCOLLISIONSHAPE_H

#include "npPrecision.h"
#include "npVector.h"

namespace NeptunePhysics {

	enum npBoundingVolumeType
	{
		AABB,
		Sphere,
		Particle
	};

	class npBoundingVolume {
		npBoundingVolumeType type;
	};

	class npAABB : npBoundingVolume {

	public:
		npVector3<npReal> c; // Center point
		npReal halfX, halfY, halfZ; // Halfway extents of AABB along each axis
		npBoundingVolumeType type = npBoundingVolumeType::AABB;
		npAABB() : c(0.0, 0, 0), halfX(0), halfY(0), halfZ(0) {}
		npAABB(npVector3<npReal>& centerPoint, npReal half_x, npReal half_y, npReal half_z) : c(centerPoint),
			halfX(half_x), halfY(half_y), halfZ(half_z) {}
	};

	class npSphere : npBoundingVolume {

	public:
		npVector3<npReal> c; // Center point
		npReal r; // Radius
		npBoundingVolumeType type = npBoundingVolumeType::Sphere;
		npSphere() : c(0.0, 0, 0), r(0) {}
		npSphere(npVector3<npReal>& centerPoint, npReal radius) : c(centerPoint), r(radius) {}
	};

	class npParticle : npBoundingVolume {

	public:
		npVector3<npReal> pos;
		npReal size;
		npBoundingVolumeType type = npBoundingVolumeType::Particle;
		npParticle() : pos(0.0, 0, 0), size(0) {}
		npParticle(npVector3<npReal>& centerPoint, npReal radius) : pos(centerPoint), size(radius) {}
	};
}


#endif