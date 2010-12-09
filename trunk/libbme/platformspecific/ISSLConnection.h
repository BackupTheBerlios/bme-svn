/*
 *  ISSLConnection.h
 *  Bme
 *
 *  Created by Tim De Jong on 24-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_SSL_CONNECTION_H
#define I_SSL_CONNECTION_H

#include "IConnection.h"

//TODO: remove? and instead add SSL functionality to IConnection?
class ISSLConnection : public IConnection 
{	
public:
	ISSLConnection() {};
	virtual ~ISSLConnection() {};
};

#endif
