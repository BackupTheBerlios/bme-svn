/*
 *  Preferences.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 30-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "IconPrefs.h"
#include <string>

class Preferences
{
public:
	Preferences();
	virtual ~Preferences();
	
	std::string GetIconPrefsPath();
	virtual IconPrefs* GetIconPrefs();

private:
	IconPrefs* m_iconPrefs;
};

#endif

