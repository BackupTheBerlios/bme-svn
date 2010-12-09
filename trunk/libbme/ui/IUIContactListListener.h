/*
 *  IUIContactListListener.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_UI_CONTACT_LIST_LISTENER_H
#define I_UI_CONTACT_LIST_LISTENER_H

#include "Contact.h"
#include "IUIListener.h"

class IUIContactListListener : public IUIListener
{
public:
	IUIContactListListener() : IUIListener("ContactListListener") {};
	virtual ~IUIContactListListener() {};
	
	virtual void SyncListStarted() = 0;
	virtual void SyncListEnded() = 0;
	
	virtual void ContactAdded(Contact* contact) = 0;
	virtual void ContactStatusChanged(Contact* contact) = 0;
	virtual void GroupAdded(std::string groupId, std::string groupName) = 0;
};

#endif
