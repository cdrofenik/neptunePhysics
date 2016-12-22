#ifndef NEPTUNE_NPPAIRMANAGER_H
#define NEPTUNE_NPPAIRMANAGER_H

#include "core/npAlignedArray.h"

namespace NeptunePhysics {

	struct npPotentialPair {
		/*!
		Holds the bodies that might be in contact
		*/
		int bodyIdA = -1;
		int bodyIdB = -1;
	};

	class npPairManager
	{
	public:
		npPairManager::npPairManager() {}

		npPairManager::~npPairManager()
		{
			m_potentialPairs.clear();
		}

		void npPairManager::addPair(const int &_indexA, const int &_indexB)
		{
			npPotentialPair pair;
			pair.bodyIdA = _indexA;
			pair.bodyIdB = _indexB;
			m_potentialPairs.push_back(pair);
		}

		void npPairManager::removePair(const int &_indexA, const int &_indexB)
		{
			for (int i = 0; i < m_potentialPairs.size(); i++)
			{
				auto currentPair = m_potentialPairs.at(i);
				if ((currentPair.bodyIdA == _indexA && currentPair.bodyIdB == _indexB) ||
					(currentPair.bodyIdA == _indexB && currentPair.bodyIdB == _indexA))
				{
					m_potentialPairs.removeAt(i);
				}
			}
		}

		npAlignedArray<npPotentialPair> getPotentialPairs() {
			return m_potentialPairs;
		}

	private:
		npAlignedArray<npPotentialPair> m_potentialPairs = npAlignedArray<npPotentialPair>();

	};

	
}
#endif