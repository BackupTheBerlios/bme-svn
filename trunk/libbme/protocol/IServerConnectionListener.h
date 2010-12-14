/*
 *  IServerConnectionListener.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 14-12-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_SERVER_CONNECTION_LISTENER_H
#define I_SERVER_CONNECTION_LISTENER_H

class IServerConnectionListener
{
public:
	virtual void DidConnect() = 0;
};

#endif
