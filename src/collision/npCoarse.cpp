#include "collision/npCoarse.h"

namespace NeptunePhysics {

	npBVHNode_AABB::npBVHNode_AABB(npBVHNode_AABB* parent, const npAabb &boundingElement,
		npRigidBody* body /* = 0 */) : m_parent(parent), m_boundingElement(boundingElement), m_body(body)
	{
		m_children[0] = m_children[1] = NP_NULL;
	}
	
	npBVHNode_AABB::~npBVHNode_AABB()
	{
		// If we don't have a parent, then we ignore the sibling
		// processing
		if (m_parent)
		{
			// Find our sibling
			npBVHNode_AABB *sibling;
			if (m_parent->m_children[0] == this) sibling = m_parent->m_children[1];
			else sibling = m_parent->m_children[0];

			// Write its data to our parent
			m_parent->m_boundingElement = sibling->m_boundingElement;
			m_parent->m_body = sibling->m_body;
			m_parent->m_children[0] = sibling->m_children[0];
			m_parent->m_children[1] = sibling->m_children[1];

			// Delete the sibling (we blank its parent and
			// children to avoid processing/deleting them)
			sibling->m_parent = NP_NULL;
			sibling->m_body = NP_NULL;
			sibling->m_children[0] = NP_NULL;
			sibling->m_children[1] = NP_NULL;
			delete sibling;

			// Recalculate the parent's bounding volume
			m_parent->recalculateBoundingVolume();
		}

		// Delete our children (again we remove their
		// parent data so we don't try to process their siblings
		// as they are deleted).
		if (m_children[0]) {
			m_children[0]->m_parent = NP_NULL;
			delete m_children[0];
		}
		if (m_children[1]) {
			m_children[1]->m_parent = NP_NULL;
			delete m_children[1];
		}
	}

	bool npBVHNode_AABB::isLeaf() const
	{
		return (m_body != NP_NULL);
	}

	unsigned npBVHNode_AABB::getPotentialContacts(npPotentialContact* contacts, unsigned limit) const
	{
		if (isLeaf() || limit == 0) return 0;

		return m_children[0]->getPotentialContactsWith(m_children[1], contacts, limit);
	}

	void npBVHNode_AABB::insert(npRigidBody* newBody, const npAabb &newVolume)
	{
		//If this node is leaf, spawn two children and place new body in one
		if (isLeaf())
		{
			m_children[0] = new npBVHNode_AABB(this, m_boundingElement, m_body); //body of node get's copied into first child

			m_children[1] = new npBVHNode_AABB(this, newVolume, newBody); //new body is now the second child

			this->m_body = NP_NULL; //not leaf anymore

			recalculateBoundingVolume(); //Recalculate bounding volume
		}
		else //If it's not a leaf we have to assign it to the right child
		{
			if (npChangeInSurfaceAabbAabb(m_children[0]->m_boundingElement, newVolume) <
				npChangeInSurfaceAabbAabb(m_children[1]->m_boundingElement, newVolume))
			{
				m_children[0]->insert(newBody, newVolume);
			}
			else
			{
				m_children[1]->insert(newBody, newVolume);
			}
		}
	}

	bool npBVHNode_AABB::overlaps(const npBVHNode_AABB *other) const
	{
		return npTestAabbAabb(m_boundingElement, other->m_boundingElement);
	}

	unsigned npBVHNode_AABB::getPotentialContactsWith(const npBVHNode_AABB *other,
		npPotentialContact* contacts,
		unsigned limit) const
	{
		//doesn't overlap or no limit
		if (!overlaps(other) || limit == 0) return 0;

		// if both at leaf nodes then this is a potential contact
		if (isLeaf() && other->isLeaf())
		{
			contacts->body[0] = m_body;
			contacts->body[1] = other->m_body;
			return 1;
		}

		// Determine which node to descend into. If either is
		// a leaf, then we descend the other. If both are branches,
		// then we use the one with the largest size.
		if (other->isLeaf() || (!isLeaf() && m_boundingElement.getSize() >= other->m_boundingElement.getSize()))
		{
			// Recurse into ourself
			unsigned count = m_children[0]->getPotentialContactsWith(other, contacts, limit);

			// Check we have enough slots to do the other side too
			if (limit > count) {
				return count + m_children[1]->getPotentialContactsWith(other, contacts + count, limit - count);
			}
			else {
				return count;
			}
		}
		else
		{
			// Recurse into the other node
			unsigned count = getPotentialContactsWith(other->m_children[0], contacts, limit);

			// Check we have enough slots to do the other side too
			if (limit > count) {
				return count + getPotentialContactsWith(other->m_children[1], contacts + count, limit - count);
			}
			else {
				return count;
			}
		}
	}

	void npBVHNode_AABB::recalculateBoundingVolume(bool recurse /* = true */)
	{
		if (isLeaf()) return;

		//Combine two bounding volumes
		/*m_boundingElement = npExpandAabbAabb(
			m_children[0]->m_boundingElement,
			m_children[1]->m_boundingElement
			);*/

		// Recurse up the tree
		if (m_parent) m_parent->recalculateBoundingVolume(true);
	}
}

