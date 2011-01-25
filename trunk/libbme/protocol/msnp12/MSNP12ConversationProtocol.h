/*
 *  MSNP12ConversationProtocol.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 25-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSNP12_CONVERSATION_PROTOCOL_H
#define MSNP12_CONVERSATION_PROTOCOL_H

#include "IConversationProtocol.h"
#include "SBServerConnection.h"
#include "IConversationProtocolDelegate.h"

class MSNP12ConversationProtocol : public IConversationProtocol
{
public:
	MSNP12ConversationProtocol(SBServerConnection* sbServerConnection);
	virtual ~MSNP12ConversationProtocol();
	
	void SetAuthenticationString(std::string authenticationString);
	std::string AuthenticationString();
	
	void SetSwitchBoardId(std::string switchBoardId);
	std::string SwitchBoardId();
	
	virtual void SetConversationProtocolDelegate(IConversationProtocolDelegate* userProtocolDelegate);
	virtual IConversationProtocolDelegate* Delegate();
	
private:
	SBServerConnection* m_sbServerConnection;
	IConversationProtocolDelegate* m_conversationProtocolDelegate;
	
	std::string m_authenticationString;
	std::string m_switchBoardId;
};

#endif