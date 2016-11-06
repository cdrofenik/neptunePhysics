#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "math/npVector3.hpp"

#include "npAabb.h"
#include "npContact.h"

#include <vector>

namespace NeptunePhysics
{

	struct SweepObject
	{
		npVector3 min;
		npVector3 max;
		void* data;
	};

	class npSortAndSweep
	{
	public:
		npSortAndSweep();
		~npSortAndSweep();

		//void insert(const npAabb& volume, void* data);
		//void updateTree(std::vector<npAabbUpdateData> diffList);
		//void getPotentialContacts(npPotentialContact* contacts);

	private:
		std::vector<SweepObject> xAxisList;
		std::vector<SweepObject> yAxisList;
		std::vector<SweepObject> zAxisList;
	};

}

#endif