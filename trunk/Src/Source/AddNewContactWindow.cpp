#ifndef ADD_NEW_CONTACT_WINDOW
#include "AddNewContactWindow.h"
#endif

#include <be/interface/Button.h>
#include "GradientView.h"


AddNewContactWindow::AddNewContactWindow(BRect frame, const char* contactPassport)
						:	BWindow(frame, "Someone wants to add you to his/her contact list", B_TITLED_WINDOW,0)
{
	AddChild(new AddNewContactView(Bounds(), "obelmiks@hotmail.com"));
} 

//===========================AddNewContactView=============================================
AddNewContactView::AddNewContactView(BRect frame, const char* contactPassport)
						:	BView(frame, "AddNewContactView", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	rgb_color topColour = {255,255,255,255};
	rgb_color bottomColour = {220,220,255,255};
	GradientView *backgroundView = new GradientView(Bounds(),"backgroundView", B_FOLLOW_ALL_SIDES,topColour,bottomColour);
	AddChild(backgroundView);
	
	//question
	//contactPassport + "wants to add you to his or her contactList. \n Do you want to add this person to your contactlist too?"
	//radio options
	//block person
	//add person to specific group
	//add okButton to right bottom of the screen
	float okWidth = 70.0f;
	float okHeight = 20.0f;
	float borderSize = 5.0f;
	
	BRect backgroundBounds = backgroundView->Bounds();
	
	BRect okFrame(backgroundBounds.Width() - okWidth - borderSize, backgroundBounds.Height() - okHeight - borderSize, backgroundBounds.Width() - borderSize, backgroundBounds.Height() - borderSize);
	BButton *okButton = new BButton(okFrame,"okButton","Ok", new BMessage());
	backgroundView->AddChild(okButton);	
}
