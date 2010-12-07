/*
 *  IRunnable.h
 *  Bme
 *
 *  Created by Tim De Jong on 07-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_RUNNABLE_H
#define I_RUNNABLE_H

#include "IThread.h"

class IRunnableListener;

class IRunnable
{
public:
	IRunnable() {};
	virtual ~IRunnable() {};
	virtual bool Run() = 0;
	
	virtual void SetRunnableListener(IRunnableListener* listener) {m_runnableListener = listener;};
	virtual IRunnableListener* RunnableListener() {return m_runnableListener;};
	
private:
	IRunnableListener* m_runnableListener;
};

class IRunnableListener
{
public:
	virtual void RunnableStopped(IRunnable* runnable) = 0;
};

#endif
