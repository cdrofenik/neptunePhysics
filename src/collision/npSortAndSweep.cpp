#include "collision/npSortAndSweep.h"

#include <iostream>

namespace NeptunePhysics
{
	void npSortAndSweep::printEndPoints(int _axis, int _limit)
	{
		std::cout << "Endpoints for axis: " << _axis << std::endl;
		for (int i = 0; i < _limit; i++)
		{
			npEndPoint* currEp = m_endPoints[_axis] + i;
			std::cout << "Endpoint: " << i << " - values: " << currEp->value << " /Max: ";
			std::cout << currEp->isMax << " /soIndex: " << currEp->soIndex << std::endl;
		}
	}

	inline unsigned int npSortAndSweep::quantize(const npReal& _value)
	{
		unsigned int value = 0;
		memcpy(&value, &_value, sizeof(value));

		if (value & 0x80000000)
			value = ~value;
		else
			value |= 0x80000000;

		return value;
	}

#pragma region SAS-core
	bool npSortAndSweep::isColliding(const int &_axis0, const npSweepObject &_so0,
		const int &_axis1, const npSweepObject &_so1)
	{
		/*if (_so0.max[_axis0] < _so1.min[_axis0] ||
			_so1.max[_axis0] < _so0.min[_axis0] ||
			_so0.max[_axis1] < _so1.min[_axis1] ||
			_so1.max[_axis1] < _so0.min[_axis1])
		{
			return false;
		}
		return true;*/

		bool firstAxisTest = false;
		if (_so0.min[_axis0] < _so1.max[_axis0] && _so0.max[_axis0] > _so1.min[_axis0])
		{
			firstAxisTest = true;
		}

		bool secondAxisTest = false;
		if (_so0.min[_axis1] < _so1.max[_axis1] && _so0.max[_axis1] > _so1.min[_axis1])
		{
			secondAxisTest = true;
		}

		return firstAxisTest && secondAxisTest;
	}

	void npSortAndSweep::checkIfColliding(const int &_axis, const npSweepObject &_activeSo,
		const npSweepObject &_soOther, const bool &_adding, bool _updateOverlaps)
	{
		const int axis1 = (1 << _axis) & 3;
		const int axis2 = (1 << axis1) & 3;
		if (_updateOverlaps && isColliding(axis1, _activeSo, axis2, _soOther)) {
			//Add to or remove from pair manager
			npPairManager* ref = *ref_pairManager;
			if (_adding)
				ref->addPair(_activeSo.bodyIdx, _soOther.bodyIdx);
			else
				ref->removePair(_activeSo.bodyIdx, _soOther.bodyIdx);

		}
	}

	void npSortAndSweep::sortMinDown(const int &_axis, const int &_startIndex, bool _updateOverlaps)
	{
		npEndPoint* activeEp = m_endPoints[_axis] + _startIndex;
		npEndPoint* prevEp = activeEp - 1;
		npSweepObject activeSo = m_sObjects.at(activeEp->soIndex);

		while (activeEp->value < prevEp->value)
		{
			npSweepObject so = m_sObjects.at(prevEp->soIndex);

			if (prevEp->isMax)
			{
				checkIfColliding(_axis, activeSo, so, true, _updateOverlaps);
				m_sObjects.at(prevEp->soIndex).max[_axis]++;
			}
			else {
				m_sObjects.at(prevEp->soIndex).min[_axis]++;
			}

			m_sObjects.at(activeEp->soIndex).min[_axis]--;

			//swap edges
			npEndPoint tmp = *activeEp;
			*activeEp = *prevEp;
			*prevEp = tmp;

			//decrement
			activeEp--;
			prevEp--;
		}
	}

	void npSortAndSweep::sortMinUp(const int &_axis, const int &_startIndex, bool _updateOverlaps)
	{
		npEndPoint* activeEp = m_endPoints[_axis] + _startIndex;
		npEndPoint* nextEp = activeEp + 1;
		npSweepObject activeSo = m_sObjects.at(activeEp->soIndex);

		while (activeEp->value >= nextEp->value)
		{
			npSweepObject so = m_sObjects.at(nextEp->soIndex);

			if (nextEp->isMax)
			{
				checkIfColliding(_axis, activeSo, so, false, _updateOverlaps);
				m_sObjects.at(nextEp->soIndex).max[_axis]--;
			}
			else
				m_sObjects.at(nextEp->soIndex).min[_axis]--;

			m_sObjects.at(activeEp->soIndex).min[_axis]++;

			//swap edges
			npEndPoint tmp = *activeEp;
			*activeEp = *nextEp;
			*nextEp = tmp;

			//incerement
			activeEp++;
			nextEp++;
		}
	}

	void npSortAndSweep::sortMaxDown(const int &_axis, const int &_startIndex, bool _updateOverlaps)
	{
		npEndPoint* activeEp = m_endPoints[_axis] + _startIndex;
		npEndPoint* prevEp = activeEp - 1;
		npSweepObject activeSo = m_sObjects.at(activeEp->soIndex);

		while (activeEp->value < prevEp->value)
		{
			npSweepObject so = m_sObjects.at(prevEp->soIndex);

			if (!prevEp->isMax)
			{
				checkIfColliding(_axis, activeSo, so, false, _updateOverlaps);
				m_sObjects.at(prevEp->soIndex).min[_axis]++;
			}
			else
				m_sObjects.at(prevEp->soIndex).max[_axis]++;

			m_sObjects.at(activeEp->soIndex).max[_axis]--;

			//swap edges
			npEndPoint tmp = *activeEp;
			*activeEp = *prevEp;
			*prevEp = tmp;

			//decrement
			activeEp--;
			prevEp--;
		}
	}

