/*
 *  MacPath.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 31-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacPath.h"

MacPath::MacPath()
			:	IPath()
{
	m_path = [[NSString alloc] init];
}

MacPath::MacPath(std::string path)
			:	IPath()
{
	this->SetPath(path);
}

MacPath::MacPath(NSString *path)
			:	IPath()
{
	m_path = [path retain];
}

MacPath::~MacPath()
{
	[m_path release];
}

void MacPath::SetPath(std::string path)
{
	[m_path release];
	m_path = [[NSString alloc] initWithCString:path.c_str() encoding:NSASCIIStringEncoding];
}

IPath* MacPath::Append(std::string path)
{
	NSString* dir = [[NSString alloc] initWithCString:path.c_str() encoding:NSASCIIStringEncoding];
	
	NSString* newPath = [m_path stringByAppendingPathComponent:dir];
	[dir release];
	
	[m_path release];
	m_path = newPath;
	
	const char* cPath = [m_path cStringUsingEncoding:NSASCIIStringEncoding];
	if (cPath)
	{
		this->SetPath(cPath);
	}
	return this;
}

std::string MacPath::ToString() const
{
	const char* cPath = [m_path cStringUsingEncoding:NSASCIIStringEncoding];
	return cPath ? cPath : "";	
}

IPath& MacPath::operator= (std::string path)
{
	this->SetPath(path);
	return *this;
}

bool MacPath::operator== (const IPath& path) const
{
	NSString* dir = [[NSString alloc] initWithCString:path.ToString().c_str() encoding:NSASCIIStringEncoding];
	
	BOOL equal = [m_path isEqualToString:dir];
	return (equal == YES) ? true : false;
}