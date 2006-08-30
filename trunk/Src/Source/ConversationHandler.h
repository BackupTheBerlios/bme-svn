#ifndef CONVERSATION_HANDLER_H
#define CONVERSATION_HANDLER_H

#include <be/app/Handler.h>
#include <be/app/Message.h>
#include <be/app/MessageFilter.h>
#include "ServerHandler.h"

class ConversationHandler : public ServerHandler
{
	public:
		ConversationHandler();
		virtual				~ConversationHandler();
		
		virtual void		MessageReceived(BMessage *message);
};

class ConversationFilter : public BMessageFilter
{
	public:
		ConversationFilter();
		virtual ~ConversationFilter();
		
		virtual filter_result	Filter(BMessage *message, BHandler **target);
};

#endif
