/*
 *  KeyValueCollection.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "KeyValueCollection.h"

KeyValueCollection::KeyValueCollection()
{
}

KeyValueCollection::~KeyValueCollection()
{
	//TODO: delete all objects here???
}

std::vector<std::string> KeyValueCollection::Keys()
{
}

std::vector<ValueItem*> KeyValueCollection::Values()
{
}

void KeyValueCollection::AddString(std::string key, std::string value)
{
	this->AddValueItemForKey(key, new StringItem(value));
}

void KeyValueCollection::AddBool(std::string key, bool value)
{
	this->AddValueItemForKey(key, new BoolItem(value));
}

void KeyValueCollection::AddInt8(std::string key, int8_t value)
{
	this->AddValueItemForKey(key, new Int8Item(value));
}

void KeyValueCollection::AddInt16(std::string key, int16_t value)
{
	this->AddValueItemForKey(key, new Int16Item(value));
}

void KeyValueCollection::AddInt32(std::string key, int32_t value)
{
	this->AddValueItemForKey(key, new Int32Item(value));
}

void KeyValueCollection::AddInt64(std::string key, int64_t value)
{
	this->AddValueItemForKey(key, new Int64Item(value));
}

void KeyValueCollection::AddDouble(std::string key, double value)
{
	this->AddValueItemForKey(key, new DoubleItem(value));
}

void KeyValueCollection::AddValueItemForKey(std::string key, ValueItem* item)
{
	ValueItem* oldItem = this->FindValueForKey(key);
	//not too sure about this...this means object ownership...
	if (oldItem)
	{
		//the object is already part of the collection
		if (oldItem == item)
		{
			return;
		}
		else 
		{
			//a different value will be stored under this key, delete the old item
			delete oldItem;
		}
	}
	//store a reference to the new item in the collection
	m_keyValueCollection[key] = item;
}

ValueItem* KeyValueCollection::FindValueForKey(std::string key)
{
	return m_keyValueCollection[key];
}

