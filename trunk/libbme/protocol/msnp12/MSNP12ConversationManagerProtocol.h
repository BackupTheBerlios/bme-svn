/*
 *  MSNP12ConversationManagerProtocol.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 24-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSNP12_CONVERSATION_MANAGER_PROTOCOL_H
#define MSNP12_CONVERSATION_MANAGER_PROTOCOL_H

#include <queue>
#include "ProtocolHandler.h"
#include "IConversationManagerProtocol.h"
#include "IConversationManagerProtocolDelegate.h"
#include "Contact.h"
#include "Conversation.h"
#include "ProtocolMessage.h"

class MSNP12ConversationManagerProtocol : public ProtocolHandler, public IConversationManagerProtocol
{
public:
	MSNP12ConversationManagerProtocol();
	virtual ~MSNP12ConversationManagerProtocol();
	
	virtual void StartConversation(Contact* contact);
	virtual void EndConversation(Conversation* conversation);

public:
	virtual bool IsHandlerForMessage(ProtocolMessage* message);
	virtual void HandleMessage(ProtocolMessage* message);	
	
public:
	virtual void SetConversationManagerProtocolDelegate(IConversationManagerProtocolDelegate* converationManagerProtocolDelegate);
	virtual IConversationManagerProtocolDelegate *Delegate();
	
private:
	IConversationManagerProtocolDelegate* m_conversationManagerDelegate;
	std::queue<Contact*> m_contactsForConversations;
};

#endif
