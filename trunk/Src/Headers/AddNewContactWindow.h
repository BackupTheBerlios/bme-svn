#ifndef ADD_NEW_CONTACT_WINDOW
#define ADD_NEW_CONTACT_WINDOW

#include <be/interface/Rect.h>
#include <be/interface/Window.h>
#include <be/interface/View.h>

class AddNewContactView;

class AddNewContactWindow : public BWindow
{
	public:
		AddNewContactWindow(BRect frame, const char* contactPassport);
};

class AddNewContactView : public BView
{
	public:
		AddNewContactView(BRect frame, const char* contactPassport);
};

#endif
