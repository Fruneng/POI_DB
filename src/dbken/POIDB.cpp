/*
 * POIDB.cpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#include "POIDB.hpp"
#include "../Log.hpp"

namespace POIDB{

	int POIDB::CreateTable(const std::string& table)
	{
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it == _table_map.end())
		{
			POITablePtr new_table_ptr(new POITable());
			_table_map.insert(std::make_pair(table, new_table_ptr));

			LOG(INFO)<< "Create table " << table << " succeced";

			return 0;
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	int POIDB::DeleteTable(const std::string& table)
	{
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it != _table_map.end())
		{
			_table_map.erase(it);

			LOG(INFO)<< "Delete table " << table << "succeced";
			return 0;
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	int POIDB::insert(
			const std::string& table,
			double lng,
			double lat,
			int exptime,
			const std::string& key,
			const std::string& value
			)
	{
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it != _table_map.end())
		{
			it->second->insert(lng, lat, exptime, key, value);
			LOG(INFO)<< "insert succeced";
			return 0;
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	int POIDB::remove(
					const std::string& table,
					const std::string& key)
	{
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it != _table_map.end())
		{
			it->second->remove(key);
			return 0;
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	int POIDB::query(
			const std::string& table,
			const std::string& key,
			std::string& reslut)
	{
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it != _table_map.end())
		{
			POIData_o poi_data;
			if(it->second->find(key, poi_data))
			{
				reslut = poi_data.value;
				return 0;
			}
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	int POIDB::query(
			const std::string& table,
			const GridKey& key,
			std::vector<std::string>& reslut)
	{
		reslut.clear();
		POIDB_Table_Map::iterator it = _table_map.find(table);
		if (it != _table_map.end())
		{
			std::list<POIData_o> poi_data_list;
			if(it->second->find(key, poi_data_list))
			{
				std::list<POIData_o>::iterator dit = poi_data_list.begin();
				LOG(INFO)<< "query  reslut :";
				while(dit != poi_data_list.end())
				{
					LOG(INFO)<< "  " << dit->key << " " << dit->value;
					reslut.push_back(dit->value);
					dit++;
				}

				return 0;
			}
		}
		LOG(INFO)<< "table " << table << " not exist";
		return 1;
	}

	void POIDB::runtimeReleaesMemory()
	{
		POIDB_Table_Map::iterator it = _table_map.begin();
		while(it != _table_map.end())
		{
			it->second->runtimeReleaesMemory();
			it++;
		}
	}
}
