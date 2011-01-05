/*
 *  Sorter.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef SORTER_H
#define SORTER_H

#include <string>
#include "KeyValueCollection.h"

class Sorter
{
public:
	Sorter();
	virtual ~Sorter();
	
	virtual void AddCompareKey(std::string key, bool ascending);
	
	bool operator() (KeyValueCollection* collection1, KeyValueCollection* collection2);	//Check!
		
private:
	std::map<std::string, bool> m_compareKeys;
};

#endif

