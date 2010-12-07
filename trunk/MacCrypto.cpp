/*
 *  MacCrypto.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 07-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacCrypto.h"
#include "MacMD5.h"

MacCrypto::MacCrypto()
			:	ICrypto()
{
}

MacCrypto::~MacCrypto()
{
}

IMD5* MacCrypto::GetMD5()
{
	return new MacMD5();
}