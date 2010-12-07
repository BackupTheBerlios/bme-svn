/*
 *  IConnectionManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 10-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONNECTION_MANAGER_H
#define I_CONNECTION_MANAGER_H

#include "IConnection.h"
#include "ISSLConnection.h"

class IConnectionManager
{
public:
	IConnectionManager() {};
	virtual ~IConnectionManager() {};
	
	virtual IConnection* OpenConnection(std::string url, int32_t port, IConnection::ConnectionType connectionType = IConnection::K_READ_WRITE) = 0;
	virtual ISSLConnection* OpenSSLConnection(std::string url, int32_t port, IConnection::SecurityLevel securityLevel, IConnection::ConnectionType connectionType = IConnection::K_READ_WRITE) = 0;
	virtual bool CloseConnection(IConnection* connection) = 0;
};

#endif
