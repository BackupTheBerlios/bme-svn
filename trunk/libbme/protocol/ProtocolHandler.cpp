/*
 *  ProtocolHandler.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 24-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ProtocolHandler.h"

ProtocolHandler::ProtocolHandler()
{
}

ProtocolHandler::~ProtocolHandler()
{
}

void ProtocolHandler::SetServerConnection(ServerConnection* serverConnection)
{
	m_serverConnection = serverConnection;
}

ServerConnection* ProtocolHandler::GetServerConnection()
{
	return m_serverConnection;
}

void ProtocolHandler::SendCommandMessage(ProtocolMessage* message)
{
	m_serverConnection->SendCommandMessage(message);
}

uint32_t ProtocolHandler::SendCommandMessageTrId(ProtocolMessage* message)
{
	uint32_t trId = ProtocolMessage::CurrentTrId();
	message->SetTrId(trId);
	this->SendCommandMessage(message);
	
	return trId;
}

void ProtocolHandler::SetProtocolDelegate(IProtocolDelegate* protocolDelegate)
{
	m_protocolDelegate = protocolDelegate;
}

IProtocolDelegate* ProtocolHandler::ProtocolDelegate()
{
	return m_protocolDelegate;
}