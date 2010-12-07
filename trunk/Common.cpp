/*
 *  Common.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 17-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "Common.h"
#include <cctype>

bool Common::is_number(const std::string s)
{
	for (int i = 0; i < s.length(); i++) 
	{
		if (!std::isdigit(s[i]))
			return false;
	}	
	return true;
}

std::string Common::truncString(std::string str)
{	
	//truncate spaces at the beginning of a string
	size_t lastSpaceFront = std::string::npos;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (c == ' ')
		{
			lastSpaceFront = i;
		}
		else 
		{
			break;
		}

	}
		
	//truncate spaces at the end of the string
	size_t firstSpaceBack = std::string::npos;
	for (size_t j = str.size() - 1; j != 0; j--)
	{
		char c = str[j];
		if (c == ' ')
		{
			firstSpaceBack = j;
		}
		else 
		{
			break;
		}		
	}

	std::string truncatedString = str.substr(lastSpaceFront + 1, firstSpaceBack - lastSpaceFront - 1);
	return truncatedString;
}

//TODO: check if it works -> Not UTF8 agnostic! How can we fix this?
std::string Common::decodeURL(std::string encoded)
{
	std::string decoded = encoded;
	size_t index = decoded.find('%');
  	while (index != std::string::npos)
  	{
   		char buf[3];
		unsigned int c;
   		decoded.erase(index,1);
   		decoded.copy(buf,2,index);
		decoded.erase(index,2);
   		sscanf(buf, "%x", &c);
   		decoded.insert(decoded.begin() + index,(char)c);
   		index = decoded.find('%', index + 1);
	}
  	return decoded;
}

//TODO:check if it works
std::string Common::encodeURL(std::string toEncode)
{
  	std::string encodedString = "";
  	//áéíóú%20(@#$%25&/?¿¡!ñÑ<>)%20{^|¬°;,~\}%20[àèìòù]
	//(áéíóú)@{àèìòù}#[ºª\|~¬æ®†¥ //∫ø //π∑∂ ƒ©™£ //≤≈ ¢√ßµ…ñÑ]
  	
	for (int i = 0; i < toEncode.size(); i++)
  	{
    	
		if(!(isalpha(toEncode[i]) || isdigit(toEncode[i]) || (toEncode[i] == '.')))
		{
    		char wptr[4];
			wptr[3] = '\0';
			sprintf(wptr, "%%%2x", (uint8_t)(toEncode[i]));
      		encodedString += wptr;
    	}
		else 
		{
			encodedString += toEncode[i];
		}   	
  	}
	
  	return encodedString;
}
