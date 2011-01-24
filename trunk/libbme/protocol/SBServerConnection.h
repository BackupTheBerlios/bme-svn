/*
 *  SBServerConnection.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 24-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef SB_SERVER_CONNECTION_H
#define SB_SERVER_CONNECTION_H

#include "ServerConnection.h"
#include "IConnectionManager.h"

class SBServerConnection : public ServerConnection
{
public:
	SBServerConnection(IConnectionManager* connectionManager, std::string ip, int32_t port);
	virtual ~SBServerConnection();
};

#endif
