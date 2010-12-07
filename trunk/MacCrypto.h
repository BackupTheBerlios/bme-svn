/*
 *  MacCrypto.h
 *  Bme
 *
 *  Created by Tim De Jong on 07-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_CRYPTO_H
#define MAC_CRYPTO_H

#include "ICrypto.h"

class MacCrypto : public ICrypto 
{
public:
	MacCrypto();
	virtual ~MacCrypto();
	virtual IMD5* GetMD5();
};

#endif
