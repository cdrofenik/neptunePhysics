#include "Collision/BroadPhase/npDbvt.h"

#include <iostream>

namespace NeptunePhysics {


	static int indexOf(const npDbvtNode* _node)
	{
		return (_node->parent->children[1] == _node);
	}

	static int selectLeaf(const npAabb &_volume, const npAabb &_leafVol1, const npAabb &_leafVol2)
	{
		return npProximityAabbAabb(_leafVol1, _volume) < npProximityAabbAabb(_leafVol2, _volume) ? 0 : 1;
	}

	static npDbvtNode* createNode(npDbvtNode* _parent, const npAabb &_volume, const int &_bodyIdx)
	{
		npDbvtNode* node = new npDbvtNode();
		node->parent = _parent;
		node->volume = _volume;
		node->bodyIdx = _bodyIdx;
		node->children[1] = 0;
		return (node);
	}

	static npDbvtNode* createInternalNode(npDbvtNode* _parent,
		const npAabb &_volume1,
		const npAabb &_volume2,
		const int &_bodyIdx)
	{
		npDbvtNode* node = createNode(_parent, _volume1, _bodyIdx);
		npMergeAabbAabb(_volume1, _volume2, node->volume);
		return node;
	}

	static void insertLeaf(npDbvt* _pdbvt, npDbvtNode* _root, npDbvtNode* _leaf)
	{
		//Is tree root set
		if (!_pdbvt->m_root) {
			_pdbvt->m_root = _leaf;
			_leaf->parent = 0;
		}
		else
		{
			//is root an internal node
			if (!_root->isLeaf())
			{
				do {
					_root = _root->children[selectLeaf(_leaf->volume,
						_root->children[0]->volume,
						_root->children[1]->volume)];
				} while (!_root->isLeaf());
			}
			npDbvtNode* previous = _root->parent;
			npDbvtNode* newInternalNode = createInternalNode(previous,
				_leaf->volume, _root->volume, 0);

			//does parent exist
			if (previous) {
				previous->children[indexOf(_root)] = newInternalNode;
				newInternalNode->children[0] = _root;
				_root->parent = newInternalNode;
				newInternalNode->children[1] = _leaf;
				_leaf->parent = newInternalNode;
				do {
					if (!previous->volume.contains(newInternalNode->volume))
						npMergeAabbAabb(previous->children[0]->volume, previous->children[1]->volume, previous->volume);
					else
						break;

					newInternalNode = previous;
				} while (0 != (previous = newInternalNode->parent));
			}
			else{
				newInternalNode->children[0] = _root;
				_root->parent = newInternalNode;
				newInternalNode->children[1] = _leaf;
				_leaf->parent = newInternalNode;
				_pdbvt->m_root = newInternalNode;
			}
		}
	}

	static void recursivlyDeleteNode(npDbvtNode* _node)
	{
		if (_node->isInternal()) {
			recursivlyDeleteNode(_node->children[0]);
			recursivlyDeleteNode(_node->children[1]);
		}
		else {
			delete _node;
		}
	}

	static bool removeNode(npDbvt* _pdbvt, npDbvtNode* _node, const npAabb &_volume, const int &_id)
	{
		npDbvtNode* currentNode = _node;
		int childIndex = -1;

		do {
			childIndex = selectLeaf(_volume,
				currentNode->children[0]->volume,
				currentNode->children[1]->volume);
			currentNode = currentNode->children[childIndex];
		} while (!currentNode->isLeaf());
		
		if (currentNode->bodyIdx == _id) {
			npDbvtNode* parent = currentNode->parent;
			auto vol = parent->children[!childIndex]->volume;
			auto idx = parent->children[!childIndex]->bodyIdx;
			parent->volume = parent->children[!childIndex]->volume;
			parent->bodyIdx = parent->children[!childIndex]->bodyIdx;
			parent->children[0] = parent->children[!childIndex]->children[0];
			parent->children[1] = parent->children[!childIndex]->children[1];

			return true;
		}
		else {
			return false;
		}
	}
	
	static void printLeafOrNode(npDbvtNode* _node)
	{
		if (_node->isLeaf()) {
			std::cout << "\\LEAF!" << std::endl;
		}
		else {
			std::cout << "\\NODE - LEFT!" << std::endl;
			printLeafOrNode(_node->children[0]);


			std::cout << "\\NODE - RIGHT" << std::endl;
			printLeafOrNode(_node->children[1]);
		}
	}

	static void checkCollision(npPairManager* _pairManager, npDbvtNode* a, npDbvtNode* b, const int &limit)
	{
		if (!npTestAabbAabb(a->volume, b->volume))
		{
			if (limit == 0)
				return;
			else {
				if (a->isInternal())
					checkCollision(_pairManager, a->children[0], a->children[1], limit - 1);

				if (b->isInternal())
					checkCollision(_pairManager, b->children[0], b->children[1], limit - 1);

				return;
			}
		}
		if (a->isLeaf() && b->isLeaf())
		{
			//add leaves to potential contacts
			_pairManager->addPair(a->bodyIdx, b->bodyIdx);
		}
		else
		{
			if (!a->isLeaf())
			{
				checkCollision(_pairManager, a->children[0], b, limit - 1);
				checkCollision(_pairManager, a->children[1], b, limit - 1);
			}
			else
			{
				checkCollision(_pairManager, a, b->children[0], limit - 1);
				checkCollision(_pairManager, a, b->children[1], limit - 1);
			}

		}
	}

	void npDbvt::clean() {
		recursivlyDeleteNode(m_root);
		m_root = 0;
	}

	void npDbvt::insert(const npAabb &_volume, const int &_bodyIdx)
	{
		npDbvtNode* newNode = createNode(0, _volume, _bodyIdx);
		insertLeaf(this, m_root, newNode);
		++m_leaves;
	}

	void npDbvt::update(const npAabbUpdateData &_volumeData, const int &_bodyIdx)
	{
		if (remove(_volumeData.originalAabb, _bodyIdx)) {
			npAabb aabb(_volumeData.originalAabb.m_minVec + _volumeData.directionDiff,
				_volumeData.originalAabb.m_maxVec + _volumeData.directionDiff);

			insert(aabb, _bodyIdx);
		}
	}

	bool npDbvt::remove(const npAabb &_volume, const int &_bodyIdx)
	{
		bool result = removeNode(this, m_root, _volume, _bodyIdx);
		if (result)
			m_leaves--;

		return result;
	}

	void npDbvt::getPotentialContacts(npPairManager* _pairManager)
	{
		int limit = 3;
		checkCollision(_pairManager, m_root->children[0], m_root->children[1], limit);
	}

	void npDbvt::DebugPrintTree()
	{
		if (!m_root) {
			return;
		}

		printLeafOrNode(m_root);

	}

	npDbvt::npDbvt()
	{
		m_root = 0;
		m_leaves = 0;
	}

	npDbvt::~npDbvt()
	{
		clean();
	}
}