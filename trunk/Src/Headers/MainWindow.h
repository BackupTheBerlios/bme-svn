/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <be/interface/Rect.h>
#include <be/interface/Window.h>
#include <be/interface/View.h>
#include <be/interface/TextControl.h>
#include <be/interface/CheckBox.h>
#include <be/interface/Button.h>
#include <be/interface/StringView.h>
#include <be/interface/MenuField.h>
#include <be/app/Looper.h>
#include <be/app/Message.h>
#include "LayeredView.h"
#include "ComboBox.h"
#include "AnimatedBitmapView.h"
#include "ProtocolLooper.h"
#include "ContactListView.h"
#include "EditableStringView.h"
#include "StatusMenu.h"

#include "EditableListItem.h"

class MainWindow : public BWindow
{
	public:
		MainWindow(BRect frame, ProtocolLooper *protocolLooper);
		virtual				~MainWindow();
		
		virtual void		MessageReceived(BMessage *message);		
		virtual bool		QuitRequested();
		
	private:
		BView				*constructLoginView(BRect frame);
		BView				*constructContactView(BRect frame);
				
	private:
		ProtocolLooper		*m_protocolLooper;
		LayeredView			*m_layeredView;
		
		ComboBox			*m_username;
		BTextControl		*m_password;
		BCheckBox			*m_passwordSaveCheck;
		BButton				*m_signinButton;
		BBitmap				*m_statusBitmap;
		AnimatedBitmapView	*m_signinStatusView;
		BStringView			*m_statusBarView;		
		
		BMessage			m_passwordList;
		
		BString				m_statusString;
		
		EditableStringView	*m_userNameView,
							*m_personalMessageView
							;
							
		StatusMenu 			*m_statusMenu;
		ContactListView		*m_contactListView;
		
		EditableListItem 	*groupName;
	private:
		enum 
		{
			K_LOGIN_VIEW_LAYER =				0, 
			K_CONTACT_VIEW_LAYER =				1
		};
};

#endif
