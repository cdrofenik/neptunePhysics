#ifndef NEPTUNE_BVNODE_H
#define NEPTUNE_BVNODE_H

#include "npContact.h"
#include "npCollisionShape.h"
#include "npCollisionBody.h"

namespace NeptunePhysics {

	template<npBoundingVolume>
	class npBVHNode {

	//Members
	public:
		npBVHNode* parent;
		npBVHNode* children[2];
		npBoundingVolume colShape;
		npRigidBody* body;

	//Methods
	public:
		npBVHNode(npBVHNode *parent, const npBoundingVolume &volume, npRigidBody* body = NULL)
			: parent(parent), colShape(volume), body(body)
		{
			children[0] = children[1] = NULL;
		}

		bool isLeaf() const {
			return (body != NULL);
		}

		unsigned getPotentialContacts(npPotentialContact* contacts, unsigned limit) const;

		void insert(npRigidBody* body, const npBoundingVolume &volume);
		
		~npBVHNode();
	
	protected:
		bool overlaps(const npBVHNode<npBoundingVolume>* otherVolume);

		unsigned getPotentialContactsWith(const npBVHNode<npBoundingVolume> *otherVolume, npPotentialContact* contacts,
			unsigned limit) const;

		void recalculateBoundingBolume(bool recurse);
	};

	template<npBoundingVolume>
	void npBVHNode<npBoundingVolume>::~npBVHNode()
	{
		// If we don't have a parent, then we ignore the sibling
		// processing
		if (parent)
		{
			// Find our sibling
			npBVHNode<npBoundingVolume> *sibling;
			if (parent->children[0] == this) sibling = parent->children[1];
			else sibling = parent->children[0];

			// Write its data to our parent
			parent->colShape = sibling->colShape;
			parent->body = sibling->body;
			parent->children[0] = sibling->children[0];
			parent->children[1] = sibling->children[1];

			// Delete the sibling (we blank its parent and
			// children to avoid processing/deleting them)
			sibling->parent = NULL;
			sibling->body = NULL;
			sibling->children[0] = NULL;
			sibling->children[1] = NULL;
			delete sibling;

			// Recalculate the parent's bounding volume
			parent->recalculateBoundingVolume();
		}

		// Delete our children (again we remove their
		// parent data so we don't try to process their siblings
		// as they are deleted).
		if (children[0]) {
			children[0]->parent = NULL;
			delete children[0];
		}
		if (children[1]) {
			children[1]->parent = NULL;
			delete children[1];
		}
	}

	template<npBoundingVolume>
	void npBVHNode<npBoundingVolume>::insert(npRigidBody* newBody, const npBoundingVolume &newVolume)
	{
		//If this node is leaf, spawn two children and place new body in one
		if (isLeaf())
		{
			children[0] = new BVHNode<BoundingVolumeClass>(this, volume, body); //body of node get's copied into first child

			children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody); //new body is now the second child

			this->body = NULL; //not leaf anymore

			//recalculateBoundingVolume(); //Recalculate bounding volume
		}
		else //If it's not a leaf we have to assign it to the right child
		{
			if (children[0]->colShape.getGrowth(newVolume) < children[1]->colShape.getGrowth(newVolume))
			{
				children[0]->insert(newBody, newVolume);
			}
			else
			{
				children[1]->insert(newBody, newVolume);
			}
		}
	}

	template<npBoundingVolume>
	unsigned npBVHNode<npBoundingVolume>::getPotentialContacts(npPotentialContact* contacts, unsigned limit) const
	{
		if (isLeaf() || limit == 0) return 0; //if leaf or no limit

		return children[0]->getPotentialContactsWith( children[1], contacts, limit); // Check overlaping of children
	}
	
	template<npBoundingVolume>
	bool npBVHNode<npBoundingVolume>::overlaps(const npBVHNode<npBoundingVolume> * otherVolume) const
	{
		return colShape->overlaps(otherVolume->colShape);
	}

	template<npBoundingVolume>
	unsigned npBVHNode<npBoundingVolume>::getPotentialContactsWith(const npBVHNode<npBoundingVolume> *otherVolume, npPotentialContact* contacts,
		unsigned limit) const
	{
		//doesn't overlap or no limit
		if (!overlaps(otherVolume) || limit == 0) return 0; 

		// if both at leaf nodes then this is a potential contact
		if (isLeaf() && otherVolume->isLeaf())
		{
			contacts->body[0] = body;
			contacts->body[1] = otherVolume->body;
			return 1;
		}

		// Determine which node to descend into. If either is
		// a leaf, then we descend the other. If both are branches,
		// then we use the one with the largest size.
		if (otherVolume->isLeaf() || (!isLeaf() && colShape->getSize() >= otherVolume->colShape->getSize()))
		{
			// Recurse into ourself
			unsigned count = children[0]->getPotentialContactsWith(otherVolume, contacts, limit);

			// Check we have enough slots to do the other side too
			if (limit > count) {
				return count + children[1]->getPotentialContactsWith(otherVolume, contacts + count, limit - count);
			}
			else {
				return count;
			}
		}
		else
		{
			// Recurse into the other node
			unsigned count = getPotentialContactsWith(otherVolume->children[0], contacts, limit);

			// Check we have enough slots to do the other side too
			if (limit > count) {
				return count + getPotentialContactsWith(otherVolume->children[1], contacts + count, limit - count);
			}
			else {
				return count;
			}
		}

	}

	template<npBoundingVolume>
	bool npBVHNode<npBoundingVolume>::overlapsrecalculateBoundingBolume(bool recurse)
	{
		if (isLeaf()) return;

		//Combine two bounding volumes
		volume = npBoundingVolume(
			children[0]->colShape,
			children[1]->colShape
			);

		// Recurse up the tree
		if (parent) parent->recalculateBoundingVolume(true);
	}

	//Specialisation for Sphere




	//Specialisation for AABB
}

#endif