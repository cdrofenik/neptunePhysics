#include "Collision/BroadPhase/npUniformGrid.h"

#include <iostream>
#include <math.h>

namespace NeptunePhysics {

	inline static void processCellOwnCell(npCell* _cell, npObjectEntity* _entity, npPairManager* _pM)
	{
		int entryNum = _cell->entityCount;
		npObjectEntity* activeOE = _cell->entity;
		while (entryNum > 1)
		{
			_pM->addPair(_entity->id, activeOE->id);
			activeOE = activeOE->next;
			entryNum--;
		}
	}

	inline static void processCell(npCell* _cell, npObjectEntity* _entity, npPairManager* _pM)
	{
		int entryNum = _cell->entityCount;
		npObjectEntity* activeOE = _cell->entity;
		while (entryNum >= 1)
		{
			//quick distance check
			_pM->addPair(_entity->id, activeOE->id);
			activeOE = activeOE->next;
			entryNum--;
		}
	}

	inline static npReal getCellBorder(const npReal &_origin, const npReal &_size, const int _index)
	{
		return _origin + (_size * _index) + _size / 2;
	}

	static void copyObjectEntity(npObjectEntity* _source,
		npObjectEntity* _destination)
	{
		_destination->previous = _source->previous;
		_destination->next = _source->next;
		_destination->bbox = _source->bbox;
		_destination->id = _source->id;
	}

	void npUniformGrid::printGrid()
	{
		for (size_t x = 0; x < m_xExtent; x++)
		{
			std::cout << "npCell z-axis: " << x << std::endl;
			for (size_t y = 0; y < m_yExtent; y++)
			{
				std::cout << "npCell x-axis: " << y << std::endl;
				for (size_t z = 0; z < m_zExtent; z++)
				{

					std::cout << "npCell y-axis: " << z << std::endl;
					npCell* cell = &m_cells[x][y][z];

					std::cout << "npCell: " << cell->center.x << " , " << cell->center.y << " , ";
					std::cout << cell->center.z << " /entryCount: " << cell->entityCount << std::endl;
				}
			}
		}
	}

	void npUniformGrid::generateCells()
	{
		m_cells = new npCell**[m_xExtent];
		for (unsigned int x = 0; x < m_xExtent; ++x) {
			m_cells[x] = new npCell*[m_yExtent];
			for (unsigned int y = 0; y < m_yExtent; ++y) {
				m_cells[x][y] = new npCell[m_zExtent];
				for (unsigned int z = 0; z < m_zExtent; ++z) {
					npCell* cell = &m_cells[x][y][z];
					cell->center.x = m_origin.x + m_cellSize.x * x;
					cell->center.y = m_origin.y + m_cellSize.y * y;
					cell->center.z = m_origin.z + m_cellSize.z * z;
				}
			}
		}

		//printGrid();
	}

	npVector3ui npUniformGrid::getLocationIndex(const npVector3r &_topLeftPos) const
	{
		unsigned int xCellIdx = static_cast<unsigned int>(floor((_topLeftPos.x - m_origin.x) / m_cellSize.x));
		unsigned int yCellIdx = static_cast<unsigned int>(floor((_topLeftPos.y - m_origin.y) / m_cellSize.y));
		unsigned int zCellIdx = static_cast<unsigned int>(floor((_topLeftPos.z - m_origin.z) / m_cellSize.z));

		return npVector3ui(xCellIdx, yCellIdx, zCellIdx);
	}

