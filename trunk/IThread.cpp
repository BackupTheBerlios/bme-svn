/*
 *  IThread.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 08-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#include "IThread.h"

IThread::IThread(IRunnable* runnable) 
{
	m_runnable = runnable;
}

IThread::~IThread() 
{ 
	delete m_runnable;
}

IRunnable* IThread::GetRunnable() 
{
	return m_runnable;
}

void IThread::SetRunnable(IRunnable* runnable) 
{
	m_runnable = runnable;
}

void IThread::Pause()
{
	this->Sleep(K_DEFAULT_PAUZE_TIME);
}

void IThread::SetThreadListener(IThreadListener* threadListener)
{
	m_threadListener = threadListener;
}

IThreadListener* IThread::ThreadListener()
{
	return m_threadListener;
}