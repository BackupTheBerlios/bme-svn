/*
 *  MSNP12ConversationProtocol.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 25-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12ConversationProtocol.h"

MSNP12ConversationProtocol::MSNP12ConversationProtocol(SBServerConnection* sbServerConnection)
								:	IConversationProtocol(),
									m_sbServerConnection(sbServerConnection)
{
}

MSNP12ConversationProtocol::~MSNP12ConversationProtocol()
{
}

void MSNP12ConversationProtocol::SetAuthenticationString(std::string authenticationString)
{
	m_authenticationString = authenticationString;
}

std::string MSNP12ConversationProtocol::AuthenticationString()
{
	return m_authenticationString;
}

void MSNP12ConversationProtocol::SetSwitchBoardId(std::string switchBoardId)
{
	m_switchBoardId = switchBoardId;
}

std::string MSNP12ConversationProtocol::SwitchBoardId()
{
	return m_switchBoardId;
}

void MSNP12ConversationProtocol::SetConversationProtocolDelegate(IConversationProtocolDelegate* conversationProtocolDelegate)
{
	m_conversationProtocolDelegate = conversationProtocolDelegate;
}

IConversationProtocolDelegate* MSNP12ConversationProtocol::Delegate()
{
	return m_conversationProtocolDelegate;
}