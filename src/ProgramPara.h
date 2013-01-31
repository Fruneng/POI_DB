/*
 * ProgramPara.h
 *
 *  Created on: 2013-1-31
 *      Author: viewin-cc
 */

#ifndef PROGRAMPARA_H_
#define PROGRAMPARA_H_

#include <boost/program_options.hpp>
#include <string>
#include <vector>



class Para{
public:
	std::string inifile_path;
	std::vector<std::string> create_table_list;
	int listening_port;

	Para():listening_port(50001),inifile_path("config.ini"){}

	void readconfig();
};

bool opinit(int argc, char** argv, Para& para);

#endif /* PROGRAMPARA_H_ */
