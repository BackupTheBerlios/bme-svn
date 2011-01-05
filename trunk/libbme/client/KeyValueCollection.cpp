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
}

ValueItem* KeyValueCollection::GetValueForKey(std::string key)
{
	return m_keyValueCollection[key];
}

