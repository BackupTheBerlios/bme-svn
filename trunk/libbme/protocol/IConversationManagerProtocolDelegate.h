/*
 *  IConversationManagerProtocolDelegate.h
 *  Bme
 *
 *  Created by Tim De Jong on 10-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONVERSATION_MANAGER_PROTOCOL_DELEGATE_H
#define I_CONVERSATION_MANAGER_PROTOCOL_DELEGATE_H

//#include "IConversationProtocol.h"
#include "Contact.h"
#include "Conversation.h"

class IConversationProtocol;

class IConversationManagerProtocolDelegate
{
public:
	IConversationManagerProtocolDelegate() {};
	virtual ~IConversationManagerProtocolDelegate() {};

	virtual void UserConversationStarted(Contact* withContact, IConversationProtocol* conversation) = 0;
	virtual void InvitedToConversation(std::string invitedByPassport, IConversationProtocol* conversation) = 0;
	virtual void ConversationEnded(Conversation* conversation) = 0;
};

#endif
