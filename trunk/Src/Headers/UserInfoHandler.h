/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef USER_INFO_HANDLER_H
#define USER_INFO_HANDLER_H

#include <be/app/Handler.h>
#include <be/app/Message.h>
#include <be/app/MessageFilter.h>
#include "ServerHandler.h"

class UserInfoHandler : public ServerHandler
{
	public:
		UserInfoHandler();
		virtual				~UserInfoHandler();
		
		virtual void		MessageReceived(BMessage *message);
};

class UserInfoFilter : public BMessageFilter
{
	public:
		UserInfoFilter();
		virtual ~UserInfoFilter();
		
		virtual filter_result	Filter(BMessage *message, BHandler **target);
};

#endif
