#ifndef NEPTUNE_CONTACT_H
#define NEPTUNE_CONTACT_H

#include "npRigidBody.h"

namespace NeptunePhysics {

	struct npPotentialContact {
		/*!
		Holds the bodies that might be in contact
		*/
		npRigidBody* bodyA = 0;
		npRigidBody* bodyB = 0;
	};

}

#endif