/*
 *  IConnectionListener.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 20-09-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONNECTION_LISTENER_H
#define I_CONNECTION_LISTENER_H

#include "IConnection.h"

class IConnectionListener
{
public:
	virtual ~IConnectionListener() {};
	
	virtual void DidConnect(IConnection* connection) = 0;
	virtual void DidDisconnect(IConnection* connection) = 0;
	virtual void BytesSent(IConnection* connection, size_t length) = 0;
	virtual void BytesRead(IConnection* connection, uint8_t* bytes, size_t length) = 0;
};

#endif
