#include "Collision\npCollisionObject.h"

namespace NeptunePhysics
{
	void npCollisionObject::setCollisionShape(npCollisionShape* _shape)
	{
		m_collisionShape = _shape;
	}

	npCollisionShape* npCollisionObject::getCollisionShape() const
	{ 
		return m_collisionShape;
	}

	void npCollisionObject::setWorldPositiong(npVector3r _position)
	{
		m_worldPosition = _position;
	}

	npVector3r npCollisionObject::getWorldPosition() const 
	{ 
		return npVector3r(m_transformMatrix.m[3], m_transformMatrix.m[7], m_transformMatrix.m[11]);
	}

	void npCollisionObject::setTransformMatrix(const npMatrix3x4 &_matrix)
	{
		m_transformMatrix = _matrix;
	}

	npMatrix3x4 npCollisionObject::getTransformMatrix() const
	{
		return m_transformMatrix;
	}
}