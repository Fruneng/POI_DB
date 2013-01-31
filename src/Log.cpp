/*
 * Log.cpp
 *
 *  Created on: 2013-1-30
 *      Author: viewin-cc
 */

#include "Log.hpp"

void glog_init(std::string home)
{
	//"/home/viewin-cc/workspace/POI_db";
	//glog init
	google::InitGoogleLogging("0");
	std::string info_log = home + "/log/master_info_";
	google::SetLogDestination(google::INFO, info_log.c_str());
	std::string warning_log = home + "/log/master_warning_";
	google::SetLogDestination(google::WARNING, warning_log.c_str());
	std::string error_log = home + "/log/master_error_";
	google::SetLogDestination(google::ERROR, error_log.c_str());
	std::string fatal_log = home + "/log/master_fatal_";
	google::SetLogDestination(google::FATAL, fatal_log.c_str());
}
