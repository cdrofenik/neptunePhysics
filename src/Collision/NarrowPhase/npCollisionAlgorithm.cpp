#include "Collision/NarrowPhase/npCollisionAlgorithm.h"

#include "Collision/CollisionShapes/npBoxShape.h"
#include "Collision/CollisionShapes/npSphereShape.h"

namespace NeptunePhysics
{
	static void setUpCollisionData(
		const npVector3r &normal,
		const npVector3r &contactPoint,
		const npReal &depth,
		npCollisionInfo &_cInfo)
	{
		_cInfo.contactNormal = normal;
		_cInfo.contactPoint = contactPoint;
		_cInfo.penetration = depth;
	}

	static inline npVector3r contactPoint(
		const npVector3r &pOne,
		const npVector3r &dOne,
		npReal oneSize,
		const npVector3r &pTwo,
		const npVector3r &dTwo,
		npReal twoSize,

		// If this is true, and the contact point is outside
		// the edge (in the case of an edge-face contact) then
		// we use one's midpoint, otherwise we use two's.
		bool useOne)
	{
		npVector3r toSt, cOne, cTwo;
		npReal dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
		npReal denom, mua, mub;

		smOne = dOne.squareLength();
		smTwo = dTwo.squareLength();
		dpOneTwo = dTwo * dOne;

		toSt = pOne - pTwo;
		dpStaOne = dOne * toSt;
		dpStaTwo = dTwo * toSt;

		denom = smOne * smTwo - dpOneTwo * dpOneTwo;

		// Zero denominator indicates parrallel lines
		if (fabs(denom) < 0.0001f) {
			return useOne ? pOne : pTwo;
		}

		mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
		mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

		// If either of the edges has the nearest point out
		// of bounds, then the edges aren't crossed, we have
		// an edge-face contact. Our point is on the edge, which
		// we know from the useOne parameter.
		if (mua > oneSize ||
			mua < -oneSize ||
			mub > twoSize ||
			mub < -twoSize)
		{
			return useOne ? pOne : pTwo;
		}
		else
		{
			cOne = pOne + dOne * mua;
			cTwo = pTwo + dTwo * mub;

			return cOne * 0.5 + cTwo * 0.5;
		}
	}

	static inline npReal transformToAxis(
		const npCollisionObject* cObject,
		const npVector3r &axis
		)
	{
		const npBoxShape* box = (npBoxShape*)cObject->getCollisionShape();

		return box->halfSize.x * fabs(axis * cObject->getTransformMatrix().getAxisValues(0)) +
			box->halfSize.y * fabs(axis * cObject->getTransformMatrix().getAxisValues(1)) +
			box->halfSize.z * fabs(axis * cObject->getTransformMatrix().getAxisValues(2));
	}

