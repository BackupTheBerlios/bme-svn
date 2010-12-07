/*
 *  Preferences.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 30-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "Preferences.h"
#include "PlatformSpecific.h"
#include <iostream>

Preferences::Preferences()
{
	m_iconPrefs = new IconPrefs(this->GetIconPrefsPath());
}

Preferences::~Preferences()
{
	delete m_iconPrefs;
}

std::string Preferences::GetIconPrefsPath()
{	
	//get path for iconprefs file
	IPath* iconPrefsPath = PlatformSpecific::GetPathManager()->GetIconPrefsPath();
	iconPrefsPath->Append("iconprefs.xml");
	
	std::string path = iconPrefsPath->ToString();
	cout << "path=" << path << endl;
	delete iconPrefsPath;
	
	return path;	
}

IconPrefs* Preferences::GetIconPrefs()
{
	return m_iconPrefs;
}