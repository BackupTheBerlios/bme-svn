/*
 *  IConnection.h
 *  Bme
 *
 *  Created by Tim De Jong on 25-04-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

class IConnectionListener;

class IConnection
{	
public:
	enum SecurityLevel 
	{
		K_NO_SECURITY = 0,
		K_SSL_V2_SECURITY = 1
	};

	enum ConnectionType 
	{
		K_READ_ONLY = 0,
		K_WRITE_ONLY,
		K_READ_WRITE
	};
	
public:
	IConnection() {};
	virtual ~IConnection() {};
	
	virtual void Close() = 0;
	virtual bool IsConnected() = 0;
	virtual std::string	URL() = 0;	
	
	virtual size_t WriteBytes(const uint8_t *bytes, uint32_t length) = 0;
	
	virtual bool Lock() = 0;
	virtual void Unlock() = 0;
	
	virtual void AddConnectionListener(IConnectionListener* connectionListener) = 0;
};

#endif
