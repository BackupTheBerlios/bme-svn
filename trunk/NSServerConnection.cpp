/*
 *  NSServerConnection.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "NSServerConnection.h"

NSServerConnection::NSServerConnection(IConnectionManager* connectionManager)
						:	ServerConnection(connectionManager)

{
	InitConnection();
}

NSServerConnection::~NSServerConnection()
{
}

void NSServerConnection::InitConnection()
{
	//setup connection to the NSServer
	this->Connect(ProtocolConstants::K_DS_ADDRESS, ProtocolConstants::K_DS_PORT);	
}