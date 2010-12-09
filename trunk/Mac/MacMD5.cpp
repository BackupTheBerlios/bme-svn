/*
 *  MacMD5.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 07-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacMD5.h"

MacMD5::MacMD5()
		:	IMD5()
{
}

MacMD5::~MacMD5()
{
}

void MacMD5::Init()
{	
	CC_MD5_Init(&m_mdContext);	
}

void MacMD5::Update(const void* data, uint32_t length)
{
	CC_MD5_Update(&m_mdContext,data, length);
}

void MacMD5::Final(unsigned char *md)
{
	CC_MD5_Final(md,&m_mdContext);
}