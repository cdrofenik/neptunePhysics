#ifndef NEPTUNE_NPCOLLISIONBODY_H
#define NEPTUNE_NPCOLLISIONBODY_H

#include "../Math/npMatrix3x4.hpp"
#include "CollisionShapes\npCollisionShape.h"

namespace NeptunePhysics {

	class npCollisionObject
	{
	public:
		npCollisionObject() {}
		~npCollisionObject() {}

		void setCollisionShape(npCollisionShape* _shape);
		npCollisionShape* getCollisionShape() const;

		void setWorldPositiong(npVector3r _position);
		npVector3r getWorldPosition() const;

		void setTransformMatrix(const npMatrix3x4 &_matrix);
		npMatrix3x4 getTransformMatrix() const;

	protected:
		npVector3r m_worldPosition;
		npMatrix3x4 m_transformMatrix;
		npCollisionShape* m_collisionShape;
	};
}
#endif