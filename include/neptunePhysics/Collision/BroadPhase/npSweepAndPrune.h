#ifndef NEPTUNE_NPSORTANDSWEEP_H
#define NEPTUNE_NPSORTANDSWEEP_H

#include "Core/npAlignedArray.hpp"

#include "npIBroadPhase.hpp"

namespace NeptunePhysics
{
	struct npSweepObject
	{
		int min[3];
		int max[3];
		int bodyIdx;
	};

	struct npEndPoint
	{
		unsigned int value;
		int soIndex;
		bool isMax;
	};

	class npSweepAndPrune : public npIBroadPhase
	{
	public:
		npSweepAndPrune(npPairManager* _pairManager);
		~npSweepAndPrune();

		virtual void insert(const npAabb &_volume, const int &_bodyIdx);
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx);
		virtual bool remove(const npAabb &_volume, const int &_bodyIdx);
		virtual void getPotentialContacts(npPairManager* _pairManager) {}

	private:
		int m_sObjectCounter;
		int m_ePointCounter;
		npEndPoint* m_endPoints[3];
		npAlignedArray<npSweepObject> m_sObjects;
		npPairManager* ref_pairManager;

		unsigned int quantize(const npReal& _value);
		bool isColliding(const int &_axis1, const npSweepObject & _so1,
			const int &_axis2, const npSweepObject &_so2);
		void checkIfColliding(const int &_axis, const npSweepObject &_activeSo,
			const npSweepObject &_so, const bool &_adding, bool _updateOverlaps);
		void printEndPoints(int axis, int limit);
		void sortMin(const int &_axis, const int &_startIndex,
			const bool &_updateOverlaps, const bool &_ascending);
		void sortMax(const int &_axis, const int &_startIndex,
			const bool &_updateOverlaps, const bool &_ascending);
	};
}
#endif