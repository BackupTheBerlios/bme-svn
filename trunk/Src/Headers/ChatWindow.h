/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <be/app/Message.h>
#include <be/interface/Rect.h>
#include <be/interface/Window.h>
#include <be/interface/TextView.h>
#include <be/interface/ListView.h>
#include <be/interface/ScrollView.h>
#include <be/support/String.h>
#include "ConvLogView.h"
#include "Contact.h"
#include "GradientView.h"
#include "ContactPictureView.h"

class ChatWindow : public BWindow
{
	public:
		ChatWindow(BRect frame, BString title);
		virtual				~ChatWindow();
		
		virtual void		MessageReceived(BMessage *message);
	
	private:
		void				AddContact(Contact *contact);
		void				RemoveContact(Contact *contact);
		
	private:
		ConvLogView			*m_convLogView;
		BTextView			*m_convTextView;
		BListView			*m_contactDetailsView;

		BScrollView 		*m_convScroll,
							*m_convTextScroll,
							*m_contactScroll;
							
		GradientView		*m_toolbarView;
		ContactPictureView	*m_contactPictureView;
};

#endif
