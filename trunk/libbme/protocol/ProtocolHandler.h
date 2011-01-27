/*
 *  ProtocolHandler.h
 *  Bme
 *
 *  Created by Tim De Jong on 24-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef PROTOCOL_HANDLER_H
#define PROTOCOL_HANDLER_H

#include "ProtocolMessage.h"
#include "ServerConnection.h"
#include "IProtocolDelegate.h"

class ProtocolHandler
{
public:
	ProtocolHandler();
	virtual ~ProtocolHandler();
	
	virtual void SetServerConnection(ServerConnection* serverConnection);	
	virtual ServerConnection* GetServerConnection();
	virtual bool IsHandlerForMessage(ProtocolMessage* message) = 0;
	virtual void HandleMessage(ProtocolMessage* message) = 0;
	
	virtual void SendCommandMessage(ProtocolMessage* message);	
	virtual uint32_t SendCommandMessageTrId(ProtocolMessage* message);
	
	virtual void SetProtocolDelegate(IProtocolDelegate* protocolDelegate);
	virtual IProtocolDelegate* ProtocolDelegate();
	
private:
	ServerConnection* m_serverConnection;
	IProtocolDelegate* m_protocolDelegate;
};

#endif
