/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef SB_LOOPER_H
#define SB_LOOPER_H

#include <be/app/Looper.h>
#include <be/support/String.h>
#include "ServerLooper.h"

class SBLooper : public ServerLooper
{
	public:
		SBLooper(BLooper *owner, BString sbAddress, int port, BString authString);
		virtual				~SBLooper();
		
		virtual void		init();
		void				SetAuthString(BString authString);
		
	private:
		BString				m_authString;
};

#endif
