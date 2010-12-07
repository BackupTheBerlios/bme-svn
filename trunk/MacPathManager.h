/*
 *  MacPathManager.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_PATH_MANAGER_H
#define MAC_PATH_MANAGER_H

#include "IPath.h"
#include "IPathManager.h"

class MacPathManager : public IPathManager
{
public:	
	MacPathManager();	
	virtual ~MacPathManager();
	
	virtual IPath* GetIconPrefsPath();
	virtual IPath* GetApplicationPath();
};

#endif
