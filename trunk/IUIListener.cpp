/*
 *  IUIListener.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 13-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#include "IUIListener.h"
#include "ProtocolConstants.h"
#include <sstream>

int32_t IUIListener::s_listenerId = 0;

IUIListener::IUIListener(std::string listenerName)
				:	m_listenerName(listenerName)
{
}

IUIListener::~IUIListener()
{
}

std::string IUIListener::Id()
{
	std::stringstream ss;
	ss << m_listenerName << "-";
	ss << IUIListener::CurrentListenerId();
	return ss.str(); 
}

int32_t IUIListener::CurrentListenerId()
{
	uint32_t newId = s_listenerId + 1;
	if (newId > 0 && newId <= ProtocolConstants::K_MAX_TR_ID)
	{	
		s_listenerId++;
	}
	else
	{
		//reset the counter
		s_listenerId = 0;
	}
	return s_listenerId;
}
