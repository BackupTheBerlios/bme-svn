/*
 *  MacConnectionManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 17-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_CONNECTION_MANAGER_H
#define MAC_CONNECTION_MANAGER_H

#include <vector>
#include "IConnection.h"
#include "IConnectionManager.h"

class MacConnectionManager : public IConnectionManager
{
public:
	MacConnectionManager();
	virtual ~MacConnectionManager();
	
	virtual IConnection* OpenConnection(std::string url, int32_t port, IConnection::ConnectionType connectionType = IConnection::K_READ_WRITE);
	virtual IConnection* OpenSSLConnection(std::string url, int32_t port, IConnection::SecurityLevel securityLevel, IConnection::ConnectionType connectionType = IConnection::K_READ_WRITE);
	virtual bool CloseConnection(IConnection* connection);
	
private:
	std::vector<IConnection*>	m_connections;
};

#endif
