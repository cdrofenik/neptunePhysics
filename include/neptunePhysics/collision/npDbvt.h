#ifndef NEPTUNE_NPBVT_H
#define NEPTUNE_NPBVT_H

#include "../core/npAlignedArray.h"

#include "npAabb.h"
#include "npPairManager.h"

#include <vector>

namespace NeptunePhysics {

	struct npDbvtNode
	{
		npDbvtNode* parent;
		npAabb volume;

		union {
			npDbvtNode* children[2];
			int bodyIdx;
		};

		bool isLeaf() const { return (children[1] == 0); }
		bool isInternal() const { return (!isLeaf()); }
	};

	class npDbvt
	{
	public:
		npDbvt();
		~npDbvt();

		void insert(const npAabb &_volume, const int &_data);
		void updateTree(npAlignedArray<npAabbUpdateData> _diffList);
		void getPotentialContacts(npPairManager** _pairManager);

		void DebugPrintTree();

		npDbvtNode* m_root;
		int m_leaves;

	private:
		void npDbvt::clean();
		void recalculateBoundingVolumes(npDbvtNode* _node);
	};

}

#endif