/*
 * Tool.hpp
 *
 *  Created on: 2013-1-31
 *      Author: viewin-cc
 */

#ifndef TOOL_HPP_
#define TOOL_HPP_


#ifdef HAS_DEV_TOOL
#include <algorithm>
#include "Log.hpp"

struct OP
{
	void operator () (const std::string& s)
	{
		std::cout << s << std::endl;
	}
};
#endif

#endif /* TOOL_HPP_ */
