/*
 * RCF_FUN_IMPL.hpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#ifndef POIDB_RPC_FUN_IMPL_HPP_
#define POIDB_RPC_FUN_IMPL_HPP_

#include "dbken/POIDB.hpp"
#include "Log.hpp"

class POIDB_RPC_FUN_Impl
{
public:
    int CreateTable(const std::string& table);

    int DeleteTable(const std::string& table);

    int insert(	const std::string& table,		//表名称
    				double lng,						//经纬度
    				double lat,
    				int exptime,					//存在时间
    				const std::string& key,			//主键
    				const std::string& value		//值
    				);

    int remove(	const std::string& table,
    				const std::string& key);

    int query(		const std::string& table,
    				const std::string& key,
    				std::string& reslut);

    int query(     const std::string& table,
    				int x,
    				int y,
    				int z,
    				std::vector<std::string>& reslut);

    int query2(    const std::string& table,
    				double lng,
    				double lat,
    				int z,
    				std::vector<std::string>& reslut);

    void runtimeReleaesMemory();

    POIDB_RPC_FUN_Impl(){};

    void init(std::vector<std::string>& table_list);

private:
    POIDB::POIDB _poidb;
};


#endif /* RCF_FUN_IMPL_HPP_ */
