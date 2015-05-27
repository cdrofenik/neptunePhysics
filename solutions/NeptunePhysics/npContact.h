#ifndef NEPTUNE_CONTACT_H
#define NEPTUNE_CONTACT_H

namespace neptunePhysics {

	struct npPotentialContact {
		/*!
		Holds the bodies that might be in contact
		*/
		int rigidBody[2];
	};

}

#endif