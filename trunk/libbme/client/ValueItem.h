/*
 *  ValueItem.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef VALUE_ITEM_H
#define VALUE_ITEM_H

#include <string>
#include <stdint.h>

class ValueItem
{
public:
	enum valueType
	{
		K_STRING_VALUE_TYPE = 0,
		K_NUMBER_VALUE_TYPE,
		K_OBJECT_VALUE_TYPE
	};
	
public:
	ValueItem();
	virtual ~ValueItem();
	
	virtual valueType Type() = 0;
};

class StringItem : public ValueItem
{
public:
	StringItem();
	StringItem(std::string value);
	virtual ~StringItem();
	
	virtual valueType Type();		
	virtual std::string StringValue();
	
	virtual void operator=(const std::string value);
	
	virtual bool Compare(ValueItem* other);
	
private:
	std::string m_value;
};

class NumberItem : public ValueItem
{
public:
	NumberItem();
	virtual ~NumberItem();
	
	virtual valueType Type();
	virtual double DoubleValue() = 0;
	
};

class BoolItem : public NumberItem
{
public:
	BoolItem();
	BoolItem(bool value);
	virtual ~BoolItem();
	
	virtual bool BoolValue();
	virtual double DoubleValue();
		
	virtual void operator=(const bool value);
	virtual bool Compare(ValueItem* other);
	
private:
	bool m_value;
};

class DoubleItem : public NumberItem
{	
public:
	DoubleItem();
	DoubleItem(double value);
	virtual ~DoubleItem();
	
	virtual double DoubleValue();
	
	virtual void operator=(const double value);
	virtual bool Compare(ValueItem* other);
	
private:
	double m_value;
};

class Int8Item : public NumberItem
{
public:
	Int8Item();
	Int8Item(int8_t value);
	virtual ~Int8Item();
	
	virtual int8_t Int8Value();
	virtual double DoubleValue();
	
	virtual void operator=(const int8_t value);
	virtual bool Compare(ValueItem* other);
	
private:
	int8_t m_value;
};

class Int16Item : public NumberItem
{
public:
	Int16Item();
	Int16Item(int16_t value);
	virtual ~Int16Item();
	
	virtual int16_t Int16Value();
	virtual double DoubleValue();
	
	virtual void operator=(const int16_t value);
	virtual bool Compare(ValueItem* other);
	
private:
	int16_t m_value;
};

class Int32Item : public NumberItem
{
public:
	Int32Item();
	Int32Item(int32_t value);
	virtual ~Int32Item();
	
	virtual int32_t Int32Value();
	virtual double DoubleValue();
	
	virtual void operator=(const int32_t value);
	virtual bool Compare(ValueItem* other);
	
private:
	int32_t m_value;
};

class Int64Item : public NumberItem
{
public:
	Int64Item();
	Int64Item(int64_t value);
	virtual ~Int64Item();
	
	virtual int64_t Int64Value();
	virtual double DoubleValue();
	
	virtual void operator=(const int64_t value);
	virtual bool Compare(ValueItem* other);
	
private:
	int64_t m_value;
};


#endif