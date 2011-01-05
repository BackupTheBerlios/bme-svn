/*
 *  ValueItem.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "ValueItem.h"

//===ValueItem===
ValueItem::ValueItem()
{
}

ValueItem::~ValueItem()
{
}

//===StringItem===
StringItem::StringItem()
{
}

StringItem::StringItem(std::string value)
				:	m_value(value)
{
}

StringItem::~StringItem()
{
}

ValueItem::valueType StringItem::Type()
{
	return K_STRING_VALUE_TYPE;
}

std::string StringItem::StringValue()
{
	return m_value;
}

void StringItem::operator=(const std::string value)
{
	m_value = value;
}

bool StringItem::Compare(ValueItem* other)
{
	return false;
}

//===NumberItem===
NumberItem::NumberItem()
{
}

NumberItem::~NumberItem()
{
}

ValueItem::valueType NumberItem::Type()
{
	return K_NUMBER_VALUE_TYPE;
}

//===BoolItem===
BoolItem::BoolItem()
{
}

BoolItem::BoolItem(bool value)
			:	m_value(value)
{
}

BoolItem::~BoolItem()
{
}

bool BoolItem::BoolValue()
{
	return m_value;
}

double BoolItem::DoubleValue()
{
	return m_value;
}

void BoolItem::operator=(const bool value)
{
	m_value = value;
}

bool BoolItem::Compare(ValueItem* other)
{
	return false;
}

//===DoubleItem===
DoubleItem::DoubleItem()
{
}

DoubleItem::DoubleItem(double value)
				:	m_value(value)
{
}

DoubleItem::~DoubleItem()
{
}

double DoubleItem::DoubleValue()
{
	return m_value;
}

void DoubleItem::operator=(const double value)
{
	m_value = value;
}

bool DoubleItem::Compare(ValueItem* other)
{
	return false;
}

//===Int8Item===
Int8Item::Int8Item()
{
}

Int8Item::Int8Item(int8_t value)
		:	m_value(value)
{
}

Int8Item::~Int8Item()
{
}

int8_t Int8Item::Int8Value()
{
	return m_value;
}

double Int8Item::DoubleValue()
{
	return m_value;
}

void Int8Item::operator=(const int8_t value)
{
	m_value = value;
}

bool Int8Item::Compare(ValueItem* other)
{
	return false;
}

//===Int16Item===
Int16Item::Int16Item()
{
}

Int16Item::Int16Item(int16_t value)
				:	m_value(value)
{
}

Int16Item::~Int16Item()
{
}

int16_t Int16Item::Int16Value()
{
	return m_value;
}

double Int16Item::DoubleValue()
{
	return m_value;
}

void Int16Item::operator=(const int16_t value)
{
	m_value = value;
}

bool Int16Item::Compare(ValueItem* other)
{
	return false;
}

//===Int32Item===
Int32Item::Int32Item()
{
}

Int32Item::Int32Item(int32_t value)
				:	m_value(value)
{
}

Int32Item::~Int32Item()
{
}

int32_t Int32Item::Int32Value()
{
	return m_value;
}

double Int32Item::DoubleValue()
{
	return m_value;
}

void Int32Item::operator=(const int32_t value)
{
	m_value = value;
}

bool Int32Item::Compare(ValueItem* other)
{
	return false;
}

//===Int64Item===
Int64Item::Int64Item()
{
}

Int64Item::Int64Item(int64_t value)
:	m_value(value)
{
}

Int64Item::~Int64Item()
{
}

int64_t Int64Item::Int64Value()
{
	return m_value;
}

double Int64Item::DoubleValue()
{
	return m_value;
}

void Int64Item::operator=(const int64_t value)
{
	m_value = value;
}

bool Int64Item::Compare(ValueItem* other)
{
	return false;
}
