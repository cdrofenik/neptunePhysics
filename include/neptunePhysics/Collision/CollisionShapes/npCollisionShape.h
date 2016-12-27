#ifndef NEPTUNE_NPCOLLISIONSHAPE_H
#define NEPTUNE_NPCOLLISIONSHAPE_H

#include "math/npPrecision.hpp"
#include "math/npVector3.hpp"

namespace NeptunePhysics {

	enum npBVType
	{
		AABB,
		bSphere
		//Particle
	};

	//class npBVInterface {

	//public:
	//	virtual npBVType getBvType() = 0;
	//};

	//class npBV : public npBVInterface {

	//public:
	//	npBV() {}
	//	~npBV() {}

	//	npBVType getBvType() { return type; }

	//private:
	//	npBVType type;
	//};

	//class npAABB : public npBV {

	//public:
	//	npVector3 c; // Center point
	//	npReal halfX, halfY, halfZ; // Halfway extents of AABB along each axis
	//	npBVType type = npBVType::AABB;
	//	npAABB() : c(0.0, 0, 0), halfX(0), halfY(0), halfZ(0) {}
	//	npAABB(npVector3& centerPoint, npReal half_x, npReal half_y, npReal half_z) : c(centerPoint),
	//		halfX(half_x), halfY(half_y), halfZ(half_z) {}
	//	~npAABB() {}
	//};

	//class npSphere : public npBV {

	//public:
	//	npVector3 c; // Center point
	//	npReal r; // Radius
	//	npBVType type = npBVType::bSphere;
	//	npSphere() : c(0.0, 0, 0), r(0) {}
	//	npSphere(npVector3& centerPoint, npReal radius) : c(centerPoint), r(radius) {}
	//	~npSphere() {}
	//};

}


#endif