/*
 *  Image.h
 *  Bme
 *
 *  Created by Tim De Jong on 10-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image
{
public:
	Image(std::string imageId);
	Image(std::string imageId, double width, double height);
	virtual ~Image();
	
	std::string ImageId();
	
	void SetWidth(double width);
	double GetWidth();
	
	void SetHeight(double height);
	double GetHeight();
	
private:
	std::string		m_imageId;
	double			m_width,
					m_height
					;
};

#endif
