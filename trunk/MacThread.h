/*
 *  MacThread.h
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_THREAD_H
#define MAC_THREAD_H

#include "IThread.h"

@interface MacThreadWrapper : NSObject 
{
	NSThread* m_thread;
	IRunnable* m_runnable;
	BOOL m_stop;
}

@property (nonatomic, retain) NSThread* m_thread;
@property (assign) IRunnable* m_runnable;
@property BOOL m_stop;

-(id)initWithRunnable:(IRunnable*)runnable;
-(void)runMethod;
-(void)start;
-(void)stop;
-(void)sleep:(double)timeInterval;
-(BOOL)isRunning;
-(void)dealloc;

@end

class MacThread : public IThread, IRunnableListener
{
public:
	MacThread(IRunnable* runnable); 
	virtual ~MacThread();
	
	virtual void Start();
	virtual void Stop();
	
	virtual void Sleep(double timeInterval);
	virtual void Resume();

	virtual void RunnableStopped(IRunnable* runnable);

private:	
	MacThreadWrapper* m_macThreadWrapper;
};

#endif