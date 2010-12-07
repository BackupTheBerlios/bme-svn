/*
 *  Status.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "Status.h"
#include "BmeClient.h"
#include "XMLNode.h"
#include "IPath.h"
#include "PlatformSpecific.h"
#include "IImageManager.h"
#include "Image.h"

std::map<std::string, Status*> Status::s_allStatusses;

std::map<std::string, Status*> Status::GetAllStatusses()
{
	if (s_allStatusses.size() == 0)
	{	
		IImageManager* imageManager = PlatformSpecific::GetImageManager();
		//otherwise open status XML file
		typedef vector<XMLNode*>::const_iterator SI;
		vector<XMLNode*> statusNodes = BmeClient::GetPreferences()->GetIconPrefs()->GetStatusNodes();
		
		for (SI s = statusNodes.begin(); s != statusNodes.end(); ++s)
		{
			XMLNode* statusNode = *s;
			if (statusNode->Name() == "status")
			{
				vector<XMLNode*> children = statusNode->Children();
				Status* status = new Status();
				for (SI c = children.begin(); c != children.end(); ++c)
				{
					
					XMLNode* statusChild = *c;
					if (statusChild->Name() == "icon")
					{						
						std::string iconPath = statusChild->StringValue();
						IPath* iconFullPath = PlatformSpecific::GetPathManager()->GetIconPrefsPath()->Append(iconPath);
						
						Image* statusIcon = imageManager->GetImageFromFile(iconFullPath->ToString());
						status->AddIcon(statusIcon);
						delete iconFullPath;
					}
					else if (statusChild->Name() == "message")
					{
						status->SetStatusName(statusChild->StringValue());
					}
					else if (statusChild->Name() == "protocol")
					{
						status->SetAbbreviation(statusChild->StringValue());
					}
					else if (statusChild->Name() == "visible")
					{
						bool userChoice = atoi(statusChild->StringValue().c_str());
						status->SetUserChoice(userChoice);
					}
					else if (statusChild->Name() == "color")
					{
					}
				}
				s_allStatusses[status->GetAbbreviation()] = (status);
			}
		}
		delete imageManager;
	}
	return s_allStatusses;
}

Status* Status::GetStatusForAbbreviation(std::string abbreviation)
{
	std::map<std::string, Status*> statusses = Status::GetAllStatusses();
	return statusses[abbreviation];
}

Status::Status()
			:	m_statusName("Offline"),
				m_statusAbbreviation(Statusses::K_HIDDEN),
				m_userChoice(true)
{
}

/**	Constructor
 @param statName,
 @param statAbbr,
 @param icon
 @param usrChoice	
 */
Status::Status(std::string statName, std::string statAbbr, Image* icon, bool usrChoice, Color statusColour)
:	m_statusName(statName),
	m_statusAbbreviation(statAbbr),
	m_userChoice(usrChoice),
	m_statusColour(statusColour)					

{
	AddIcon(icon);		
}

/**	Destructor
 */
Status::~Status()
{	
	typedef map<int32_t, Image*>::const_iterator II;
	for (II p = m_statusIcons.begin(); p != m_statusIcons.end(); ++p)
	{
		delete (*p).second;
	}
}

void Status::SetStatusName(std::string name)
{
	m_statusName = name;
}

/**	Get the user readable name of this status.
 @return a human readable status name.
 */
std::string Status::GetStatusName() 
{
	return m_statusName;
}

void Status::SetAbbreviation(std::string abbreviation)
{
	m_statusAbbreviation = abbreviation;
}

/**	Gets the abbreviation for this status. This abbreviation is
 used by the protocol to set and identify the status.
 @return an abbreviation representing the status, used by the
 messenger protocol.
 */
std::string Status::GetAbbreviation()
{
	return m_statusAbbreviation;
}

/**	Gets the icon representation of this status.
 @return a bitmap representing this status.
 */
Image* Status::GetStatusIcon(int32_t width)
{
	return m_statusIcons[width];
}

/**	
 */
void Status::AddIcon(Image *statusIcon)
{
	int32_t width = int32_t(statusIcon->GetWidth());
	m_statusIcons[width] = statusIcon;
}

/**	Returns if this status represents an online status: true if
 it does, false otherwise.
 @return true if the status is one of the online statusses,
 false if it is the offline status.
 */
bool Status::IsOnline() const
{ 	
	return m_statusAbbreviation != Statusses::K_OFFLINE;
}


void Status::SetUserChoice(bool userChoice)
{
	m_userChoice = userChoice;
}

/**	Returns if this status is a status that can be chosen by the user.
 @return true if the status can be set by the user, false if not.
 */
bool Status::IsUserChoice() const
{
	return m_userChoice;
}

void Status::SetStatusColour(Color colour)
{
	m_statusColour = colour;
}

Color Status::StatusColour() const
{
	return m_statusColour; 
}
