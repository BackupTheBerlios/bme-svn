/*
 *  MacConnectionManager.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 17-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacConnectionManager.h"
#include "MacConnection.h"

MacConnectionManager::MacConnectionManager()
						:	IConnectionManager()
{
}

MacConnectionManager::~MacConnectionManager()
{
}

IConnection* MacConnectionManager::OpenConnection(std::string url, int32_t port, IConnection::ConnectionType connectionType)
{
	return new MacConnection(url, port, connectionType, IConnection::K_NO_SECURITY);
}

IConnection* MacConnectionManager::OpenSSLConnection(std::string url, int32_t port, IConnection::SecurityLevel securityLevel, IConnection::ConnectionType connectionType)
{
	return new MacConnection(url, port, connectionType, IConnection::K_SSL_V2_SECURITY);
}

bool MacConnectionManager::CloseConnection(IConnection* connection)
{
	connection->Close();
	return !(connection->IsConnected());
}