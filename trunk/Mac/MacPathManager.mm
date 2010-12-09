/*
 *  MacPathManager.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacPathManager.h"
#include "MacPath.h"

MacPathManager::MacPathManager()
{
}

MacPathManager::~MacPathManager()
{
}

IPath* MacPathManager::GetApplicationPath()
{
	NSString* appPath = [[NSBundle mainBundle] bundlePath];
	return new MacPath(appPath);
}

IPath* MacPathManager::GetIconPrefsPath()
{
	IPath* iconPrefsPath = this->GetApplicationPath();
	iconPrefsPath->Append("Contents/Resources/Graphics/Icons/Standard/");
	return iconPrefsPath;
}
