/*****************************************************************
 * Copyright (c) 2005 Tim de Jong								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef CONV_LOG_VIEW_H
#include "ConvLogView.h"
#endif

#include <be/app/Cursor.h>
#include <be/app/Messenger.h>
#include <be/interface/Region.h>
#include <be/interface/Window.h>
#include <be/translation/TranslationUtils.h>
#include "constants.h"
#include "MessageFields.h"

ConvLogView::ConvLogView(BRect frame,  BRect textRect) 
				:	BTextView(frame, NULL, textRect, B_FOLLOW_ALL, B_WILL_DRAW)
{
	SetStylable(true);
	SetWordWrap(true);
	MakeEditable(false);
	//fSOffset = -1;
	SetViewColor(255,255,255);
	
	BBitmap *smiley = BTranslationUtils::GetBitmap("/ZetaOS/home/Documents/Programming/Miksprojects/Bme/Graphics/Icons/Standard/Emoticons/001.png"); 
	m_emoticonList.push_back(smiley);
	SetText("This is a test \03300");
}

ConvLogView::~ConvLogView()
{
}

void ConvLogView::MessageReceived(BMessage *message)
{
	switch(message->what)
	{		
		case InterfaceMessages::K_ADD_CHAT_TEXT:
		{
			//get text message
			
			//get emoticons from message and and them to the emoticonlist
			
			//get url from message and add them to urlInfoList
		}
		break;
		default:
			BTextView::MessageReceived(message);
		break;
	}
}

void ConvLogView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	bool overURL = false;

	if(transit == B_INSIDE_VIEW) 
	{
		typedef vector<URLInfo*>::const_iterator CI;
		for(CI p = m_urlInfoList.begin(); p != m_urlInfoList.end(); ++p) 
		{
			if((*p)->Contains(this, point)) 
			{
				// Mouse is over a link. Display "URL hover cursor".
				// That cursor is identical to the BeOS hand cursor
				// but contains a little arrow (like in Net+).
				#if B_BEOS_VERSION >= B_BEOS_VERSION_5
					const BCursor URLHoverCursor(K_CURSOR_HYPERLINK);				
					SetViewCursor(&URLHoverCursor);
				#else
					be_app->SetCursor(K_CURSOR_HYPERLINK);
				#endif
				
				overURL = true;
				
				break;
			}
		}
		
		#if B_BEOS_VERSION >= B_BEOS_VERSION_5
		if(!overURL) 
		{
			SetViewCursor(B_CURSOR_I_BEAM);
		}
		#endif
	}
	
	if(!overURL)
		BTextView::MouseMoved(point, transit, message);
}

void ConvLogView::MouseDown(BPoint point)
{
	//check if an url has been clicked!
	typedef vector<URLInfo*>::const_iterator CI;
	for(CI p = m_urlInfoList.begin(); p != m_urlInfoList.end(); ++p) 
	{
		URLInfo *urlInfo = (*p);
		if(urlInfo->Contains(this, point)) 
		{
			//User clicked on an anchor. Send message to open webbrowser 
			//or eMail client.
			BMessage *urlOpenMessage = new BMessage(InterfaceMessages::K_OPEN_URL_MSG);
			urlOpenMessage->AddString(K_URL_STRING, urlInfo->GetURL());
			BMessenger owner(Window());
			owner.SendMessage(urlOpenMessage);
			return;
		}
	}	
	BTextView::MouseDown(point);
}

void ConvLogView::Draw(BRect updateRect)
{
	/*if (fSOffset > -1) 
	{
		BPoint point = PointAt(fSOffset);
		float height = TextHeight(LineAt(fSOffset),LineAt(fSOffset + fLen-1));
		BRect rect(point.x,point.y,Frame().Width(),point.y + height);
		SetHighColor(245,245,245);
		FillRect(rect);
	}*/
	//BTextView::Draw(updateRect);
	
	BString text = Text();
	SetDrawingMode(B_OP_ALPHA);
	SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_COMPOSITE);
	
	//draw emoticons within text
	int32 offset = 0;
	while (text.FindFirst("\033", offset) != B_ERROR)
	{
		offset = text.FindFirst("\033", offset);
		
		//find emoticon
		for (uint32 i = 0; i < m_emoticonList.size(); i++)
		{
			BString cod = "\033";
			if (i < 10)
				cod << "0";
			cod << i;	
			if (offset == text.FindFirst(cod, offset))
			{				
				BBitmap *eicon = m_emoticonList[i];
				DrawBitmap(eicon,PointAt(offset));
				offset++;	
				break;
			}
		}
	}
}

void ConvLogView::FrameResized(float width, float height)
{
	BTextView::FrameResized(width, height);
	
	if (DoesWordWrap()) 
	{
		BRect textRect;
		textRect = Bounds();
		textRect.OffsetTo(B_ORIGIN);
		SetTextRect(textRect);
	}
}

void ConvLogView::InsertAnchor(const char *anchorText, const char *href, int32 offset)
{
}

//=========================ConvLogView::URLInfo===============================
ConvLogView::URLInfo::URLInfo(int32 start, int32 end, BString href) 
						:	m_start(start), 
							m_end(end),
							m_href(href)
{
}

ConvLogView::URLInfo::~URLInfo()
{	
}


bool ConvLogView::URLInfo::Contains(ConvLogView *view, BPoint point)
{
	// Returns true, if the point is over this URL.
	BRegion region;
	view->GetTextRegion(m_start, m_end, &region);
	
	return region.Contains(point);
}

BString	ConvLogView::URLInfo::GetURL()
{
	return m_href;
}

//==================ConvLogView::CTextRun ===================================
ConvLogView::TextRun::TextRun(const text_run &other)
{ 
	(text_run &)(*this) = other; 
}

ConvLogView::TextRun::TextRun(int32 _offset, BFont _font, rgb_color _color) 
{
	offset	= _offset;
	font	= _font;
	color	= _color;
}
