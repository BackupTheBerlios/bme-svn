/*
 *  MSNP12Protocol.h
 *  Bme
 *
 *  Created by Tim De Jong on 17-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MSPN12_PROTOCOL_H
#define MSPN12_PROTOCOL_H

#include "Protocol.h"
#include "MSNP12Protocol.h"
#include "IUserProtocol.h"
#include "MSNP12UserProtocol.h"
#include "MSNP12ContactListProtocol.h"
#include "IProtocolDelegate.h"
#include "NSServerConnection.h"

class MSNP12Protocol : public Protocol, public IProtocolDelegate
{
public:
	MSNP12Protocol();
	virtual ~MSNP12Protocol();
	
	virtual std::string Version();
	virtual void Login(std::string username, std::string password);

public:
	virtual void AuthenticationCompleted();
	virtual void SyncListEnded();
	
protected:
	virtual IUserProtocol* GetUserProtocol();
	virtual IContactListProtocol* GetContactListProtocol();
	virtual IConversationManagerProtocol* GetConversationManagerProtocol();
	
private:
	NSServerConnection* m_connection; 
	MSNP12UserProtocol* m_userProtocol;
	MSNP12ContactListProtocol* m_contactListProtocol;
};

#endif
