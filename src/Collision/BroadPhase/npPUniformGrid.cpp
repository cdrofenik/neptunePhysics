#include "Collision\BroadPhase\npPUniformGrid.h"

#include <iostream>

namespace NeptunePhysics
{
	inline static npReal getCellBorder(const npReal &_origin, const npReal &_size, const int _index)
	{
		return _origin + (_size * _index) + _size / 2;
	}

	void npPUniformGrid::printGrid()
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

	void npPUniformGrid::generateCells()
	{

	}

	npVector3ui npPUniformGrid::getLocationIndex(const npVector3r & _centerPos) const
	{
		unsigned int xCellIdx = static_cast<unsigned int>(floor((_centerPos.x - m_origin.x) / m_cellSize.x));
		unsigned int yCellIdx = static_cast<unsigned int>(floor((_centerPos.y - m_origin.y) / m_cellSize.y));
		unsigned int zCellIdx = static_cast<unsigned int>(floor((_centerPos.z - m_origin.z) / m_cellSize.z));

		return npVector3ui(xCellIdx, yCellIdx, zCellIdx);
	}

	void npPUniformGrid::insertCellBorderEnity(const npVector3ui &_cellPos, npObjectEntity * _oEntity)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		if (currCell->borderEntitiesCount > 0)
		{
			npObjectEntity* oePntr = currCell->borderEntity;
			int cellBorderCount = currCell->borderEntitiesCount;
			while (cellBorderCount > 0)
			{
				if (cellBorderCount == 1) {
					break;
				}
				else {
					oePntr = oePntr->next;
					cellBorderCount--;
				}
			}

			_oEntity->previous = oePntr;
			oePntr->next = _oEntity;
			currCell->borderEntitiesCount++;
		}
		else
		{
			currCell->borderEntity = _oEntity;
			currCell->borderEntitiesCount++;
		}
	}

	void npPUniformGrid::updateCellBorderEntity(const npVector3ui & _cellPos, const npSphere & _volume, const int & _id)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		npObjectEntity* oePntr = currCell->borderEntity;
		int cellEntryCount = currCell->borderEntitiesCount;
		while (cellEntryCount > 0)
		{
			if (oePntr->id == _id) {
				break;
			}
			oePntr = oePntr->next;
		}
		oePntr->bSphere = _volume;
	}

	void npPUniformGrid::removeCellBorderEnity(const npVector3ui & _cellPos, const int & _data)
	{
		npCell* currCell = &m_cells[_cellPos.x][_cellPos.y][_cellPos.z];
		if (currCell->entityCount > 1)
		{
			npObjectEntity* oePntr = currCell->borderEntity;
			int cellEntryCount = currCell->borderEntitiesCount;
			while (cellEntryCount > 0)
			{
				if (oePntr->id == _data) {
					if (cellEntryCount > 1) {
						oePntr->bSphere = oePntr->next->bSphere;
						oePntr->id = oePntr->next->id;
						oePntr->next = oePntr->next->next;

						oePntr = NP_NULL;
					}
					else {
						oePntr = NP_NULL;
					}
					currCell->borderEntitiesCount--;
					return;
				}
				oePntr = oePntr->next;
				cellEntryCount--;
			}
		}
		else
		{
			currCell->borderEntitiesCount = 0;
			currCell->borderEntity = NP_NULL;
		}
	}

	void npPUniformGrid::addEntityToCell(const npVector3ui & _cellPos, npObjectEntity * _oEntity)
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

	void npPUniformGrid::removeEntityFromCell(const npVector3ui & _cellPos, const int & _data)
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
						oePntr->bSphere = oePntr->next->bSphere;
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

	void npPUniformGrid::updateEntityInCell(const npVector3ui & _cellPos, const npSphere & _volume, const int & _id)
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
		oePntr->bSphere = _volume;
	}

	#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
	#define SET_BIT(var, pos) ((var) + (1<<(pos)))

	void npPUniformGrid::insert(const npAabb &_volume, const int &_bodyIdx)
	{
		npSphere boundingSphere = _volume.getBoundingSphere();
		npVector3ui cellIdx = getLocationIndex(boundingSphere.center);
		npObjectEntity* objE = new npObjectEntity(boundingSphere, _bodyIdx);

		//Insert element in proper cell based on centroid
		addEntityToCell(cellIdx, objE);


		//check if element crosses any cell borders
		int checkFlag = 0;
		unsigned int zAxis = cellIdx.z;
		int passCount = 0;
		while (passCount < 2) {

			//check N border
			if (CHECK_BIT(checkFlag, 3) ||
				(objE->bSphere.getMax(1) > getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y + 1)))
			{
				insertCellBorderEnity(npVector3ui(cellIdx.x, cellIdx.y + 1, zAxis), objE);
				SET_BIT(checkFlag, 3);
			}
			
			//check S border
			if (CHECK_BIT(checkFlag, 1) ||
				(objE->bSphere.getMin(1) > getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y)))
			{
				insertCellBorderEnity(npVector3ui(cellIdx.x, cellIdx.y - 1, zAxis), objE);
				SET_BIT(checkFlag, 1);
			}

			//check E border
			if (CHECK_BIT(checkFlag, 0) ||
				(objE->bSphere.getMax(0) > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x + 1)))
			{
				insertCellBorderEnity(npVector3ui(cellIdx.x + 1, cellIdx.y, zAxis), objE);
				SET_BIT(checkFlag, 0);
			}

			//check W border
			if (CHECK_BIT(checkFlag, 2) ||
				(objE->bSphere.getMin(0) > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x)))
			{
				insertCellBorderEnity(npVector3ui(cellIdx.x - 1, cellIdx.y, zAxis), objE);
				SET_BIT(checkFlag, 2);
			}

			//// NW
			//if(CHECK_BIT(checkFlag, 3) && CHECK_BIT(checkFlag, 2))
			//	addToCellBorderList();

			//// NE
			//if (CHECK_BIT(checkFlag, 3) && CHECK_BIT(checkFlag, 0))
			//	addToCellBorderList();

			//// SW
			//if (CHECK_BIT(checkFlag, 1) && CHECK_BIT(checkFlag, 2))
			//	addToCellBorderList();

			//// SE
			//if (CHECK_BIT(checkFlag, 1) && CHECK_BIT(checkFlag, 0))
			//	addToCellBorderList();

			// Front
			if (objE->bSphere.getMin(2) > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z + 1))
			{
				zAxis++;
				insertCellBorderEnity(npVector3ui(cellIdx.x, cellIdx.y, zAxis), objE);
			}

			//Back
			if ((objE->bSphere.getMax(2) > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z)))
			{
				zAxis--;
				insertCellBorderEnity(npVector3ui(cellIdx.x, cellIdx.y, zAxis), objE);
			}

			passCount++;
		}
	}

	void npPUniformGrid::update(const npAabbUpdateData &_volumeData, const int &_bodyIdx)
	{
		npVector3ui oldCellIdx = getLocationIndex(_volumeData.originalAabb.getTopLeft());
		npAabb updatedAabb(_volumeData.originalAabb.m_minVec + _volumeData.directionDiff,
			_volumeData.originalAabb.m_maxVec + _volumeData.directionDiff);
		npVector3ui newCellIdx = getLocationIndex(updatedAabb.getTopLeft());
		
		remove(_volumeData.originalAabb, _bodyIdx);
		insert(updatedAabb, _bodyIdx);

		m_activeCellIds.push_back(newCellIdx);
	}

	bool npPUniformGrid::remove(const npAabb &_volume, const int &_bodyIdx)
	{
		npVector3ui cellPos = getLocationIndex(_volume.getTopLeft());
		removeEntityFromCell(cellPos, _bodyIdx);

		//check if element crosses any cell borders
		int checkFlag = 0;
		unsigned int zAxis = cellPos.z - 1;
		int passCount = 0;
		while (passCount < 2) {

			removeCellBorderEnity(npVector3ui(cellPos.x, cellPos.y + 1, cellPos.z), _bodyIdx);
			removeCellBorderEnity(npVector3ui(cellPos.x, cellPos.y - 1, cellPos.z), _bodyIdx);
			removeCellBorderEnity(npVector3ui(cellPos.x + 1, cellPos.y, cellPos.z), _bodyIdx);
			removeCellBorderEnity(npVector3ui(cellPos.x - 1, cellPos.y, cellPos.z), _bodyIdx);

			//NE
			removeCellBorderEnity(npVector3ui(cellPos.x + 1, cellPos.y + 1, cellPos.z), _bodyIdx);
			
			//SE
			removeCellBorderEnity(npVector3ui(cellPos.x + 1, cellPos.y - 1, cellPos.z), _bodyIdx);
			
			//NW
			removeCellBorderEnity(npVector3ui(cellPos.x - 1, cellPos.y + 1, cellPos.z), _bodyIdx);
			
			//SW
			removeCellBorderEnity(npVector3ui(cellPos.x - 1, cellPos.y - 1, cellPos.z), _bodyIdx);

			zAxis += 2;
			passCount++;
		}

		removeCellBorderEnity(npVector3ui(cellPos.x, cellPos.y, cellPos.z + 1), _bodyIdx);
		removeCellBorderEnity(npVector3ui(cellPos.x, cellPos.y, cellPos.z - 1), _bodyIdx);

		return true;
	}

	void npPUniformGrid::getPotentialContacts(npPairManager* _pairManager)
	{
		//TODO: parallel magic!

		//Based on activeCellIds size generate dim element for blocks/threads for CUDA

		//copy data to working elements

		//do work

		//copy data back to result elements
	}

	npPUniformGrid::npPUniformGrid(const int &_gridSize, const npVector3r &_cellSize)
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

	npPUniformGrid::~npPUniformGrid()
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