	void npUniformGrid::addEntityToCell(const npVector3ui &_cellPos, npObjectEntity* _oEntity)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		if (currCell->entityCount > 0)
		{
			npObjectEntity* oePntr = currCell->entity;
			int cellEntryCount = currCell->entityCount;
			while (cellEntryCount > 0)
			{
				if (cellEntryCount == 1) {
					break;
				}
				else {
					oePntr = oePntr->next;
					cellEntryCount--;
				}
			}

			_oEntity->previous = oePntr;
			oePntr->next = _oEntity;
			currCell->entityCount++;
		}
		else
		{
			currCell->entity = _oEntity;
			currCell->entityCount++;
		}
	}

	void npUniformGrid::removeEntityFromCell(const npVector3ui &_cellPos, const int &_data)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		if (currCell->entityCount > 1)
		{
			npObjectEntity* oePntr = currCell->entity;
			int cellEntryCount = currCell->entityCount;
			while (cellEntryCount > 0)
			{
				if (oePntr->id == _data) {
					if (cellEntryCount > 1) {
						oePntr->bbox = oePntr->next->bbox;
						oePntr->id = oePntr->next->id;
						oePntr->next = oePntr->next->next;

						oePntr = NP_NULL;
					}
					else {
						oePntr = NP_NULL;
					}
					currCell->entity--;
					return;
				}
				oePntr = oePntr->next;
				cellEntryCount--;
			}
		}
		else
		{
			currCell->entityCount = 0;
			currCell->entity = NP_NULL;
		}
	}

	void npUniformGrid::updateEntityInCell(const npVector3ui &_cellPos,
		const npAabb &_volume,
		const int &_id)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		npObjectEntity* oePntr = currCell->entity;
		int cellEntryCount = currCell->entityCount;
		while (cellEntryCount > 0)
		{
			if (oePntr->id == _id) {
				break;
			}
			oePntr = oePntr->next;
		}
		oePntr->bbox = _volume;
	}

	void npUniformGrid::insert(const npAabb &_volume, const int &_bodyIdx)
	{
		npVector3ui cellIdx = getLocationIndex(_volume.getTopLeft());
		npObjectEntity* objE = new npObjectEntity(_volume, _bodyIdx);
		addEntityToCell(cellIdx, objE);
	}

	void npUniformGrid::update(const npAabbUpdateData &_volume, const int &_bodyIdx)
	{
		npVector3ui oldCellIdx = getLocationIndex(_volume.originalAabb.getTopLeft());
		npAabb updatedAabb(_volume.originalAabb.m_minVec + _volume.directionDiff,
			_volume.originalAabb.m_maxVec + _volume.directionDiff);
		npVector3ui newCellIdx = getLocationIndex(updatedAabb.getTopLeft());

		if (oldCellIdx != newCellIdx)
		{
			removeEntityFromCell(oldCellIdx, _bodyIdx);

			npObjectEntity* objE = new npObjectEntity(updatedAabb, _bodyIdx);
			addEntityToCell(newCellIdx, objE);
		}
		else
		{
			updateEntityInCell(newCellIdx, updatedAabb, _bodyIdx);
		}

		m_activeCellIds.push_back(newCellIdx);
	}

	bool npUniformGrid::remove(const npAabb &_volume, const int &_bodyIdx)
	{
		npVector3ui cellPos = getLocationIndex(_volume.getTopLeft());
		removeEntityFromCell(cellPos, _bodyIdx);
		return true;
	}

	void npUniformGrid::getPotentialContacts(npPairManager* _pairManager)
	{
		for (int i = 0; i < m_activeCellIds.size(); i++)
		{
			npVector3ui cellIdx = m_activeCellIds.at(i);
			npCell* activeCell = &m_cells[cellIdx.x][cellIdx.y][cellIdx.z];

			int entityCount = activeCell->entityCount;
			npObjectEntity* activeOE = activeCell->entity;
			while (entityCount > 0)
			{
				//Check own cell
				processCellOwnCell(activeCell, activeOE, _pairManager);

				//check neighbours
				while (true) {
					//SW - same z axis
					processCell(&m_cells[cellIdx.x - 1][cellIdx.y + 1][cellIdx.z], activeOE, _pairManager);

					//E border
					if (activeOE->bbox.m_maxVec.x > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x))
						processCell(&m_cells[cellIdx.x + 1][cellIdx.y][cellIdx.z], activeOE, _pairManager);

					//S border
					if (activeOE->bbox.m_minVec.y < getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y))
					{
						processCell(&m_cells[cellIdx.x][cellIdx.y + 1][cellIdx.z], activeOE, _pairManager);
						//SE border
						if (activeOE->bbox.m_maxVec.x > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x))
							processCell(&m_cells[cellIdx.x + 1][cellIdx.y + 1][cellIdx.z], activeOE, _pairManager);
					}

					//Back border
					if (activeOE->bbox.m_maxVec.z > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z))
					{
						cellIdx.z++;
						processCell(&m_cells[cellIdx.x][cellIdx.y][cellIdx.z], activeOE, _pairManager);
					}
					else
						break;
				}

				activeOE = activeOE->next;
				entityCount--;
			}

			
		}
		m_activeCellIds.clear();
	}

	npUniformGrid::npUniformGrid(const int &_gridSize, const npVector3r &_cellSize)
	{
		//Init
		m_xExtent = 100;
		m_yExtent = 100;
		m_zExtent = 100;

		m_cellSize = _cellSize;

		m_origin = npVector3r(
			-(_cellSize.x * (_gridSize / 2)) + (_cellSize.x / 2),
			-(_cellSize.y * (_gridSize / 2)) + (_cellSize.y / 2),
			-(_cellSize.z * (_gridSize / 2)) + (_cellSize.z / 2)
		);

		generateCells();
		m_activeCellIds = npAlignedArray<npVector3ui>();
	}

	npUniformGrid::~npUniformGrid()
	{
		for (unsigned int x = 0; x < m_xExtent; ++x) {
			m_cells[x] = new npCell*[m_yExtent];
			for (unsigned int y = 0; y < m_yExtent; ++y) {
				m_cells[x][y] = new npCell[m_zExtent];
				for (unsigned int z = 0; z < m_zExtent; ++z) {
					m_cells[x][y][z] = NP_NULL;
				}
			}
		}
		m_activeCellIds.clear();
	}
}