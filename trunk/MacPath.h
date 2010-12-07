/*
 *  MacPath.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_PATH_H
#define MAC_PATH_H

#include <string>
#include <Foundation/Foundation.h>
#include "IPath.h"

class MacPath : public IPath
{
public:
	MacPath();
	MacPath(std::string path);
	MacPath(NSString *path);
	virtual ~MacPath();
	
	virtual IPath* Append(std::string path);
	virtual std::string ToString() const;
	virtual void SetPath(std::string path);
	
	virtual IPath& operator= (std::string path);
	virtual bool operator== (const IPath& path) const;
	
private:
	NSString* m_path;
};

#endif
