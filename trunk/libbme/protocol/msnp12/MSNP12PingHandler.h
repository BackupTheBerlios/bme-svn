/*
 *  MSNP12PingHandler.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSNP12_PING_HANDLER_H
#define MSNP12_PING_HANDLER_H

#include "ProtocolHandler.h"
#include <string>//NotificationMessages::K_CLIENT_PONG

class MSNP12PingHandler : public ProtocolHandler 
{
public:
	MSNP12PingHandler();
	virtual ~MSNP12PingHandler();
		
public:
	virtual bool IsHandlerForMessage(ProtocolMessage* message);
	virtual void HandleMessage(ProtocolMessage* message);
	
private:
	std::string DoMSNP11Challenge(std::string challenge);
	
private:
	bool m_receivedPong;
};

#endif
