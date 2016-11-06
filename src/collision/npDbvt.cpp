#include "collision/npDbvt.h"

#include <iostream>

namespace NeptunePhysics {


	static int indexOf(const npDbvtNode* node)
	{
		return (node->parent->children[1] == node);
	}

	static int selectLeaf(const npAabb& volume, const npAabb& leafVol1, const npAabb& leafVol2)
	{
		return npProximityAabbAabb(leafVol1, volume) < npProximityAabbAabb(leafVol2, volume) ? 0 : 1;
	}

	static npDbvtNode* createNode(npDbvtNode* parent, const npAabb& volume, void* data)
	{
		npDbvtNode* node = new npDbvtNode();
		node->parent = parent;
		node->volume = volume;
		node->data = data;
		node->children[1] = 0;
		return (node);
	}

	static npDbvtNode* createInternalNode(npDbvtNode* parent,
		const npAabb& volume1,
		const npAabb& volume2,
		void* data)
	{
		npDbvtNode* node = createNode(parent, volume1, data);
		npMergeAabbAabb(volume1, volume2, node->volume);
		return node;
	}

	static void insertLeaf(npDbvt* pdbvt, npDbvtNode* root, npDbvtNode* leaf)
	{
		//Is tree root set
		if (!pdbvt->m_root) {
			pdbvt->m_root = leaf;
			leaf->parent = 0;
		}
		else
		{
			//is root an internal node
			if (!root->isLeaf())
			{
				do {
					root = root->children[selectLeaf(leaf->volume,
						root->children[0]->volume,
						root->children[1]->volume)];
				} while (!root->isLeaf());
			}
			npDbvtNode* previous = root->parent;
			npDbvtNode* newInternalNode = createInternalNode(previous, leaf->volume, root->volume, 0);

			//does parent exist
			if (previous) {
				previous->children[indexOf(root)] = newInternalNode;
				newInternalNode->children[0] = root; root->parent = newInternalNode;
				newInternalNode->children[1] = leaf; leaf->parent = newInternalNode;
				do {
					if (!previous->volume.contains(newInternalNode->volume))
						npMergeAabbAabb(previous->children[0]->volume, previous->children[1]->volume, previous->volume);
					else
						break;

					newInternalNode = previous;
				} while (0 != (previous = newInternalNode->parent));
			}
			else{
				newInternalNode->children[0] = root;
				root->parent = newInternalNode;
				newInternalNode->children[1] = leaf;
				leaf->parent = newInternalNode;
				pdbvt->m_root = newInternalNode;
			}
		}
	}

	static void recursivlyDeleteNode(npDbvtNode* node)
	{
		if (node->isInternal()) {
			recursivlyDeleteNode(node->children[0]);
			recursivlyDeleteNode(node->children[1]);
		}
		else {
			delete node;
		}
	}

	static npDbvtNode* fetchNode(npDbvt* pdbvt, npDbvtNode* node, npAabb& volume)
	{
		npDbvtNode* currentParent = node;
		do {
			auto val =  selectLeaf(volume,
				currentParent->children[0]->volume,
				currentParent->children[1]->volume);
			currentParent = currentParent->children[val];
		} while (!currentParent->isLeaf());

		return (currentParent->volume.isEqual(volume)) ? currentParent : NP_NULL;
	}
	
	static void printLeafOrNode(npDbvtNode* node)
	{
		if (node->isLeaf()) {
			std::cout << "\\LEAF!" << std::endl;
		}
		else {
			std::cout << "\\NODE - LEFT!" << std::endl;
			printLeafOrNode(node->children[0]);


			std::cout << "\\NODE - RIGHT" << std::endl;
			printLeafOrNode(node->children[1]);
		}
	}

	static void removeNodeFromTree(npDbvt* pdbvt, npDbvtNode* node)
	{
		if (!pdbvt->m_root)
		{
			return;
		}

		npDbvtNode* prnt = node->parent;
		npDbvtNode* activeSibling = (prnt->children[0] == node) ?
			prnt->children[1] : prnt->children[0];

		if (activeSibling)
		{
			npDbvtNode* pNode = createNode(prnt->parent,
				activeSibling->volume, activeSibling->data);
			
			if (pNode->parent == pdbvt->m_root->parent)
			{
				pdbvt->m_root = pNode;
			}
			else
			{
				//TODO test if works
				prnt = pNode;
				prnt->children[1] = 0;
				prnt->data = activeSibling->data;
				prnt->volume = activeSibling->volume;
				activeSibling->parent = prnt;
			}
		}
	}

	static void DbvtCollision(npPotentialContact* contacts, npDbvtNode* a, npDbvtNode* b)
	{
		if (!npTestAabbAabb(a->volume, b->volume)) return;
		if (a->isLeaf() && b->isLeaf())
		{
			//add leaves to potential contacts
			contacts->bodyA = (npRigidBody*)a->data;
			contacts->bodyB = (npRigidBody*)b->data;
		}
		else
		{
			if (!a->isLeaf())
			{
				DbvtCollision(contacts, a->children[0], b);
				DbvtCollision(contacts, a->children[1], b);
			}
			else
			{
				DbvtCollision(contacts, a, b->children[0]);
				DbvtCollision(contacts, a, b->children[1]);
			}

		}
	}

	void npDbvt::clean() {
		recursivlyDeleteNode(m_root);
		m_root = 0;
	}

	void npDbvt::insert(const npAabb& volume, void* data)
	{
		npDbvtNode* newNode = createNode(0, volume, data);
		insertLeaf(this, m_root, newNode);
		++m_leaves;
	}

	void npDbvt::updateTree(std::vector<npAabbUpdateData> diffList)
	{
		for (size_t i = 0; i < diffList.size(); i++)
		{
			auto node = fetchNode(this, m_root, diffList[i].originalAabb);
			if (node) {
				removeNodeFromTree(this, node);

				npAabb aabb(diffList[i].originalAabb.m_minVec + diffList[i].directionDiff,
					diffList[i].originalAabb.m_maxVec + diffList[i].directionDiff);

				insert(aabb, node->data);
			}
		}
	}

	void npDbvt::getPotentialContacts(npPotentialContact* contacts)
	{
		DbvtCollision(contacts, m_root->children[0], m_root->children[1]);
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