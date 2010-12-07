/*
 *  IImageManager.h
 *  Bme
 *
 *  Created by Tim De Jong on 18-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef I_IMAGE_MANAGER_H
#define I_IMAGE_MANAGER_H

#include <string>
#include "Image.h"

class IImageManager
{
public:	
	IImageManager() {};
	virtual ~IImageManager() {};
	
	virtual void*	GetUIBitmapFromImage(Image* image) = 0;
	virtual Image*	GetImageFromFile(std::string filename) = 0;
	virtual Image*	GetImageFromBytes(const uint8_t *bytes, uint8_t length) = 0;
};

#endif