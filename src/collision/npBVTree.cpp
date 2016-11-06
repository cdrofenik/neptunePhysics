#include "collision\npBVTree.h"

namespace NeptunePhysics {

	npBvNode::npBvNode(npBvNode* _parent,
		const npAabb &_boundingElement,
		npRigidBody* _body) :
		m_parent(_parent),
		m_boundingVolume(_boundingElement),
		m_body(_body)
	{
		m_left = m_right = NP_NULL;
	}

	npBvNode::~npBvNode()
	{
		if (m_parent)
		{
			npBVTree* sibling;
			//Check for sibling
			if (m_parent->m_right != NP_NULL && m_parent->m_left == this)
			{
				sibling = m_parent->m_right;
			}
			else sibling = m_parent->m_left;

			//Transfer sibling values to parent
			m_parent->m_boundingVolume = sibling->m_boundingVolume;
			m_parent->m_body = sibling->m_body;
			m_parent->m_left = sibling->m_left;
			m_parent->m_right = sibling->m_right;

			//Remove sibling
			sibling->m_parent = NP_NULL;
			sibling->m_body = NP_NULL;
			sibling->m_left = NP_NULL;
			sibling->m_right = NP_NULL;
			delete sibling;

			//Recalculate parent's bounding volume
			m_parent->recalculateBoundingVolume();
		}

		//Remove children and parent data for them
		if (m_left) {
			m_left->m_parent = NP_NULL;
			delete m_left;
		}
		if (m_right) {
			m_right->m_parent = NP_NULL;
			delete m_right;
		}

		//TODO - delete m_body?
	}

	bool npBvNode::isLeaf() const
	{
		return (m_body != NP_NULL);
	}

	void npBvNode::insert(npRigidBody* newBody, const npAabb &newVolume)
	{
		if (isLeaf())
		{
			//TODO check on which side it fits best
			m_left = new npBVTree(this, m_boundingVolume, m_body); //body of tree get's copied into left child
			m_right = new npBVTree(this, newVolume, newBody); //new tree is now the right child
			this->m_body = NP_NULL; //not leaf anymore

			recalculateBoundingVolume();
		}
		else //not leaf -> check to which child it fits
		{
			if (npChangeInSurfaceAabbAabb(m_left->m_boundingVolume, newVolume) <
				npChangeInSurfaceAabbAabb(m_right->m_boundingVolume, newVolume))
			{
				m_left->insert(newBody, newVolume);
			}
			else
			{
				m_right->insert(newBody, newVolume);
			}
		}
	}

	void npBvNode::recalculateBoundingVolume(bool recurse /* = true */)
	{
		if (isLeaf()) return;

		//Combine two bounding volumes
		m_boundingVolume = npCombineAabbAabb(
			m_left->m_boundingVolume,
			m_right->m_boundingVolume
			);

		// Recurse up the tree
		if (m_parent) m_parent->recalculateBoundingVolume(true);
	}

	
}