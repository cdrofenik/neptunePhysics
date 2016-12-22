#ifndef NEPTUNE_BROAD_SEARCH_H
#define NEPTUNE_BROAD_SEARCH_H

#include "npAabb.h"
#include "npPairManager.h"

namespace NeptunePhysics {

	class npIBroadPhase {

	public:
		virtual void insert(const npAabb &_volume, const int &_bodyIdx) = 0;
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx) = 0;
		virtual void remove(const npAabb &_volume, const int &_bodyIdx) = 0;
		virtual void getPotentialContacts(npPairManager** _pairManager) = 0;
	};
}

#endif