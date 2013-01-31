/*
 * RCF_Fun.h
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#ifndef RCF_FUN_H_
#define RCF_FUN_H_

#include <RCF/RCF.hpp>
#include <SF/vector.hpp>

/*默认创建的表有										*/
/*	cloud 云图数据									*/
/*	mstreet 移动结晶数据								*/
/*	mark 标注数据									*/
/*  custmor 用户自定义标注数据						*/


RCF_BEGIN(POIDB_RPC_FUN, "POIDB_RPC_FUN")
    RCF_METHOD_R1(int, CreateTable, const std::string &)
    RCF_METHOD_R1(int, DeleteTable, const std::string &)
    RCF_METHOD_R6(int, insert, const std::string &, double,double, int, const std::string&, const std::string&)
    RCF_METHOD_R2(int, remove, const std::string &, const std::string &)
    RCF_METHOD_R3(int, query, const std::string &, const std::string &,std::string&)
    RCF_METHOD_R5(int, query, const std::string &, int, int, int, std::vector<std::string>&)
    RCF_METHOD_R5(int, query2, const std::string &, double, double, int, std::vector<std::string>&)
    RCF_METHOD_V0(void, runtimeReleaesMemory)
RCF_END(POIDB_RPC_FUN)

/*
 *class POIDB_RPC_FUN 接口:
 *    int CreateTable(const std::string& table);
 *
 *    int DeleteTable(const std::string& table);
 *
 *    int insert(	const std::string& table,		//表名称
 *    				double lng,						//经纬度
 *    				double lat,
 *    				int exptime,					//存在时间
 *    				const std::string& key,			//主键
 *    				const std::string& value		//值
 *    				);
 *
 *    int remove(	const std::string& table,
 *    				const std::string& key);
 *
 *    int query(	const std::string& table,
 *    				const std::string& key,
 *    				std::string& reslut);
 *
 *    int query(    const std::string& table,
 *    				int x,								//网格x
 *    				int y,								//网格y
 *    				int z,								//网格zoom
 *    				std::vector<std::string>& reslut);
 *
 *    int query2(   const std::string& table,
 *   				double lng,							//经纬度
 *    				double lat,
 *    				int z,								//网格zoom
 *    				std::vector<std::string>& reslut);
 *
 *    void runtimeReleaesMemory();
 */



#endif /* RCF_FUN_H_ */
