/*
 *  MSNP12ConversationProtocol.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 25-01-11.
 *  Copyright 2011 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12ConversationProtocol.h"

MSNP12ConversationProtocol::MSNP12ConversationProtocol(SBServerConnection* sbServerConnection)
								:	IConversationProtocol(),
									m_sbServerConnection(sbServerConnection)
{
}

MSNP12ConversationProtocol::~MSNP12ConversationProtocol()
{
}