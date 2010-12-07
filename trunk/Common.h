/*
 *  Common.h
 *  Bme
 *
 *  Created by Tim De Jong on 17-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef COMMON_H
#define COMMON_H

#include <string>

namespace Common
{
	//check whether a string contains a number
	bool is_number(const std::string s);
	//string methods
	std::string truncString(std::string str);
	//methods for decoding and encoding URLs	
	std::string decodeURL(std::string encoded);
	std::string encodeURL(std::string toEncode);
};

#endif