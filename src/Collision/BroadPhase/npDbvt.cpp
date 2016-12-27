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

	static npDbvtNode* fetchNode(npDbvt* _pdbvt, npDbvtNode* _node, const npAabb &_volume)
	{
		npDbvtNode* currentParent = _node;
		do {
			auto val = selectLeaf(_volume,
				currentParent->children[0]->volume,
				currentParent->children[1]->volume);
			currentParent = currentParent->children[val];
		} while (!currentParent->isLeaf());

		return (currentParent->volume.isEqual(_volume)) ? currentParent : NP_NULL;
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

	static void removeNodeFromTree(npDbvt* _pdbvt, npDbvtNode* _node)
	{
		if (!_pdbvt->m_root)
		{
			return;
		}

		npDbvtNode* prnt = _node->parent;
		npDbvtNode* activeSibling = (prnt->children[0] == _node) ?
			prnt->children[1] : prnt->children[0];

		if (activeSibling)
		{
			npDbvtNode* pNode = createNode(prnt->parent,
				activeSibling->volume, activeSibling->bodyIdx);
			
			if (pNode->parent == _pdbvt->m_root->parent)
			{
				_pdbvt->m_root = pNode;
			}
			else
			{
				//TODO test if works
				prnt = pNode;
				prnt->children[1] = 0;
				prnt->bodyIdx = activeSibling->bodyIdx;
				prnt->volume = activeSibling->volume;
				activeSibling->parent = prnt;
			}
		}
	}

	static void DbvtCollision(npPairManager** _pairManager, npDbvtNode* a, npDbvtNode* b)
	{
		if (!npTestAabbAabb(a->volume, b->volume)) return;
		if (a->isLeaf() && b->isLeaf())
		{
			//add leaves to potential contacts
			npPairManager* ref = *_pairManager;
			ref->addPair(a->bodyIdx, b->bodyIdx);
		}
		else
		{
			if (!a->isLeaf())
			{
				DbvtCollision(_pairManager, a->children[0], b);
				DbvtCollision(_pairManager, a->children[1], b);
			}
			else
			{
				DbvtCollision(_pairManager, a, b->children[0]);
				DbvtCollision(_pairManager, a, b->children[1]);
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
		auto node = fetchNode(this, m_root, _volumeData.originalAabb);
		if (node) {
			removeNodeFromTree(this, node);

			npAabb aabb(_volumeData.originalAabb.m_minVec + _volumeData.directionDiff,
				_volumeData.originalAabb.m_maxVec + _volumeData.directionDiff);

			insert(aabb, node->bodyIdx);
		}
	}

	void npDbvt::remove(const npAabb &_volume, const int &_bodyIdx)
	{
		//TODO: implement
	}

	void npDbvt::getPotentialContacts(npPairManager** _pairManager)
	{
		DbvtCollision(_pairManager, m_root->children[0], m_root->children[1]);
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