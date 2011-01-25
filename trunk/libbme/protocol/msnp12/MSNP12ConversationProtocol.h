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

class MSNP12ConversationProtocol : public IConversationProtocol
{
public:
	MSNP12ConversationProtocol(SBServerConnection* sbServerConnection);
	virtual ~MSNP12ConversationProtocol();
	
private:
	SBServerConnection* m_sbServerConnection;
};

#endif