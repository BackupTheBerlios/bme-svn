/*
 *  IUIUserListener.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_UI_USER_LISTENER
#define I_UI_USER_LISTENER

#include "IUIListener.h"

class IUIUserListener : public IUIListener
{
public:	
	IUIUserListener();
	virtual ~IUIUserListener(); 
	
	virtual void UsernameFound(std::string username); 
};

#endif
