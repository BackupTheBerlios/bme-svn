/*
 *  Sorter.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 04-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "Sorter.h"

Sorter::Sorter()
{
}

Sorter::~Sorter()
{
}

void Sorter::AddCompareKey(std::string key, bool ascending)
{
	m_compareKeys[key] = ascending;
}

int Sorter::compare(KeyValueCollection* collection1, KeyValueCollection* collection2)
{
	typedef std::map<std::string, bool>::const_iterator MI;
	//loop through all the key which should be taken into account in the comparison
	for (MI p = m_compareKeys.begin(); p != m_compareKeys.end(); ++p)
	{
		std::string key = p->first;
		bool ascending = p->second;
				
		ValueItem* vi1 = collection1->FindValueForKey(key);
		ValueItem* vi2 = collection2->FindValueForKey(key);
		if (vi1 && vi2)
		{
			int compare = vi1->Compare(vi2);
			//if one of the values for a key is smaller than the other return true
			//else compare the next two key-value pairs with each other
			if (ascending && compare != 0)
			{
				return compare;
			}
			else if (!ascending && compare != 0)
			{
				return -compare;
			}			
		}
	}
	return 0;
}

bool Sorter::operator() (KeyValueCollection* collection1, KeyValueCollection* collection2)
{
	if (collection1 && collection2)
	{
		return (this->compare(collection1, collection2) < 0);
	}	
	return false;
}

/** ====sorter example =====
 
 //TODO: create a sorter class that makes it possible to sort on a combination of values 
 
 int comparefunc(const void *arg1, const void *arg2);
 
 
 
 int main(void) {
 
 MyDate dates[MAXDATES];
 
 // Set up some initial date values here
 
 
 
 // Now sort them                                      
 
 qsort(dates, MAXDATES, sizeof(MyDate), comparefunc);
 
 
 
 return 0;
 
 }
 
 
 
 int comparefunc(const void *arg1, const void *arg2) {
 
 const MyDate *date1 = (MyDate *)arg1;
 
 const MyDate *date2 = (MyDate *)arg2;
 
 
 
 if (date1->year < date2->year)
 
 return -1;
 
 else if (date1->year > date2->year)
 
 return 1;
 
 else {
 
 if (date1->month < date2->month)
 
 return -1;
 
 else if (date1->month > date2->month)
 
 return 1;
 
 else {
 
 if (date1->day < date2->day)
 
 return -1;
 
 else if (date1->day > date2->day)
 
 return 1;
 
 }
 
 }
 
 return 0;
 }
 
 */ 
