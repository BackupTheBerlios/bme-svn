/*
 *  ConversationManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef CONVERSATION_MANAGER_H
#define CONVERSATION_MANAGER_H

#include "Contact.h"
#include "Conversation.h"
#include "IConversationManagerProtocol.h"

class ConversationManager
{
public:
	ConversationManager(IConversationManagerProtocol *conversationProtocol);
	virtual ~ConversationManager();
	
	Conversation* StartConversation(Contact* contact);	
	void EndConversation(Conversation* conversation);
};

#endif