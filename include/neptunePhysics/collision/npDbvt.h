#ifndef NEPTUNE_NPBVT_H
#define NEPTUNE_NPBVT_H

#include "npAabb.h"
#include "npContact.h"

#include <vector>

namespace NeptunePhysics {

	struct npDbvtNode
	{
		npDbvtNode* parent;
		npAabb volume;

		union {
			npDbvtNode* children[2];
			void* data;
		};

		bool isLeaf() const { return (children[1] == 0); }
		bool isInternal() const { return (!isLeaf()); }
	};

	class npDbvt
	{
	public:
		npDbvt();
		~npDbvt();

		void insert(const npAabb& volume, void* data);
		void updateTree(std::vector<npAabbUpdateData> diffList);
		void getPotentialContacts(npPotentialContact* contacts);

		void DebugPrintTree();

		npDbvtNode* m_root;
		int m_leaves;

	private:
		void npDbvt::clean();
		void recalculateBoundingVolumes(npDbvtNode* node);
	};

}

#endif