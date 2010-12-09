/*
 *  Status.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
/*****************************************************************
 * Copyright (c) 2005 Tim de Jong 								 *
 *							       								 *
 * All rights reserved.											 *
 * Distributed under the terms of the MIT License.               *
 *****************************************************************/
#ifndef STATUS_H
#define STATUS_H

#include <string>
#include <map>
#include "Color.h"
#include "Image.h"
#include "ProtocolConstants.h"

/** Class representing different IM statusses
 @author Tim de Jong
 */
class Status //: public BArchivable
{
private:
	static std::map<std::string, Status*> s_allStatusses;

public:
	static std::map<std::string, Status*> GetAllStatusses();
	static Status* GetStatusForAbbreviation(std::string abbreviation);
	
public:
	Status();
	Status(std::string statusName, std::string statusAbbr, Image* icon, bool usrChoice, Color statusColour);
	virtual				~Status();
	
	void				SetStatusName(std::string name);
	std::string			GetStatusName();		
	
	void				SetAbbreviation(std::string abbreviation);
	std::string			GetAbbreviation();		
	
	Image*				GetStatusIcon(int32_t width = 18);		
	void				AddIcon(Image *statusIcon);
	
	bool				IsOnline() const;
	
	void				SetUserChoice(bool userChoice);
	bool				IsUserChoice() const;
	
	void				SetStatusColour(Color colour);
	Color				StatusColour() const;
	
	//archivable methods
	//static BArchivable*	Instantiate(BMessage *archive);
	//virtual status_t	Archive(BMessage *archive, bool deep = true) const;		
	
private:
	std::string				m_statusName,
							m_statusAbbreviation;
	
	bool					m_userChoice;
	Color					m_statusColour;
	
	std::map<int32_t,Image*>		m_statusIcons;
};

#endif

