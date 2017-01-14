#ifndef NEPTUNE_NPPUNIFORMGRID_H
#define NEPTUNE_NPPUNIFORMGRID_H

#include "npIBroadPhase.hpp"

namespace NeptunePhysics
{
	//Test function
	extern "C" int cuda_func(int &a, const int &b);

	class npPUniformGrid : public npIBroadPhase
	{
	public:
		npPUniformGrid();
		~npPUniformGrid();

		virtual void insert(const npAabb &_volume, const int &_bodyIdx);
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx);
		virtual bool remove(const npAabb &_volume, const int &_bodyIdx);
		virtual void getPotentialContacts(npPairManager* _pairManager);

	private:

	};
}

#endif