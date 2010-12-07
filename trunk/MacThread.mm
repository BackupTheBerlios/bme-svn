/*
 *  MacThread.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MacThread.h"

MacThread::MacThread(IRunnable* runnable) 
			:	IThread(runnable)
{
	runnable->SetRunnableListener(this);
	m_macThreadWrapper = [[MacThreadWrapper alloc] initWithRunnable:runnable];
}

MacThread::~MacThread()
{
	[m_macThreadWrapper release];
}

void MacThread::Start()
{
	[m_macThreadWrapper start];
}

void MacThread::Stop()
{	
	[m_macThreadWrapper stop];
}

void MacThread::Sleep(double timeInterval)
{
	[m_macThreadWrapper sleep:timeInterval];
}

void MacThread::Resume()
{
}

void MacThread::RunnableStopped(IRunnable* runnable)
{
	this->ThreadListener()->ThreadStopped(this);
}

@implementation MacThreadWrapper

@synthesize m_thread, m_runnable, m_stop;

-(id)initWithRunnable:(IRunnable*)runnable
{
	self = [super init];
	if (self)
	{
		m_runnable = runnable;
		m_stop = NO;
		//spawn thread for runnable
		NSThread* thread = [[NSThread alloc] initWithTarget:self selector:@selector(runMethod) object:nil];
		self.m_thread = thread;
		[thread release];
	}
	return self;
}

-(void)runMethod
{	
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	do
	{		
		[self sleep:0.025];
	}
	while(m_runnable->Run() && !m_stop);
	
	//[NSThread exit];
	NSLog(@"Thread exited");
	m_runnable->RunnableListener()->RunnableStopped(m_runnable);
	[pool release];
}

-(void)start
{
	[m_thread start];
}

-(void)stop
{
	m_stop = YES;
	[m_thread cancel];
}

-(void)sleep:(double)timeInterval
{
	[NSThread sleepForTimeInterval:timeInterval];
}

-(BOOL)isRunning
{
	return [m_thread isExecuting];
}

-(void)dealloc
{
	[m_thread release];
	[super dealloc];
}

@end


