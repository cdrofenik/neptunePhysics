#include "Collision/BroadPhase/npSweepAndPrune.h"

#include <iostream>

namespace NeptunePhysics
{
    void npSweepAndPrune::printEndPoints(int _axis, int _limit)
    {
        std::cout << "Endpoints for axis: " << _axis << std::endl;
        for (int i = 0; i < _limit; i++)
        {
            npEndPoint* currEp = m_endPoints[_axis] + i;
            std::cout << "Endpoint: " << i << " - values: " << currEp->value << " /Max: ";
            std::cout << currEp->isMax << " /soIndex: " << currEp->soIndex << std::endl;
        }
    }

    inline unsigned int npSweepAndPrune::quantize(const npReal& _value)
    {
        unsigned int value = 0;
        memcpy(&value, &_value, sizeof(value));

        if (value & 0x80000000)
            value = ~value;
        else
            value |= 0x80000000;

        return value;
    }

    bool npSweepAndPrune::isColliding(const int &_axis0, const npSweepObject &_so0,
        const int &_axis1, const npSweepObject &_so1)
    {
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

    void npSweepAndPrune::checkIfColliding(const int &_axis, const npSweepObject &_activeSo,
        const npSweepObject &_soOther, const bool &_adding, bool _updateOverlaps)
    {
        const int axis1 = (1 << _axis) & 3;
        const int axis2 = (1 << axis1) & 3;
        if (_updateOverlaps && isColliding(axis1, _activeSo, axis2, _soOther)) {
            //Add to or remove from pair manager
            if (_adding)
                ref_pairManager->addPair(_activeSo.bodyIdx, _soOther.bodyIdx);
            else
                ref_pairManager->removePair(_activeSo.bodyIdx, _soOther.bodyIdx);

        }
    }

    bool isAscending(unsigned int a, unsigned int b)
    {
        return a > b;
    }

    bool isDecending(unsigned int a, unsigned int b)
    {
        return a < b;
    }

    void npSweepAndPrune::sortMin(const int &_axis,
        const int &_startIndex,
        const bool &_updateOverlaps,
        const bool &_ascending = false)
    {
        int shiftValue = _ascending ? 1 : -1;
        bool (*evaluationFunc)(unsigned int, unsigned int) = _ascending ? isAscending : isDecending;

        npEndPoint* activeEP = m_endPoints[_axis] + _startIndex;
        npEndPoint* nextEP = activeEP + shiftValue;
        npSweepObject activeSo = m_sObjects.at(activeEP->soIndex);

        while (evaluationFunc(activeEP->value, nextEP->value))
        {
            npSweepObject so = m_sObjects.at(nextEP->soIndex);
            if (nextEP->isMax)
            {
                checkIfColliding(_axis, activeSo, so, !_ascending, _updateOverlaps);
                m_sObjects.at(nextEP->soIndex).max[_axis] += (shiftValue * -1);
            }
            else {
                m_sObjects.at(nextEP->soIndex).min[_axis] += (shiftValue * -1);
            }

            m_sObjects.at(activeEP->soIndex).min[_axis] += shiftValue;

            //swap edgepoints
            npEndPoint tmp = *activeEP;
            *activeEP = *nextEP;
            *nextEP = tmp;

            //increment or decrement depending on _ascending
            activeEP += shiftValue;
            nextEP += shiftValue;
        }
    }

    void npSweepAndPrune::sortMax(const int &_axis,
        const int &_startIndex,
        const bool &_updateOverlaps,
        const bool &_ascending = false)
    {
        int shiftValue = _ascending ? 1 : -1;
        bool(*evaluationFunc)(unsigned int, unsigned int) = _ascending ? isAscending : isDecending;
    
        npEndPoint* activeEP = m_endPoints[_axis] + _startIndex;
        npEndPoint* nextEP = activeEP + shiftValue;
        npSweepObject activeSo = m_sObjects.at(activeEP->soIndex);

        while (evaluationFunc(activeEP->value, nextEP->value))
        {
            npSweepObject so = m_sObjects.at(nextEP->soIndex);
            if (!nextEP->isMax)
            {
                checkIfColliding(_axis, activeSo, so, _ascending, _updateOverlaps);
                m_sObjects.at(nextEP->soIndex).min[_axis] += (shiftValue * -1);
            }
            else
                m_sObjects.at(nextEP->soIndex).max[_axis] += (shiftValue * -1);

            m_sObjects.at(activeEP->soIndex).max[_axis] += shiftValue;

            //swap edgepoints
            npEndPoint tmp = *activeEP;
            *activeEP = *nextEP;
            *nextEP = tmp;

            //increment or decrement depending on _ascending
            activeEP += shiftValue;
            nextEP += shiftValue;
        }
    }

    void npSweepAndPrune::insert(const npAabb &_volume, const int &_bodyIdx)
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

        sortMin(0, so.min[0], false);
        sortMax(0, so.max[0], false);
        sortMin(1, so.min[0], false);
        sortMax(1, so.max[0], false);
        sortMin(2, so.min[0], true);
        sortMax(2, so.max[0], true);

        m_ePointCounter += 2;
        m_sObjectCounter++;
    }

    void npSweepAndPrune::update(const npAabbUpdateData &_volumeData, const int &_bodyIdx)
    {
        npAabb updatedAabb;
        updatedAabb.m_minVec = _volumeData.originalAabb.m_minVec + _volumeData.directionDiff;
        updatedAabb.m_maxVec = _volumeData.originalAabb.m_maxVec + _volumeData.directionDiff;

        npSweepObject activeSo = m_sObjects.at(_bodyIdx);
        for (int axis = 0; axis < 3; axis++)
        {

            int minIdx = activeSo.min[axis];
            int maxIdx = activeSo.max[axis];

            unsigned int _volumeMin = quantize(updatedAabb.m_minVec.getValue(axis));
            unsigned int _volumeMax = quantize(updatedAabb.m_maxVec.getValue(axis));

            unsigned int dMin = _volumeMin - m_endPoints[axis][minIdx].value;
            unsigned int dMax = _volumeMax - m_endPoints[axis][maxIdx].value;

            m_endPoints[axis][minIdx].value = _volumeMin;
            m_endPoints[axis][maxIdx].value = _volumeMax;

            if (dMin != 0)
                sortMin(axis, minIdx, true, dMin > 0);

            if (dMax != 0)
                sortMax(axis, maxIdx, true, dMax > 0);
        }
    }

    bool npSweepAndPrune::remove(const npAabb &_volume, const int &_bodyIdx)
    {
        //TODO: implement remove function
        return false;
    }

    npSweepAndPrune::npSweepAndPrune(npPairManager* _pairManager)
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

    npSweepAndPrune::~npSweepAndPrune()
    {
        delete[] &m_endPoints;
        m_sObjects.clear();
    }
}