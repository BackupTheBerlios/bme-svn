/*
 *  IPathManager.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_PATH_MANAGER_H
#define I_PATH_MANAGER_H

#include "IPath.h"

class IPathManager
{
public:
	virtual ~IPathManager() {};
	
	virtual IPath* GetIconPrefsPath() = 0;
	virtual IPath* GetApplicationPath() = 0;
};

#endif
