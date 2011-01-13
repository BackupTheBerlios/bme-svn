/*
 *  IUIListener.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 13-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_UI_LISTENER
#define I_UI_LISTENER

#include <string>
#include <stdint.h>

class IUIListener
{
public:
	IUIListener(std::string listenerName);
	virtual ~IUIListener();
	
	virtual std::string Id();
	
public:	
	static int32_t CurrentListenerId();
	
private:
	static int32_t s_listenerId;

private:
	std::string m_listenerName;
};

#endif
