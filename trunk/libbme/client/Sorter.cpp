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

bool Sorter::operator() (KeyValueCollection* collection1, KeyValueCollection* collection2)
{
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