	void npSortAndSweep::sortMaxUp(const int &_axis, const int &_startIndex, bool _updateOverlaps)
	{
		npEndPoint* activeEp = m_endPoints[_axis] + _startIndex;
		npEndPoint* nextEp = activeEp + 1;
		npSweepObject activeSo = m_sObjects.at(activeEp->soIndex);

		while (activeEp->value >= nextEp->value)
		{
			npSweepObject so = m_sObjects.at(nextEp->soIndex);

			if (!nextEp->isMax)
			{
				checkIfColliding(_axis, activeSo, so, true, _updateOverlaps);
				m_sObjects.at(nextEp->soIndex).min[_axis]--;
			}
			else
				m_sObjects.at(nextEp->soIndex).max[_axis]--;

			m_sObjects.at(activeEp->soIndex).max[_axis]++;

			//swap edges
			npEndPoint tmp = *activeEp;
			*activeEp = *nextEp;
			*nextEp = tmp;

			//incerement
			activeEp++;
			nextEp++;
		}
	}
#pragma endregion

	void npSortAndSweep::insert(const npAabb& _volume, const int &_bodyIdx)
	{
		npSweepObject so;
		so.bodyIdx = _bodyIdx;
		for (int axis = 0; axis < 3; axis++)
		{
			m_endPoints[axis][m_ePointCounter + 1] = m_endPoints[axis][m_ePointCounter - 1];

			unsigned int val = quantize(_volume.m_minVec.getValue(axis));
			m_endPoints[axis][m_ePointCounter - 1].value = val;
			m_endPoints[axis][m_ePointCounter - 1].soIndex = m_sObjectCounter;
			m_endPoints[axis][m_ePointCounter - 1].isMax = false;

			val = quantize(_volume.m_maxVec.getValue(axis));
			m_endPoints[axis][m_ePointCounter].value = val;
			m_endPoints[axis][m_ePointCounter].soIndex = m_sObjectCounter;
			m_endPoints[axis][m_ePointCounter].isMax = true;

			so.min[axis] = m_ePointCounter - 1;
			so.max[axis] = m_ePointCounter;
		}

		m_sObjects.push_back(so);

		sortMinDown(0, so.min[0], false);
		sortMaxDown(0, so.max[0], false);
		sortMinDown(1, so.min[1], false);
		sortMaxDown(1, so.max[1], false);
		sortMinDown(2, so.min[2], true);
		sortMaxDown(2, so.max[2], true);

		m_ePointCounter += 2;
		m_sObjectCounter++;
	}

	void npSortAndSweep::update(const npAabb &_volume, const int &_soIdx)
	{
		npSweepObject activeSo = m_sObjects.at(_soIdx);
		for (int axis = 0; axis < 3; axis++)
		{

			int minIdx = activeSo.min[axis];
			int maxIdx = activeSo.max[axis];

			unsigned int _volumeMin = quantize(_volume.m_minVec.getValue(axis));
			unsigned int _volumeMax = quantize(_volume.m_maxVec.getValue(axis));

			unsigned int dMin = _volumeMin - m_endPoints[axis][minIdx].value;
			unsigned int dMax = _volumeMax - m_endPoints[axis][maxIdx].value;

			m_endPoints[axis][minIdx].value = _volumeMin;
			m_endPoints[axis][maxIdx].value = _volumeMax;

			if (dMin < 0)
				sortMinDown(axis, minIdx, true);
			else if (dMin > 0)
				sortMinUp(axis, minIdx, true);

			if (dMax < 0)
				sortMaxDown(axis, maxIdx, true);
			else if (dMax > 0)
				sortMaxUp(axis, maxIdx, true);
		}
	}

	void npSortAndSweep::remove(const int &_bodyIdx)
	{
		//TODO: implement remove function
	}

	npSortAndSweep::npSortAndSweep(npPairManager** _pairManager)
	{
		m_sObjects = npAlignedArray<npSweepObject>();
		m_sObjectCounter = 0;

		ref_pairManager = _pairManager;

		for (int i = 0; i < 3; i++)
		{
			m_endPoints[i] = new npEndPoint[20 * 2];
		}

		m_ePointCounter = 2;
		//Adding sentinels to all axises
		for (int axis = 0; axis < 3; axis++)
		{
			m_endPoints[axis][0].isMax = false;
			m_endPoints[axis][0].soIndex = -1;
			m_endPoints[axis][0].value = 0;

			m_endPoints[axis][1].isMax = true;
			m_endPoints[axis][1].soIndex = -1;
			m_endPoints[axis][1].value = ULONG_MAX;
		
			printEndPoints(axis, m_ePointCounter);
		}
	}

	npSortAndSweep::~npSortAndSweep()
	{
		delete[] &m_endPoints;
		m_sObjects.clear();
	}
}