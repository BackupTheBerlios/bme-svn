/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef CHAT_WINDOW_H
#include "ChatWindow.h"
#endif

#include <be/app/Message.h>
#include <be/interface/MenuBar.h>
#include <be/interface/Menu.h>
#include <be/interface/MenuItem.h>
#include <be/interface/InterfaceDefs.h>
#include "constants.h"
#include "MessageFields.h"
#include "ContactDetailsItem.h"
#include "Statusses.h"

#include "Common.h"

ChatWindow::ChatWindow(BRect frame, BString title)
				:	BWindow(frame, title.String(), B_TITLED_WINDOW, 0)
{
	//construct menu
	BMenuBar *chatMenuBar = new BMenuBar(BRect(0,0,0,0),"chatMenuBar");	
	AddChild(chatMenuBar);	
	//file menu
	BMenu *fileMenu = new BMenu("File");
	
	BMenuItem *saveItem = new BMenuItem("Save Conversation",new BMessage(B_SAVE_REQUESTED));
	fileMenu->AddItem(saveItem);
	
	BMessage *closeMsg = new BMessage(InterfaceMessages::K_CLOSE_CHAT_WINDOW);	
	BMenuItem *closeItem = new BMenuItem("Close", closeMsg);
	fileMenu->AddItem(closeItem);
	
	chatMenuBar->AddItem(fileMenu);
	//edit menu
	
	//background view
	float chatMenuBarHeight = (chatMenuBar->Bounds()).Height();
	BRect backgroundFrame(0.0f,chatMenuBarHeight,frame.Width(), frame.Height());
	BView *backgroundView = new BView(backgroundFrame,"backgroundView",B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	backgroundView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(backgroundView);
	//Construct list of contact details
	BRect contactDetailsFrame(0.0f, 1.0f, backgroundFrame.Width(), 42.0f);
	m_contactDetailsView = new BListView(contactDetailsFrame, "contactDetailsView", B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE | B_FRAME_EVENTS| B_FULL_UPDATE_ON_RESIZE);
	m_contactDetailsView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	m_contactScroll = new BScrollView("contactScroll", m_contactDetailsView, B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE, false, false, B_NO_BORDER);	
	backgroundView->AddChild(m_contactScroll);	
	
	//Construct ConvLogView, to show entire conversation	
	BRect convLogFrame(5.0f, contactDetailsFrame.bottom + 10.0f,backgroundFrame.Width() - 121.0f, backgroundFrame.Height() - 100.0f);
	BRect convLogTextFrame(0.0f,0.0f,convLogFrame.Width(), convLogFrame.Height());
	m_convLogView = new ConvLogView(convLogFrame, convLogTextFrame);
	m_convScroll = new BScrollView("convScroll", m_convLogView, B_FOLLOW_ALL_SIDES, 0, false, true);
	backgroundView->AddChild(m_convScroll);	
	//construct contact picture view, to display a contact avatar
	BRect contactPictureFrame(convLogFrame.right + 10.0f, convLogFrame.top, convLogFrame.right + 102.0f, convLogFrame.top + 92.0f);
	m_contactPictureView = new ContactPictureView(contactPictureFrame);
	backgroundView->AddChild(m_contactPictureView);
	//construct toolbar with font settings, etc.
	rgb_color topColor = {255,255,255,255};
	rgb_color bottomColor = {220,220,255,255};
	BRect toolbarFrame(0.0f, convLogFrame.bottom + 5.0f, backgroundFrame.Width(),convLogFrame.bottom + 30.0f);
	m_toolbarView = new GradientView(toolbarFrame,"toolbarView",B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM, topColor, bottomColor);
	backgroundView->AddChild(m_toolbarView);
	//construct ConvTextView, to enter text
	BRect convTextViewFrame(convLogFrame.left, toolbarFrame.bottom + 10.0f, convLogFrame.right - 30.0f, backgroundFrame.Height() - 10.0f);
	BRect convTextFrame(0.0f,0.0f,convTextViewFrame.Width(),convTextViewFrame.Height() * 10.0f);
	m_convTextView = new BTextView(convTextViewFrame,"convTextView",convTextFrame, B_FOLLOW_ALL_SIDES, B_WILL_DRAW);
	m_convTextScroll = new BScrollView("convTextScroll", m_convTextView, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_BOTTOM, 0, false, true);	
	backgroundView->AddChild(m_convTextScroll);
	
	Contact *contact1 = new Contact("harry@hotmail.com", "I wonder why people like to use such long names in msn","",0,statusses["NLN"]);
	AddContact(contact1);
	Contact *contact2 = new Contact("harry@hotmail.com", "Rémi","",0,statusses["IDL"]);
	AddContact(contact2);	
	Contact *contact3 = new Contact("harry@hotmail.com", "Joep","",0,statusses["NLN"]);
	AddContact(contact3);	
}

ChatWindow::~ChatWindow()
{
}

void ChatWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{		
		case B_SIMPLE_DATA:
		{
			//find out if contact has been dragged and dropped onto window
		}
		break;
		case InterfaceMessages::K_CONTACT_TYPING_MSG:
		{
			BString passport;
			message->FindString(K_CONTACT_PASSPORT, &passport);
			bool isTyping;
			message->FindBool(K_IS_TYPING, &isTyping);
			//turn typing on/off in contact details view
			//ContactDetailsItem *ci = m_contactDetailsView->FindContact(passport);
			//ci->SetTyping(isTyping);
			m_contactDetailsView->Invalidate();
		}
		break;
		default:
			BWindow::MessageReceived(message);
		break;
	}
}

void ChatWindow::AddContact(Contact *contact)
{		
	//add the contact to the contact details listview	
	ContactDetailsItem *ci = new ContactDetailsItem(contact);
	m_contactDetailsView->AddItem(ci);	
	//check if it is the first contact to add to conversation
	int32 noItems = m_contactDetailsView->CountItems();
	if (noItems == 1)
	{
		BString windowTitle = "Chatting with ";
		windowTitle << contact->FriendlyName();
		SetTitle(windowTitle.String());
	}
	//resize m_contactDetailsView to fit the contact details items	
	float contactViewWidth = (m_contactDetailsView->Bounds()).Width();	
	if (noItems <= 3)
	{
		float newHeight = noItems * (ci->Height() + 1.0f);	
		m_contactScroll->ResizeTo(contactViewWidth, newHeight);		
	}
	else
	{
		//resize to 3 times item height(max height)
		m_contactScroll->ResizeTo(contactViewWidth, 3.0f * (ci->Height() + 1.0f));			
		//add scrollbar??				
	}
	
	float convX = (m_convScroll->Frame()).left;
	float convY = m_contactDetailsView->Frame().bottom + 10.0f;
	m_convScroll->MoveTo(convX, convY);
	
	float contactPicX = m_convScroll->Frame().right + 10.0f;
	m_contactPictureView->MoveTo(contactPicX, convY);

	float toolbarX = (m_toolbarView->Frame()).left;
	float toolbarY = (m_convScroll->Frame()).bottom + 5.0f;
	m_toolbarView->MoveTo(toolbarX,toolbarY);
	
	float convTextX = (m_convTextScroll->Frame()).left;
	float convTextY = (m_toolbarView->Frame()).bottom + 10.0f;	
	m_convTextScroll->MoveTo(convTextX,convTextY);		
}

void ChatWindow::RemoveContact(Contact *contact)
{
}
