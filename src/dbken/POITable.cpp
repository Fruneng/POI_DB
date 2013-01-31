/*
 * POITable.cpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#include "POITable.hpp"

namespace POIDB
{
	void POITable::insert(double lng, double lat, int exptime, const std::string& key, const std::string& value)
	{
		POIDataPtr poi_data_ptr = POIDataPtr(new POIData(key));
		time_t now;
		time(&now);

		POIDataMap::iterator it = poi_data_map.find(poi_data_ptr);
		if (it != poi_data_map.end())
		{
			POIDataPtr ptr = POIDataPtr(new POIData);
			ptr->key = key;
			(*it)->leaf_node->deleteData(ptr);

			(*it)->value = value;
			(*it)->lng = lng;
			(*it)->lat = lat;
			(*it)->exptime = exptime;
			(*it)->time = now;

			HashGridTreeKey index_key(lng, lat);

			POIDataIndexFindandCreate(index_key)->second->insert(*it);
		}
		else
		{
			poi_data_ptr->value = value;
			poi_data_ptr->lng = lng;
			poi_data_ptr->lat = lat;
			poi_data_ptr->exptime = exptime;
			poi_data_ptr->time = now;

			poi_data_map.insert(poi_data_ptr);

			HashGridTreeKey index_key(lng, lat);

			POIDataIndexFindandCreate(index_key)->second->insert(poi_data_ptr);
		}
	}

	void POITable::remove(const std::string& key)
	{
		POIDataPtr poi_data_ptr(new POIData(key));
		POIDataMap::iterator it = poi_data_map.find(poi_data_ptr);

		if (it != poi_data_map.end())
		{
			(*it)->leaf_node->deleteData(poi_data_ptr);
			poi_data_map.erase(it);
		}
	}

	bool POITable::find(const GridKey& key, std::list<POIData_o>& poi_data_list)
	{
		bool ret;
		POIDataIndex::iterator it = poi_data_index.find(key.toHashGridKey());

		if (it != poi_data_index.end())
		{
			std::vector<POIDataPtr> poi_data_vec;
			ret = it->second->getPOIs(key.x, key.y, key.z,poi_data_vec);

			if(ret)
			{
				checkTimeandCopytoOutput(poi_data_vec, poi_data_list);
			}
		}
		else
		{
			ret = false;
		}

		return ret;
	}

	bool POITable::find(const std::string& key, POIData_o& poi_data)
	{
		POIDataPtr poi_data_key(new POIData(key));
		POIDataMap::iterator it = poi_data_map.find(poi_data_key);
		if (it != poi_data_map.end())
		{
			if(!checkTimeandCopytoOutput(*it, poi_data))
			{
				return true;
			}
		}
		return false;
	}

	void POITable::runtimeReleaesMemory()
	{
		POIDataIndex::iterator it = poi_data_index.begin();
		for (;it != poi_data_index.end();)
		{
			if (it->second->size() == 0)
			{
				poi_data_index.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}

	void POITable::clear()
	{
		poi_data_map.clear();
		poi_data_index.clear();
	}

	POIDataIndex::iterator POITable::POIDataIndexFindandCreate(HashGridTreeKey key)
	{
		POIDataIndex::iterator it = poi_data_index.find(key);

		if (it == poi_data_index.end())
		{
			boost::shared_ptr<GridTree> gridtree_ptr(new GridTree(key.x, key.y));
			it = poi_data_index.insert(std::make_pair(key, gridtree_ptr)).first;
		}

		return it;
	}

	void POITable::checkTimeandCopytoOutput(
			const std::vector<POIDataPtr>& poi_data_vec,
			std::list<POIData_o>& output)
	{
		time_t now;
		time(&now);

		std::vector<POIDataPtr>::const_iterator it = poi_data_vec.begin();
		for (;it != poi_data_vec.end(); it++)
		{
			if((*it)->isOverTime(now))
			{
				(*it)->leaf_node->deleteData(*it);
				poi_data_map.erase(*it);
			}
			else
			{
				output.push_back(**it);
			}
		}
	}

	bool POITable::checkTimeandCopytoOutput(
			const POIDataPtr& poi_data_ptr, POIData_o& output)
	{
		time_t now;
		time(&now);

		if (poi_data_ptr->isOverTime(now))
		{
			return false;
		}
		else
		{
			output = *poi_data_ptr;
			return true;
		}
	}

}// end of namespace POIDB
