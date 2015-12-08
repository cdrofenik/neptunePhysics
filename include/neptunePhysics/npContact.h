#ifndef NEPTUNE_CONTACT_H
#define NEPTUNE_CONTACT_H

namespace NeptunePhysics {

	struct npPotentialContact {
		/*!
		Holds the bodies that might be in contact
		*/
		int rigidBody[2];
	};

}

#endif