/*
 *  IProtocolDelegate.h
 *  Bme
 *
 *  Created by Tim De Jong on 06-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_PROTOCOL_DELEGATE_H
#define I_PROTOCOL_DELEGATE_H

class IProtocolDelegate 
{
public:
	IProtocolDelegate() {};
	virtual ~IProtocolDelegate() {};
	
	virtual void AuthenticationCompleted() = 0;
	virtual void SyncListEnded() = 0;
};

#endif
