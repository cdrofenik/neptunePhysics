//#ifndef NEPTUNE_BVNODE_H
//#define NEPTUNE_BVNODE_H
//
//#include "npContact.h"
//#include "npCollisionShape.h"
//#include "npCollisionBody.h"
//
//namespace NeptunePhysics {
//
//	template<npBV>
//	class npBVHNode {
//
//	//Members
//	public:
//		npBVHNode* parent;
//		npBVHNode* children[2];
//		npBV colShape;
//		npRigidBody* body;
//
//	//Methods
//	public:
//		npBVHNode(npBVHNode *parent, const npBV &volume, npRigidBody* body = NULL)
//			: parent(parent), colShape(volume), body(body)
//		{
//			children[0] = children[1] = NULL;
//		}
//
//		bool isLeaf() const {
//			return (body != NULL);
//		}
//
//		unsigned getPotentialContacts(npPotentialContact* contacts, unsigned limit) const;
//
//		void insert(npRigidBody* body, const npBV &volume);
//		
//		~npBVHNode();
//	
//	protected:
//		bool overlaps(const npBVHNode<npBV>* otherVolume);
//
//		unsigned getPotentialContactsWith(const npBVHNode<npBV> *otherVolume, npPotentialContact* contacts,
//			unsigned limit) const;
//
//		void recalculateBoundingBolume(bool recurse);
//	};
//
//	template<npBV>
//	void npBVHNode<npBV>::~npBVHNode()
//	{
//		// If we don't have a parent, then we ignore the sibling
//		// processing
//		if (parent)
//		{
//			// Find our sibling
//			npBVHNode<npBoundingVolume> *sibling;
//			if (parent->children[0] == this) sibling = parent->children[1];
//			else sibling = parent->children[0];
//
//			// Write its data to our parent
//			parent->colShape = sibling->colShape;
//			parent->body = sibling->body;
//			parent->children[0] = sibling->children[0];
//			parent->children[1] = sibling->children[1];
//
//			// Delete the sibling (we blank its parent and
//			// children to avoid processing/deleting them)
//			sibling->parent = NULL;
//			sibling->body = NULL;
//			sibling->children[0] = NULL;
//			sibling->children[1] = NULL;
//			delete sibling;
//
//			// Recalculate the parent's bounding volume
//			parent->recalculateBoundingVolume();
//		}
//
//		// Delete our children (again we remove their
//		// parent data so we don't try to process their siblings
//		// as they are deleted).
//		if (children[0]) {
//			children[0]->parent = NULL;
//			delete children[0];
//		}
//		if (children[1]) {
//			children[1]->parent = NULL;
//			delete children[1];
//		}
//	}
//
//	template<npBV>
//	void npBVHNode<npBV>::insert(npRigidBody* newBody, const npBV &newVolume)
//	{
//		//If this node is leaf, spawn two children and place new body in one
//		if (isLeaf())
//		{
//			children[0] = new BVHNode<BoundingVolumeClass>(this, volume, body); //body of node get's copied into first child
//
//			children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody); //new body is now the second child
//
//			this->body = NULL; //not leaf anymore
//
//			//recalculateBoundingVolume(); //Recalculate bounding volume
//		}
//		else //If it's not a leaf we have to assign it to the right child
//		{
//			if (children[0]->colShape.getGrowth(newVolume) < children[1]->colShape.getGrowth(newVolume))
//			{
//				children[0]->insert(newBody, newVolume);
//			}
//			else
//			{
//				children[1]->insert(newBody, newVolume);
//			}
//		}
//	}
//
//	template<npBV>
//	unsigned npBVHNode<npBV>::getPotentialContacts(npPotentialContact* contacts, unsigned limit) const
//	{
//		if (isLeaf() || limit == 0) return 0; //if leaf or no limit
//
//		return children[0]->getPotentialContactsWith( children[1], contacts, limit); // Check overlaping of children
//	}
//	
//	template<npBV>
//	bool npBVHNode<npBV>::overlaps(const npBVHNode<npBV> * otherVolume) const
//	{
//		return colShape->overlaps(otherVolume->colShape);
//	}
//
//	template<npBV>
//	unsigned npBVHNode<npBV>::getPotentialContactsWith(const npBVHNode<npBV> *otherVolume, npPotentialContact* contacts,
//		unsigned limit) const
//	{
//		//doesn't overlap or no limit
//		if (!overlaps(otherVolume) || limit == 0) return 0; 
//
//		// if both at leaf nodes then this is a potential contact
//		if (isLeaf() && otherVolume->isLeaf())
//		{
//			contacts->body[0] = body;
//			contacts->body[1] = otherVolume->body;
//			return 1;
//		}
//
//		// Determine which node to descend into. If either is
//		// a leaf, then we descend the other. If both are branches,
//		// then we use the one with the largest size.
//		if (otherVolume->isLeaf() || (!isLeaf() && colShape->getSize() >= otherVolume->colShape->getSize()))
//		{
//			// Recurse into ourself
//			unsigned count = children[0]->getPotentialContactsWith(otherVolume, contacts, limit);
//
//			// Check we have enough slots to do the other side too
//			if (limit > count) {
//				return count + children[1]->getPotentialContactsWith(otherVolume, contacts + count, limit - count);
//			}
//			else {
//				return count;
//			}
//		}
//		else
//		{
//			// Recurse into the other node
//			unsigned count = getPotentialContactsWith(otherVolume->children[0], contacts, limit);
//
//			// Check we have enough slots to do the other side too
//			if (limit > count) {
//				return count + getPotentialContactsWith(otherVolume->children[1], contacts + count, limit - count);
//			}
//			else {
//				return count;
//			}
//		}
//
//	}
//
//	template<npBV>
//	bool npBVHNode<npBV>::overlapsrecalculateBoundingBolume(bool recurse)
//	{
//		if (isLeaf()) return;
//
//		//Combine two bounding volumes
//		volume = npBoundingVolume(
//			children[0]->colShape,	
//			children[1]->colShape
//			);
//
//		// Recurse up the tree
//		if (parent) parent->recalculateBoundingVolume(true);
//	}
//
//	//Specialisation for Sphere
//
//
//
//
//	//Specialisation for AABB
//}
//
//#endif