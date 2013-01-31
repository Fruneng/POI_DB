/*
 * POIDB_RPC_FUN_IMPL.cpp
 *
 *  Created on: 2013-1-31
 *      Author: viewin-cc
 */

#include "POIDB_RPC_FUN_IMPL.hpp"

int POIDB_RPC_FUN_Impl::CreateTable(const std::string& table)
{
	LOG(INFO) << "Command: CreateTable(["<<table<<"]);";
	return _poidb.CreateTable(table);
}

int POIDB_RPC_FUN_Impl::DeleteTable(const std::string& table)
{
	LOG(INFO) << "Command: DeleteTable({s}["<< table <<"]);";
	return _poidb.DeleteTable(table);
}

int POIDB_RPC_FUN_Impl::insert(	const std::string& table,		//表名称
			double lng,						//经纬度
			double lat,
			int exptime,					//存在时间
			const std::string& key,			//主键
			const std::string& value		//值
			)
{
	LOG(INFO) << "Command: insert({s}["<< table <<"],"
			<< "{d}[" << lng << "],"
			<< "{d}[" << lat << "],"
			<< "{i}[" << exptime << "],"
			<< "{s}[" << key << "],"
			<< "{s}[" << value <<"]);";
	return _poidb.insert(table,	lng,lat,exptime,key,value);
}

int POIDB_RPC_FUN_Impl::remove(	const std::string& table,
			const std::string& key)
{
	LOG(INFO) << "Command: remove({s}["<< table <<"],"
			<< "{s}[" << key << "]);";
	return _poidb.remove(table, key);
}

int POIDB_RPC_FUN_Impl::query(		const std::string& table,
			const std::string& key,
			std::string& reslut)
{
	LOG(INFO) << "Command: remove({s}["<< table <<"],"
			<< "{s}[" << key << "], reslut);";
	return _poidb.query(table, key, reslut);
}

int POIDB_RPC_FUN_Impl::query(     const std::string& table,
			int x,
			int y,
			int z,
			std::vector<std::string>& reslut)
{
	LOG(INFO) << "Command: remove({s}["<< table <<"],"
			 << "{i}[" << x << "],"
			 << "{i}[" << y << "],"
			 << "{i}[" << z << "], reslut_vec);";
	POIDB::GridKey gridkey(x,y,z);
	return _poidb.query(table, gridkey, reslut);
}

int POIDB_RPC_FUN_Impl::query2(    const std::string& table,
			double lng,
			double lat,
			int z,
			std::vector<std::string>& reslut)
{
	LOG(INFO) << "Command: remove({s}["<< table <<"],"
			 << "{d}[" << lng << "],"
			 << "{d}[" << lat << "],"
			 << "{i}[" << z << "], reslut_vec);";
	POIDB::GridKey gridkey(lng,lat,z);
	return _poidb.query(table, gridkey, reslut);
}

void POIDB_RPC_FUN_Impl::runtimeReleaesMemory()
{
	LOG(INFO) << "Command: runtimeReleaesMemory();";
	_poidb.runtimeReleaesMemory();
}

void POIDB_RPC_FUN_Impl::init(std::vector<std::string>& table_list)
{
	std::vector<std::string>::iterator it = table_list.begin();
	while(it != table_list.end())
	{
		_poidb.CreateTable(*it);
		it++;
	}
}
