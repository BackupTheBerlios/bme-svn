/*
 *  UIEventProvider.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 13-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef UI_EVENT_PROVIDER_H
#define UI_EVENT_PROVIDER_H

#include <vector>
#include "IUIListener.h"

class UIEventProvider
{
public:
	typedef std::vector<IUIListener*>::iterator UI;
public:
	UIEventProvider();
	virtual ~UIEventProvider();
	
	virtual void AddUIListener(IUIListener* userListener);
	virtual bool RemoveUIListener(IUIListener* userListener);
	std::vector<IUIListener*> GetAllListeners();
		
private:	
	std::vector<IUIListener*> m_uiUserListeners;
};

#endif
