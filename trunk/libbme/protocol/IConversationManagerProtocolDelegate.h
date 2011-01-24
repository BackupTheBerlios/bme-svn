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

#include "Conversation.h"

class IConversationManagerProtocolDelegate
{
public:
	IConversationManagerProtocolDelegate() {};
	virtual ~IConversationManagerProtocolDelegate() {};
	
	virtual void ConversationStarted(Conversation* conversation, bool startedByUser) = 0;
	virtual void ConversationEnded(Conversation* conversation) = 0;
};

#endif