	static int processEdgeEdge(const npCollisionObject* obj0,
		const npCollisionObject* obj1,
		npVector3r &toCenter,
		const npReal &penetration,
		const int &bestAxis,
		npCollisionInfo &_cInfo)
	{
		int resultingAxis = bestAxis - 6;
		unsigned oneAxisIndex = resultingAxis / 3;
		unsigned twoAxisIndex = resultingAxis % 3;
		npVector3r oneAxis = obj0->getTransformMatrix().getAxisValues(oneAxisIndex);
		npVector3r twoAxis = obj1->getTransformMatrix().getAxisValues(twoAxisIndex);
		npVector3r axis = oneAxis % twoAxis;
		axis.normalize();

		// The axis should point from box one to box two.
		if (axis * toCenter > 0) axis = axis * -1.0f;

		// We have the axes, but not the edges: each axis has 4 edges parallel
		// to it, we need to find which of the 4 for each object. We do
		// that by finding the point in the centre of the edge. We know
		// its component in the direction of the box's collision axis is zero
		// (its a mid-point) and we determine which of the extremes in each
		// of the other axes is closest.

		const npBoxShape* box0 = (npBoxShape*)obj0->getCollisionShape();
		const npBoxShape* box1 = (npBoxShape*)obj1->getCollisionShape();
		npVector3r ptOnOneEdge = box0->halfSize;
		npVector3r ptOnTwoEdge = box1->halfSize;
		for (unsigned i = 0; i < 3; i++)
		{
			if (i == oneAxisIndex)
				ptOnOneEdge.setValue(i, 0);
			else if (obj0->getTransformMatrix().getAxisValues(i) * axis > 0)
				ptOnOneEdge.setValue(i, -ptOnOneEdge.getValue(i));

			if (i == twoAxisIndex)
				ptOnTwoEdge.setValue(i, 0);
			else if (obj1->getTransformMatrix().getAxisValues(i) * axis < 0)
				ptOnTwoEdge.setValue(i, -ptOnTwoEdge.getValue(i));
		}

		// Move them into world coordinates (they are already oriented
		// correctly, since they have been derived from the axes).
		ptOnOneEdge = obj0->getTransformMatrix() * ptOnOneEdge;
		ptOnTwoEdge = obj1->getTransformMatrix() * ptOnTwoEdge;

		// So we have a point and a direction for the colliding edges.
		// We need to find out point of closest approach of the two
		// line-segments.
		npVector3r vertex = contactPoint(
			ptOnOneEdge, oneAxis, box0->halfSize.getValue(oneAxisIndex),
			ptOnTwoEdge, twoAxis, box1->halfSize.getValue(oneAxisIndex),
			bestAxis > 2
			);

		setUpCollisionData(axis, vertex, penetration, _cInfo);
	}

	static int processFaceFace(const npCollisionObject* obj0,
		const npCollisionObject* obj1,
		npVector3r &toCenter,
		const npReal &penetration,
		const int &bestAxis,
		npCollisionInfo &_cInfo)
	{
		npVector3r normal = obj0->getTransformMatrix().getAxisValues(bestAxis);
		if (obj0->getTransformMatrix().getAxisValues(bestAxis) * toCenter > 0)
		{
			normal = normal * -1.0f;
		}

		const npBoxShape* box2 = (npBoxShape*)obj1->getCollisionShape();
		npVector3r vertex = box2->halfSize;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.x = -vertex.x;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.y = -vertex.y;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.z = -vertex.z;

		setUpCollisionData(normal, vertex, penetration, _cInfo);
		return 1;
	}

	static bool SeparatingAxisTest(const npCollisionObject* obj0,
		const npCollisionObject* obj1,
		npVector3r &axis,
		npVector3r &toCenter,
		unsigned int testId,
		npReal &smallestPenetration,
		unsigned int &result)
	{
		// Project this onto the axis
		npReal distance = fabs(toCenter * axis);

		// Check projection distance
		npReal projectionDistance = transformToAxis(obj0, axis) + transformToAxis(obj1, axis) - distance;
		
		if (projectionDistance < 0)
			return false;
		if (projectionDistance < smallestPenetration) {
			smallestPenetration = projectionDistance;
			result = testId;
		}
		return true;
	}

	//preprocessor definition used to shorten function call to SeparatingAxisTest
	#define SEPARATING_AXIS_TEST(axis, index) \
		SeparatingAxisTest(obj0, obj1, (axis), toCenter, (index), penetration, bestTestId)

	#define MERGE_AXIS_VALUES(index0, index1) \
		obj0->getTransformMatrix().getAxisValues(index0) % obj0->getTransformMatrix().getAxisValues(index1)

