/*
 *  NSServerConnection.h
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef NS_SERVER_CONNECTION_H
#define NS_SERVER_CONNECTION_H

#include "ServerConnection.h"
#include "ProtocolConstants.h"

class NSServerConnection : public ServerConnection
{
public:
	NSServerConnection(IConnectionManager* connectionManager);
	virtual ~NSServerConnection();

private:
	virtual void InitConnection();
};

#endif
