/*
 * ProgramPara.cpp
 *
 *  Created on: 2013-1-31
 *      Author: viewin-cc
 */
#include "ProgramPara.h"
#include "IniFile.hpp"


bool opinit(int argc, char** argv, Para& para)
{
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce help message")
	    ("Init,I", boost::program_options::value<std::string>(), "set the init file path")
	    ("Port,P", boost::program_options::value<int>(), "set the listening port")
	;

	boost::program_options::variables_map vm;
	boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return false;
	}

	if (vm.count("I")) {
		std::cout << "Init file : "
				<< vm["I"].as<std::string>() << std::endl;
		para.inifile_path = vm["I"].as<std::string>();
	} else {
		std::cout << "default Init file : config.ini" << std::endl;
	}

	if (vm.count("P")) {
		std::cout << "listening port : "
				<< vm["P"].as<int>() << std::endl;
		para.listening_port = vm["P"].as<int>();
	} else {
		std::cout << "default listening port : 50001" << std::endl;
	}

	para.readconfig();
	return true;
}

std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}


void Para::readconfig()
{
	IniFile ini;
	ini.open(inifile_path);

	std::string tables = ini.read("POIDB","tables");

	create_table_list = split(tables,"|");
}