	static int BoxBoxGenerateContacts(npCollisionObject* obj0, npCollisionObject* obj1, npCollisionInfo &_cInfo)
	{
		npVector3r toCenter = obj0->getWorldPosition() - obj1->getWorldPosition();
		const npBoxShape* box0 = (npBoxShape*)obj0->getCollisionShape();
		const npBoxShape* box1 = (npBoxShape*)obj1->getCollisionShape();

		npReal penetration = NP_REAL_MAX;
		unsigned int bestTestId = -1;

		//Check 15 axes 
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(0), 0) &&
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(1), 1) &&
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(2), 2) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(0), 3) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(1), 4) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(2), 5);

		npReal smallestPenetration = penetration;

		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 0), 6) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 1), 7) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 2), 8) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 0), 9) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 1), 10) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 2), 11) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 0), 12) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 1), 13) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 2), 14);

		if (bestTestId < 0)
			return 0;
		if (bestTestId < 6)
		{
			return processFaceFace(
				bestTestId < 3 ? obj0 : obj1,
				bestTestId < 3 ? obj1 : obj0,
				bestTestId < 3 ? toCenter : toCenter*-1.0f,
				penetration,
				bestTestId < 3 ? bestTestId : bestTestId - 3,
				_cInfo);
		}
		else
		{
			return processFaceFace(obj0, obj1, toCenter, smallestPenetration, bestTestId, _cInfo);
		}
	}

	static int SphereBoxGenerateContacts(npCollisionObject* obj0, npCollisionObject* obj1, npCollisionInfo &_cInfo)
	{
		const npSphereShape* sphere = (npSphereShape*)obj0->getCollisionShape();
		const npBoxShape* box = (npBoxShape*)obj1->getCollisionShape();

		npVector3r sphereCenter = obj0->getWorldPosition();
		npVector3r relCenter = obj1->getTransformMatrix().transformInverse(sphereCenter);
		
		npVector3r closestPoint;
		box->closestPoint(relCenter, closestPoint);

		// Check collision
		npReal distance = (closestPoint - relCenter).squareLength();
		if (distance > (sphere->getRadius() * sphere->getRadius()))
			return 0;

		npVector3r closesPntWorldPos = obj1->getTransformMatrix().transform(closestPoint);

		setUpCollisionData((closesPntWorldPos - sphereCenter).normalize(),
			closesPntWorldPos,
			sphere->getRadius() - (closestPoint - relCenter).length(),
			_cInfo);
		return 1;
	}

	static int SphereSphereGenerateContacts(npCollisionObject* obj0, npCollisionObject* obj1, npCollisionInfo &_cInfo)
	{
		const npSphereShape* sphere0 = (npSphereShape*)obj0->getCollisionShape();
		const npSphereShape* sphere1 = (npSphereShape*)obj1->getCollisionShape();

		npVector3r distanceVector = obj0->getWorldPosition() - obj1->getWorldPosition();
		npReal distance = distanceVector.length();

		if (distance <= 0.0f || distance >= (sphere0->getRadius() + sphere1->getRadius()))
			return 0;

		npVector3r normal = distanceVector * (((npReal)1.0) / distance);
		setUpCollisionData(normal,
			obj0->getWorldPosition() + distanceVector * (npReal)0.5,
			sphere0->getRadius() + sphere1->getRadius() - distance,
			_cInfo);
		return 1;
	}

	int npCollisionAlgorithm::processCollision(npCollisionObject* obj0, npCollisionObject* obj1, npCollisionInfo &_cInfo)
	{
		if (obj0->getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE &&
			obj1->getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE)
		{
			return BoxBoxGenerateContacts(obj0, obj1, _cInfo);
		}

		if ((obj0->getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE &&
			obj1->getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE) ||
			(obj0->getCollisionShape()->getType() == npCollisionShapeType::BOX_SHAPE &&
			obj1->getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE))
		{
			if (obj1->getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE)
				return SphereBoxGenerateContacts(obj1, obj0, _cInfo);
			else
				return SphereBoxGenerateContacts(obj0, obj1, _cInfo);
		}

		if (obj0->getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE &&
			obj1->getCollisionShape()->getType() == npCollisionShapeType::SPHERE_SHAPE)
		{
			return SphereSphereGenerateContacts(obj0, obj1, _cInfo);
		}

		return 0;
	}
}