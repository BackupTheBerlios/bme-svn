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
	//clean up all the objects in the collection
	typedef std::map<std::string, ValueItem*>::iterator MI;
	for (MI p = m_keyValueCollection.begin(); p != m_keyValueCollection.end(); ++p)
	{
		ValueItem* vi = p->second;
		delete vi;
	}	
}

std::vector<std::string> KeyValueCollection::Keys()
{
	std::vector<std::string> keys;
	//return all the keys in the keyvaluecollection
	typedef std::map<std::string,ValueItem*>::iterator MI;
	for (MI p = m_keyValueCollection.begin(); p != m_keyValueCollection.end(); ++p)
	{
		keys.push_back(p->first);
	}
	return keys;
}

std::vector<ValueItem*> KeyValueCollection::Values()
{
	std::vector<ValueItem*> values;
	//return all the values in the keyvaluecollection
	typedef std::map<std::string,ValueItem*>::iterator MI;
	for (MI p = m_keyValueCollection.begin(); p != m_keyValueCollection.end(); ++p)
	{
		values.push_back(p->second);
	}
	return values;
}

bool KeyValueCollection::IsEmpty()
{
	return m_keyValueCollection.empty();
}

void KeyValueCollection::AddString(std::string key, std::string value)
{
	this->AddValueItemForKey(key, new StringItem(value));
}

bool KeyValueCollection::FindString(std::string key, std::string* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		StringItem* stringItem = dynamic_cast<StringItem*> (item);
		if (stringItem)
		{
			*value = stringItem->StringValue();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddBool(std::string key, bool value)
{
	this->AddValueItemForKey(key, new BoolItem(value));
}

bool KeyValueCollection::FindBool(std::string key, bool* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		BoolItem* boolItem = dynamic_cast<BoolItem*> (item);
		if (boolItem)
		{
			*value = boolItem->BoolValue();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddInt8(std::string key, int8_t value)
{
	this->AddValueItemForKey(key, new Int8Item(value));
}

bool KeyValueCollection::FindInt8(std::string key, int8_t* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		Int8Item* int8Item = dynamic_cast<Int8Item*> (item);
		if (int8Item)
		{
			*value = int8Item->Int8Value();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddInt16(std::string key, int16_t value)
{
	this->AddValueItemForKey(key, new Int16Item(value));
}

bool KeyValueCollection::FindInt16(std::string key, int16_t* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		Int16Item* int16Item = dynamic_cast<Int16Item*> (item);
		if (int16Item)
		{
			*value = int16Item->Int16Value();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddInt32(std::string key, int32_t value)
{
	this->AddValueItemForKey(key, new Int32Item(value));
}

bool KeyValueCollection::FindInt32(std::string key, int32_t* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		Int32Item* int32Item = dynamic_cast<Int32Item*> (item);
		if (int32Item)
		{
			*value = int32Item->Int32Value();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddInt64(std::string key, int64_t value)
{
	this->AddValueItemForKey(key, new Int64Item(value));
}

bool KeyValueCollection::FindInt64(std::string key, int64_t* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		Int64Item* int64Item = dynamic_cast<Int64Item*> (item);
		if (int64Item)
		{
			*value = int64Item->Int64Value();
			return true;
		}
	}
	return false;
}

void KeyValueCollection::AddDouble(std::string key, double value)
{
	this->AddValueItemForKey(key, new DoubleItem(value));
}

bool KeyValueCollection::FindDouble(std::string key, double* value)
{
	ValueItem* item = this->FindValueForKey(key);
	if (item)
	{
		DoubleItem* doubleItem = dynamic_cast<DoubleItem*> (item);
		if (doubleItem)
		{
			*value = doubleItem->DoubleValue();
			return true;
		}
	}
	return false;
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
	if (m_keyValueCollection.find(key) != m_keyValueCollection.end())
	{
		return m_keyValueCollection[key];
	}
	return NULL;
}

