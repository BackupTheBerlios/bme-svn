/*
 *  MacMD5.h
 *  Bme
 *
 *  Created by Tim De Jong on 07-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_MD5_H
#define MAC_MD5_H

#include "ICrypto.h"
#include <CommonCrypto/CommonDigest.h>

class MacMD5 : public IMD5 
{
public:
	MacMD5();
	virtual ~MacMD5();

public:
	virtual void Init();
	virtual void Update(const void* data, uint32_t length);
	virtual void Final(unsigned char *md);

private:
	CC_MD5_CTX m_mdContext;
};

#endif