#ifndef NEPTUNE_NPPUNIFORMGRID_H
#define NEPTUNE_NPPUNIFORMGRID_H

#include "npIBroadPhase.hpp"
#include "Collision/CollisionShapes/npSphere.h"

namespace NeptunePhysics
{
	//Test function
	extern "C" int cuda_func(int &a, const int &b);

	class npPUniformGrid : public npIBroadPhase
	{
	public:
		npPUniformGrid(const int &_gridSize, const npVector3r &_cellSize);
		~npPUniformGrid();

		virtual void insert(const npAabb &_volume, const int &_bodyIdx);
		virtual void update(const npAabbUpdateData &_volumeData, const int &_bodyIdx);
		virtual bool remove(const npAabb &_volume, const int &_bodyIdx);
		virtual void getPotentialContacts(npPairManager* _pairManager);

	private:
		struct npObjectEntity
		{
			npObjectEntity(const npSphere &_bVol = npSphere(), const int &_id = -1) :
				bSphere(_bVol), id(_id)
			{
				npObjectEntity* previous = NP_NULL;
				npObjectEntity* next = NP_NULL;
			}

			npObjectEntity* previous;
			npObjectEntity* next;
			npSphere bSphere;
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
			unsigned int borderEntitiesCount;
			npObjectEntity* borderEntity;
		};

		unsigned int m_xExtent;
		unsigned int m_yExtent;
		unsigned int m_zExtent;
		bool m_initialized;

		npCell*** m_cells;
		npAlignedArray<npVector3ui> m_activeCellIds;

		npVector3r m_origin;
		npVector3r m_cellSize;

		void printGrid();
		void generateCells();
		npVector3ui getLocationIndex(const npVector3r &_centerPos) const;
		void addEntityToCell(const npVector3ui &_cellPos, npObjectEntity* _oEntity);
		void removeEntityFromCell(const npVector3ui &_cellPos, const int &_data);
		void updateEntityInCell(const npVector3ui &_cellPos, const npSphere &_volume, const int &_id);
	
		void insertCellBorderEnity(const npVector3ui &_cellPos, npObjectEntity * _oEntity);
		void updateCellBorderEntity(const npVector3ui & _cellPos, const npSphere & _volume, const int & _id);
		void removeCellBorderEnity(const npVector3ui & _cellPos, const int & _data);
	};
}

#endif