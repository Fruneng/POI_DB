// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)

#ifndef __TREE_NODE_HPP__
#define __TREE_NODE_HPP__
#include <iostream>
#include <assert.h>
#include "POITable.hpp"
#include "base/gridfunc.hpp"

#include <vector>
#include <set>
#include <boost/unordered_set.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/functional/hash.hpp>


namespace POIDB
{

class GridTree;
struct Node;
struct POIData;
struct HashPOIDataFunc;
struct HashPOIDataPtr_equal_to;

enum{_minz = 11, _maxz = 16};

struct POIData
{
	double lng;
	double lat;
	time_t time;
	int exptime;
	std::string key;
	std::string value;
	Node* leaf_node;

	POIData() : leaf_node(NULL)
	{

	}

	POIData(const std::string &_key) : leaf_node(NULL), key(_key)
	{

	}

	bool operator ==(const POIData& rhs)
	{
		return key == rhs.key;
	}

	bool operator <(const POIData& rhs)
	{
		return key < rhs.key;
	}

	bool isOverTime(time_t t)
	{
		return time + exptime < t;
	}
};

typedef boost::shared_ptr<POIData> POIDataPtr;

struct HashPOIDataFunc
	: std::unary_function<POIDataPtr, std::size_t>
{
	HashPOIDataFunc() 
	{

	}

	std::size_t operator()(POIDataPtr const& x) const
	{
		return boost::hash_value(x->key);
	}
};

struct POIDataPtrLess
{
	POIDataPtrLess() 
	{

	}

	bool operator()(POIDataPtr const& lhs, POIDataPtr const& rhs) const
	{
		return lhs->key < rhs->key;
	}
};

struct HashPOIDataPtr_equal_to
{
	HashPOIDataPtr_equal_to()
	{

	}

	bool operator () (const POIDataPtr& lhs, const POIDataPtr& rhs) const
	{
		return lhs->key == rhs->key;
	}
};

struct POIData_o{
	double lng;
	double lat;
	time_t time;
	std::string key;
	std::string value;

	POIData_o(){}

	POIData_o(const POIData& poi_data)
	{
		lng = poi_data.lng;
		lat = poi_data.lat;
		time = poi_data.time;
		key = poi_data.key;
		value = poi_data.value;
	}

	POIData_o operator =(const POIData& poi_data)
	{
		lng = poi_data.lng;
		lat = poi_data.lat;
		time = poi_data.time;
		key = poi_data.key;
		value = poi_data.value;
		return *this;
	}
};

typedef boost::unordered_set<
	POIDataPtr,
	HashPOIDataFunc,
	HashPOIDataPtr_equal_to,
	std::allocator<POIDataPtr>
> POISet;

//typedef std::set<
//	POIDataPtr,
//	POIDataPtrLess,
//	std::allocator<POIDataPtr>
//> POISet;

struct Node{
	int x;
	int y;
	int z;

	Node* child[2][2];
	GridTree* pTree;

	POISet *poi_set;

	Node(int _x,int _y,int _z, GridTree* _pTree):
	x(_x), y(_y), z(_z), poi_set(NULL), pTree(_pTree)
	{
		if (z == _maxz)
		{
			poi_set = new POISet();
		}
	}

	bool equalto(int _x, int _y)
	{
		return x == _x && y == _y;
	}

	bool getPOIs(std::vector<POIDataPtr>& ret)
	{
		if(z == _maxz)
		{
			ret.insert(ret.end(), poi_set->begin(), poi_set->end());
		}
		else
		{
			child[0][0]->getPOIs(ret);
			child[0][1]->getPOIs(ret);
			child[1][0]->getPOIs(ret);
			child[1][1]->getPOIs(ret);
		}
		return true;
	}

	bool insert(POIDataPtr poi_data_ptr)
	{
		poi_data_ptr->leaf_node = this;

		assert(poi_set != NULL);

		assert(isExist(poi_data_ptr));

		poi_set->insert(poi_data_ptr);

		//POISet::iterator it = poi_set->find(poi_data_ptr);
		//if (it != poi_set->end())
		//{
		//	//*it = poi_data_ptr;
		//	return false;
		//}
		//else
		//{
		//	poi_set->insert(poi_data_ptr);		
		//}
		return true;
	}

	bool deleteData(POIDataPtr poi_data_ptr)
	{
		assert(poi_set != NULL);
		
		assert(!isExist(poi_data_ptr));

		POISet::iterator it = poi_set->find(poi_data_ptr);
		if (it != poi_set->end())
		{
			(*it)->leaf_node = NULL;
			poi_set->erase(it);
			return true;
		}
		
		return false;
	}

	bool isExist(POIDataPtr poi_data_ptr)
	{
		POISet::iterator it = poi_set->find(poi_data_ptr);
		if (it != poi_set->end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	size_t size() const
	{
		if(z == _maxz)
		{
			return poi_set->size();
		}
		else
		{
			size_t si = child[0][0]->size();
			si += child[0][1]->size();
			si += child[1][0]->size();
			si += child[1][1]->size();
			return si;
		}
	}
};

}//end POIDB

#endif
