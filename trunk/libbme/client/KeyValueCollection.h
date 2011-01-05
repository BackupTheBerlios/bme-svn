/*
 *  KeyValueCollection.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef KEY_VALUE_COLLECTION_H
#define KEY_VALUE_COLLECTION_H

#include <map>
#include <vector>
#include <stdint.h>
#include "ValueItem.h"

class KeyValueCollection
{
public:
	KeyValueCollection();
	virtual ~KeyValueCollection();
	
	virtual std::vector<std::string> Keys();
	virtual std::vector<ValueItem*> Values();
	
	virtual void AddString(std::string key, std::string value);
	
	virtual void AddBool(std::string key, bool value);
	
	virtual void AddInt8(std::string key, int8_t value);
	
	virtual void AddInt16(std::string key, int16_t value);
	
	virtual void AddInt32(std::string key, int32_t value);
	
	virtual void AddInt64(std::string key, int64_t value);
	
	virtual void AddDouble(std::string key, double value);
	
	virtual void AddValueItemForKey(std::string key, ValueItem* item);
	virtual ValueItem* FindValueForKey(std::string key);	
	
private:
	std::map<std::string, ValueItem*> m_keyValueCollection;
};

#endif

