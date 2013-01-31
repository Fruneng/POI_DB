// Copyright 2012, Cheng Chu.  All rights reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Cheng Chu (zunceng at gmail dot com)
#ifndef __POIDB_HPP__
#define __POIDB_HPP__

#include <iostream>
#include <list>
#include <time.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "GridTree.hpp"
#include "TreeNode.hpp"

namespace POIDB
{

	struct HashGridTreeKeyFunc;
	struct HashGridTreeKey_equal_to;
	struct HashPOIDataFunc;
	struct HashPOIDataPtr_equal_to;
	struct HashGridTreeKey;
	class GridTree;

	typedef boost::unordered_set<
		POIDataPtr,
		HashPOIDataFunc,
		HashPOIDataPtr_equal_to,
		std::allocator<POIDataPtr>
	> POIDataMap;

	typedef boost::unordered_map<
		HashGridTreeKey,
		GridTreePtr,
		HashGridTreeKeyFunc,
		HashGridTreeKey_equal_to,
		std::allocator<std::pair<HashGridTreeKey, GridTreePtr> >
	> POIDataIndex;

	class POITable
	{
	public:
		POITable(){}

		void insert(double lng, double lat, int exptime, const std::string& key, const std::string& value);

		void remove(const std::string& key);

		bool find(const GridKey& key, std::list<POIData_o>& poi_data_list);

		bool find(const std::string& key, POIData_o& poi_data);

		void runtimeReleaesMemory();

		void clear();

	protected:

		POIDataIndex::iterator POIDataIndexFindandCreate(HashGridTreeKey key);

		void checkTimeandCopytoOutput(
				const std::vector<POIDataPtr>& poi_data_vec,
				std::list<POIData_o>& output);

		bool checkTimeandCopytoOutput(
				const POIDataPtr& poi_data_ptr,
				POIData_o& output);
	
	private:
		POIDataMap		poi_data_map;
		POIDataIndex	poi_data_index;
	};// end of class POIDB


}// end of namespace POIDB
#endif // end of __POIDB_HPP__
