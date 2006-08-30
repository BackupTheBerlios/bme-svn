/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef AUTHENTICATION_HANDLER_H
#define AUTHENTICATION_HANDLER_H

#include <be/app/Handler.h>
#include <be/app/Message.h>
#include <be/app/MessageFilter.h>
#include <be/support/String.h>
#include "ServerHandler.h"
#include "HTTPFormatter.h"

class AuthenticationHandler : public ServerHandler
{
	public:
		AuthenticationHandler();
		virtual				~AuthenticationHandler();
		
		virtual void		MessageReceived(BMessage *message);
		
	private:
		bool				startLogin(BString loginName, BString password, const char* address, int port);
		BString				TweenerAuthenticate(BString challenge);
		status_t			SSLSend(const char *host, HTTPFormatter *send, HTTPFormatter **recv);		
		
	private:
		BString				m_loginName,
							m_password,
							m_initialStatus;
							
		bool				m_dispatch;
};

class AuthenticationFilter : public BMessageFilter
{
	public:
		AuthenticationFilter();
		virtual ~AuthenticationFilter();
		
		virtual filter_result	Filter(BMessage *message, BHandler **target);
};

#endif
