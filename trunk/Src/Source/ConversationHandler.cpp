#ifndef CONVERSATION_HANDLER_H
#include "ConversationHandler.h"
#endif

ConversationHandler::ConversationHandler()
						:	ServerHandler()
{
}

ConversationHandler::~ConversationHandler()
{
}

void ConversationHandler::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		default:
			BHandler::MessageReceived(message);
		break;
	}
}

//==========================ConversationFilter================================
ConversationFilter::ConversationFilter()
						:	BMessageFilter(B_PROGRAMMED_DELIVERY,B_LOCAL_SOURCE)
{
}

ConversationFilter::~ConversationFilter()
{
}

filter_result ConversationFilter::Filter(BMessage *message, BHandler **target)
{
	filter_result result;
	switch (message->what)
	{		
		default:
			result = B_SKIP_MESSAGE;
		break;
	}
	return result;
}
