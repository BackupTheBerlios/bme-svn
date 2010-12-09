/*
 *  IThread.h
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_THREAD_H
#define I_THREAD_H

#include "IRunnable.h"

#define K_DEFAULT_PAUZE_TIME	50000

class IThreadListener;

class IThread
{
public:
	IThread(IRunnable* runnable);
	virtual ~IThread();
	
	virtual void Start() = 0;
	virtual void Stop() = 0;
	
	virtual void Pause();
	virtual void Sleep(double timeInterval) = 0;
	virtual void Resume() = 0;

	virtual IRunnable* GetRunnable();
	virtual void SetRunnable(IRunnable* runnable);
	
	virtual void SetThreadListener(IThreadListener* threadListener);
	virtual IThreadListener *ThreadListener(); 
	
private:
	IRunnable* m_runnable;	
	IThreadListener* m_threadListener;
};

class IThreadListener
{
public:	
	virtual void ThreadStopped(IThread* thread) = 0;
};


#endif
