/*
 *  Image.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 10-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "Image.h"

Image::Image(std::string imageId)
		:	m_imageId(imageId)
{
}

Image::Image(std::string imageId, double width, double height)
		:	m_imageId(imageId),
			m_width(width),
			m_height(height)
{
}

Image::~Image()
{
}

std::string Image::ImageId()
{
	return m_imageId;
}

void Image::SetWidth(double width)
{
	m_width = width;
}

double Image::GetWidth()
{
	return m_width;
}

void Image::SetHeight(double height)
{
	m_height = height;
}

double Image::GetHeight()
{
	return m_height;
}