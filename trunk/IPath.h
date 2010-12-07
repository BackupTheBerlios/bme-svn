/*
 *  IPath.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_PATH_H
#define I_PATH_H

#include <string>

class IPath 
{
public:
	virtual ~IPath() {};
	
	virtual IPath* Append(std::string path) = 0;
	virtual std::string ToString() const = 0;
	virtual void SetPath(std::string path) = 0;
	
	virtual IPath& operator= (std::string path) = 0;
	virtual bool operator== (const IPath& path) const = 0;
};


#endif
