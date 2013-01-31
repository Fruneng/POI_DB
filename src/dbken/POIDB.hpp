/*
 * POIDB.hpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#ifndef POIDB_HPP_
#define POIDB_HPP_

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "POITable.hpp"

namespace POIDB
{

	class POIDB
	{
	public:
		POIDB(){};

		/*return 0：创建成功 1：已存在*/
		int CreateTable(const std::string& table);

		/*return 0：创建成功 1：不存在*/
		int DeleteTable(const std::string& table);

		/*return 0：插入成功 1：表不存在*/
		int insert(
				const std::string& table,		//表名称
				double lng,						//经纬度
				double lat,
				int exptime,					//存在时间
				const std::string& key,			//主键
				const std::string& value		//值
				);

		int remove(
				const std::string& table,
				const std::string& key);

		/*按主键查询*/
		int query(
				const std::string& table,
				const std::string& key,
				std::string& reslut);

		/*区域聚合查询*/
		int query(
				const std::string& table,
				const GridKey& key,
				std::vector<std::string>& reslut);

		void runtimeReleaesMemory();

	protected:

		typedef boost::shared_ptr<POITable> POITablePtr;
		typedef std::map<std::string, POITablePtr> POIDB_Table_Map;

	private:
		POIDB_Table_Map _table_map;

	};

}

#endif /* POIDB_HPP_ */
