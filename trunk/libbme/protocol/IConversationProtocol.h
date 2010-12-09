/*
 *  IConversationProtocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 05-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_CONTACT_LIST_PROTOCOL_H
#define I_CONTACT_LIST_PROTOCOL_H

#include "IConversationProtocolDelegate.h"

class IConversationProtocol
{
public:
	IConversationProtocol() {};
	virtual ~IConversationProtocol() {};
	
	virtual void SetConversationProtocolDelegate(IConversationProtocolDelegate* userProtocolDelegate) = 0;
	virtual IConversationProtocolDelegate* Delegate() = 0;
};

#endif

