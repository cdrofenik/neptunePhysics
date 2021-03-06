#ifndef NEPTUNE_NPUNIFORMGRID_H
#define NEPTUNE_NPUNIFORMGRID_H

#include "../../Math/npVector3.hpp"
#include "../../Core/npAlignedArray.hpp"

#include "npIBroadPhase.hpp"

namespace NeptunePhysics {

	struct npObjectEntity
	{
		npObjectEntity(const npAabb &_bbox = npAabb(), const int &_id = -1) : bbox(_bbox), id(_id)
		{
			npObjectEntity* previous = NP_NULL;
			npObjectEntity* next = NP_NULL;
		}

		npObjectEntity* previous;
		npObjectEntity* next;
		npAabb bbox;
		int id;
	};

	struct npCell
	{
		npCell(const npReal &_x = 0.0, const npReal &_y = 0.0, const npReal &_z = 0.0) {
			center = npVector3r(_x, _y, _z);
			entityCount = NP_NULL;
			entity = NP_NULL;
		}

		int entityCount;
		npVector3r center;
		npObjectEntity* entity;
	};

	class npUniformGrid : public npIBroadPhase
	{
	public:
		npUniformGrid(const int &_gridSize, const npVector3r &_cellSize);
		~npUniformGrid();

		virtual void insert(const npAabb &_volume, const int &_bodyIdx);
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx);
		virtual bool remove(const npAabb &_volume, const int &_bodyIdx);
		virtual void getPotentialContacts(npPairManager* _pairManager);

	private:
		unsigned int m_xExtent;
		unsigned int m_yExtent;
		unsigned int m_zExtent;

		npCell*** m_cells;
		npAlignedArray<npVector3ui> m_activeCellIds;

		npVector3r m_origin;
		npVector3r m_cellSize;
	
		void printGrid();
		void generateCells();
		npVector3ui getLocationIndex(const npVector3r &_centerPos) const;
		void addEntityToCell(const npVector3ui &_cellPos, npObjectEntity* _oEntity);
		void removeEntityFromCell(const npVector3ui &_cellPos, const int &_data);
		void updateEntityInCell(const npVector3ui &_cellPos, const npAabb &_volume, const int &_id);
	};
}
#endif