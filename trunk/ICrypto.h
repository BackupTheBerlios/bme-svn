/*
 *  ICrypto.h
 *  Bme
 *
 *  Created by Tim De Jong on 07-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CRYPTO_H
#define I_CRYPTO_H

#include <stdint.h>

class IMD5;

class ICrypto 
{
public:
	ICrypto() {};
	virtual ~ICrypto() {};
	
	virtual IMD5* GetMD5() = 0;
};

class IMD5
{
public:
	IMD5() {};
	virtual ~IMD5() {};
	
	virtual void Init() = 0;
	virtual void Update(const void* data, uint32_t length) = 0;
	virtual void Final(unsigned char *md) = 0;
};


#endif
