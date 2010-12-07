/*
 *  ConversationManager.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ConversationManager.h"

ConversationManager::ConversationManager(IConversationManagerProtocol *conversationProtocol)
{
}

ConversationManager::~ConversationManager()
{
}

Conversation* ConversationManager::StartConversation(Contact* contact)
{
	return NULL;
}

void ConversationManager::EndConversation(Conversation* conversation)
{
}