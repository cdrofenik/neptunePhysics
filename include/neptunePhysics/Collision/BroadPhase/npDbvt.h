#ifndef NEPTUNE_NPBVT_H
#define NEPTUNE_NPBVT_H

#include "../../Core/npAlignedArray.hpp"

#include "npBroadPhase.h"

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

	class npDbvt : public npIBroadPhase
	{
	public:
		npDbvt();
		~npDbvt();

		virtual void insert(const npAabb &_volume, const int &_bodyIdx);
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx);
		virtual void remove(const npAabb &_volume, const int &_bodyIdx);
		virtual void getPotentialContacts(npPairManager** _pairManager);

		void DebugPrintTree();

		npDbvtNode* m_root;
		int m_leaves;

	private:
		void npDbvt::clean();
		void recalculateBoundingVolumes(npDbvtNode* _node);
	};

}

#endif