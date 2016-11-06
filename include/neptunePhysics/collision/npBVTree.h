#ifndef NEPTUNE_NPBVTREE_H
#define NEPTUNE_NPBVTREE_H

#include "npAabb.h"
#include "collision/npRigidBody.h"
#include "collision/npDbvt.h"

namespace NeptunePhysics {

	class npBvNode
	{
	public:
		npBvNode(npBvNode* _parent,
			const npAabb &_boundingElement,
			npRigidBody* _body = NP_NULL);

		~npBvNode();

		npBvNode* m_left;
		npBvNode* m_right;
		npBvNode* m_parent;
		npAabb m_boundingVolume;

		bool isLeaf() const;
		void insert(npRigidBody* newBody, const npAabb &newVolume);

	private:
		npRigidBody* m_body;

		void recalculateBoundingVolume(bool recurse = true);
	};

}

#endif