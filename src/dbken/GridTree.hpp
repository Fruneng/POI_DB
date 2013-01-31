// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __GRID_TREE_HPP__
#define __GRID_TREE_HPP__
#include <iostream>
#include <assert.h>
#include "POITable.hpp"
#include "TreeNode.hpp"
#include "base/gridfunc.hpp"

#include "base/Timer.hpp"

#include <vector>
#include <set>
#include <boost/unordered_set.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/functional/hash.hpp>


namespace POIDB
{

class GridTree;
struct POIData;

struct HashPOIDataFunc;
struct HashPOIDataPtr_equal_to;

struct POIDataPtrLess; 

class GridTree
{
	
public:
	GridTree(int x, int y)
	{
		Timer timer;

		timer.start();
		build(x, y, _minz, _maxz);
		timer.finish();

		std::cout << "cost: " << timer << "ms" << std::endl;
	}

	~GridTree()
	{
		deleteNode(head, _maxz);
	}


	bool getPOIs(int _x, int _y, int _z, std::vector<POIDataPtr>& ret)
	{
		assert(_z >= _minz && _z <= _maxz);
		Node *node = find(_x, _y, _z);
		return node->getPOIs(ret);
	}

	bool insert(POIDataPtr poi_data_ptr)
	{
		int x = CCTool::GridFunc::getTileNumberX(_maxz, poi_data_ptr->lng);
		int y = CCTool::GridFunc::getTileNumberY(_maxz, poi_data_ptr->lat);
		Node *node = find(x, y, _maxz);

		return node->insert(poi_data_ptr);
	}

	bool remove(POIDataPtr poi_data_ptr)
	{
		int x = CCTool::GridFunc::getTileNumberX(_maxz, poi_data_ptr->lng);
		int y = CCTool::GridFunc::getTileNumberY(_maxz, poi_data_ptr->lat);
		Node *node = find(x, y, _maxz);

		return node->deleteData(poi_data_ptr);
	}

	size_t size() const
	{
		return head->size();
	}

	int getX() const { return head->x;}
	int getY() const { return head->y;}

protected:

	void build(int x, int y, int minz, int maxz)
	{
		head = new Node(x, y, minz, this);
		GeneNode(head, maxz);
	}
	
	void GeneNode(Node* pNode, int maxz)
	{
		if(pNode->z >= maxz)
		{
			return;
		}

		for (int i = 0 ;i < 2 ; i++)
			for (int j = 0 ; j < 2; j++)
			{
				pNode->child[i][j] = new Node(
					pNode->x * 2 + i,
					pNode->y * 2 + j,
					pNode->z + 1,
					this);
				GeneNode(pNode->child[i][j],maxz);
			}
	}

	void deleteNode(Node* pNode, int maxz)
	{
		if (pNode->z == maxz)
		{
			delete pNode;
			return;
		}

		for (int i = 0 ;i < 2 ; i++)
			for (int j = 0 ; j < 2; j++)
			{
				deleteNode(pNode->child[i][j], maxz);
			}
		delete pNode;
	}

	Node* find(int x, int y, int z)
	{
		assert(z >= _minz && z <= _maxz);
		assert(isBelongToThisTree(x, y, z));

		int tree_path[_maxz - _minz][2];

		for (int i = z - _minz - 1; i >= 0 ; i--)
		{
			tree_path[i][0] = x % 2;
			tree_path[i][1] = y % 2;

			x = x / 2;
			y = y / 2;
		}

		Node* tmp = head;
		for (int i = 0 ; i < z - _minz ; i++)
		{
			tmp = tmp->child[tree_path[i][0]][tree_path[i][1]];
		}
		return tmp;
	}

	bool isBelongToThisTree(int x, int y, int z)
	{
		assert(z >= _minz && z <= _maxz);
		
		int diff = z - _minz;

		if (diff > 0)
		{
			x = x >> diff;
			y = y >> diff;
		}
		return head->x == x && head->y == y;
	}

private:
	GridTree(const GridTree&);
	GridTree& operator = (const GridTree&);

	Node* head;
};


typedef boost::shared_ptr<GridTree> GridTreePtr;

struct HashGridTreeKey{
	size_t x;
	size_t y;

	HashGridTreeKey()
	{

	}
	HashGridTreeKey(double lng, double lat)
	{
		x = CCTool::GridFunc::getTileNumberX(_minz, lng);
		y = CCTool::GridFunc::getTileNumberY(_minz, lat);
	}
};

struct GridKey
{
	size_t x;
	size_t y;
	size_t z;

	GridKey(){}
	explicit GridKey(int _x, int _y ,int _z): x(_x), y(_y), z(_z){}
	explicit GridKey(double _lng, double _lat, int _z): z(_z)
	{
		assert(z >= _minz && z <= _maxz );
		x = CCTool::GridFunc::getTileNumberX(z, _lng);
		y = CCTool::GridFunc::getTileNumberY(z, _lat);
	}

	HashGridTreeKey toHashGridKey() const
	{
		assert(z >= _minz && z <= _maxz);

		HashGridTreeKey hash_grid_key;

		if (z == _minz)
		{
			hash_grid_key.x = x;
			hash_grid_key.y = y;
		}
		else
		{
			int offset = z - _minz;
			hash_grid_key.x = x >> offset;
			hash_grid_key.y = y >> offset;
		}
		return hash_grid_key;
	}
};

struct HashGridTreeKeyFunc
	: std::unary_function<HashGridTreeKey, std::size_t>
{
	HashGridTreeKeyFunc() 
	{

	}
	std::size_t operator()(HashGridTreeKey const& x) const
	{
		return boost::hash_value(x.x * 1024 * 64+ x.y);
	}
};

struct HashGridTreeKey_equal_to
{
	HashGridTreeKey_equal_to(){}

	bool operator () (const HashGridTreeKey& lhs, const HashGridTreeKey& rhs) const
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};

}//end of namespace POIDB

#endif// end of __GRID_TREE_HPP__
