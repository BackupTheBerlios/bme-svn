/*
 *  SBServerConnection.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 24-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "SBServerConnection.h"

SBServerConnection::SBServerConnection(IConnectionManager* connectionManager, std::string ip, int32_t port)
						:	ServerConnection(connectionManager)
{
	this->Connect(ip, port);
}

SBServerConnection::~SBServerConnection()
{
}