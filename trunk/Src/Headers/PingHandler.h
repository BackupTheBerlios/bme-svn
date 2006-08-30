/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef PING_HANDLER_H
#define PING_HANDLER_H

#include <be/app/Handler.h>
#include <be/app/Message.h>
#include <be/app/MessageFilter.h>
#include <be/app/MessageRunner.h>
#include "ServerHandler.h"

class PingHandler : public ServerHandler
{
	public:
		PingHandler();
		virtual				~PingHandler();
		
		virtual void		MessageReceived(BMessage *message);
	
	public:
		enum 
		{
							K_PING_MSG = 'PIms',
							K_PING_TIME = 1000000
		};
	
	private:
		void				DoMSNP11Challenge(const char *szChallenge, char *szOutput);
		
	private:
		BMessageRunner		*m_pingRunner;
		bool				m_receivedPong;
};

class PingFilter : public BMessageFilter
{
	public:
		PingFilter();
		virtual ~PingFilter();
		
		virtual filter_result	Filter(BMessage *message, BHandler **target);
};
#endif
