/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef SB_LOOPER_H
#include "SBLooper.h"
#endif

#include "ConversationHandler.h"
#include "ErrorHandler.h"

SBLooper::SBLooper(BLooper *owner, BString sbAddress, int port, BString authString)
			:	ServerLooper(owner),
				m_authString(authString)
{
	Connect(sbAddress.String(), port);
	AddHandler(new ConversationHandler());
	AddHandler(new ErrorHandler());
}

SBLooper::~SBLooper()
{
}

void SBLooper::init()
{
}

void SBLooper::SetAuthString(BString authString)
{
	m_authString = authString;
}
