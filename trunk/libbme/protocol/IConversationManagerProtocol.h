/*
 *  IConversationManagerProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONVERSATION_MANAGER_PROTOCOL_H
#define I_CONVERSATION_MANAGER_PROTOCOL_H

#include "IConversationManagerProtocolDelegate.h"
#include "Contact.h"
#include "Conversation.h"
#include "IConversationManagerProtocol.h"

class IConversationManagerProtocol
{
public:
	IConversationManagerProtocol() {};
	virtual ~IConversationManagerProtocol() {};
	
	virtual void StartConversation(Contact* contact) = 0;
	virtual void EndConversation(Conversation* conversation) = 0;
	
public:
	virtual void SetConversationManagerProtocolDelegate(IConversationManagerProtocolDelegate* converationManagerProtocolDelegate) = 0;
	virtual IConversationManagerProtocolDelegate *Delegate() = 0;
};

#endif
