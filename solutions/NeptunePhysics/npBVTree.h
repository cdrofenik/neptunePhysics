#ifndef NEPTUNE_BVTREE_H
#define NEPTUNE_BVTREE_H

#include "npContact.h"
#include "npCollisionShape.h"

namespace neptunePhysics {

	class BVTree {

	public:
		/*!
		Holds the parent of this tree/node - binary tree
		*/
		BVTree* parent;

		/*!
		Holds the children of this tree/node - binary tree
		*/
		BVTree* children[2];

		/*!
		Holds the collision volume of the tree/node
		*/
		npCollisionShape colShape;

		bool isLeaf() const {
			true;
		}

		unsigned getPotentialContacts(npPotentialContact* contacts, unsigned limit) const;

		//void insert(npRigidBody* body, const npCollisionShape& colShp);
	};
}


#endif