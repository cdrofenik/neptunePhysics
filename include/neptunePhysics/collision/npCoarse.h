#ifndef NEPTUNE_BVNODE_H
#define NEPTUNE_BVNODE_H

#include "collision/npRigidBody.h"
#include "collision/npContact.h"
#include "npAabb.h"

namespace NeptunePhysics {

	class npBVHNode_AABB
	{
	public:
		npBVHNode_AABB(npBVHNode_AABB* parent,
			const npAabb &boundingElement,
			npRigidBody* body = NP_NULL);
		~npBVHNode_AABB();

		npRigidBody* m_body;
		npBVHNode_AABB* m_children[2];
		npAabb m_boundingElement;

		bool isLeaf() const;

		unsigned getPotentialContacts(npPotentialContact* contacts,
			unsigned limit) const;

		void insert(npRigidBody* body, const npAabb &volume);

	private:
		npBVHNode_AABB* m_parent;

		bool overlaps(const npBVHNode_AABB *other) const;

		unsigned getPotentialContactsWith(const npBVHNode_AABB *other,
			npPotentialContact* contacts,
			unsigned limit) const;

		void recalculateBoundingVolume(bool recurse = true);
	};

}

#endif