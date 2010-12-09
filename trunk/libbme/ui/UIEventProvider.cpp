/*
 *  UIEventProvider.cpp
 *  BmeApp
 *
 *  Created by Tim De Jong on 13-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "UIEventProvider.h"

UIEventProvider::UIEventProvider()
{
}

UIEventProvider::~UIEventProvider()
{
	//delete the contactlist listeners here?
}

void UIEventProvider::AddUIListener(IUIListener* uiListener)
{
	m_uiUserListeners.push_back(uiListener);
}

bool UIEventProvider::RemoveUIListener(IUIListener* userListener)
{
	for (UI ul = m_uiUserListeners.begin(); ul != m_uiUserListeners.end(); ++ul) 
	{
		IUIListener* currentListener = *ul;
		if (userListener->Id() == currentListener->Id())
		{
			m_uiUserListeners.erase(ul);
			return true;
		}
	}	
	return false;
}

std::vector<IUIListener*> UIEventProvider::GetAllListeners()
{
	return m_uiUserListeners;
}