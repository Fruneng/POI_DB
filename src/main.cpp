/*
 * main.cpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#include <iostream>
#include <algorithm>
#include "ProgramPara.h"

#include "Log.hpp"
#include "RCF_Fun.h"
#include "POIDB_RPC_FUN_IMPL.hpp"

int main(int argc,char** argv)
{
	Para para;
	if(!opinit(argc, argv, para))
	{
		return 0;
	}

	glog_init("/home/viewin-cc/workspace/POI_db");

	RCF::RcfInitDeinit rcfInit;

	POIDB_RPC_FUN_Impl poidb_rpc_fun_impl;
	poidb_rpc_fun_impl.init(para.create_table_list);

	RCF::RcfServer server( RCF::TcpEndpoint(para.listening_port) );
	server.bind<POIDB_RPC_FUN>(poidb_rpc_fun_impl);
	server.start();

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
