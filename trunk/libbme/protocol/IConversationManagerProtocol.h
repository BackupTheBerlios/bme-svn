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

class IConversationManagerProtocol
{
public:
	IConversationManagerProtocol() {};
	virtual ~IConversationManagerProtocol() {};
	
	virtual IConversationProtocol* GetConversationProtocol() = 0;
public:
	virtual void SetConversationManagerProtocolDelegate(IConversationManagerProtocolDelegate* converationManagerProtocolDelegate) = 0;
	virtual IConversationManagerProtocolDelegate *Delegate() = 0;
};

#endif
