#ifndef NEPTUNE_BROAD_SEARCH_H
#define NEPTUNE_BROAD_SEARCH_H

namespace NeptunePhysics {

	class npBroadSearch {

	public:
		enum broadSearchType
		{
			BVH,
			OCTTree,
			SAP
		};

		npBroadSearch(broadSearchType type);
		~npBroadSearch();

	};

}

#endif